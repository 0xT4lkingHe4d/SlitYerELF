#include "../include/pack.hh"

#define DO_DEBUG_H
#ifdef DO_DEBUG_H
#define dbgf(fmt, ...) {        \
    printf(fmt, __VA_ARGS__);   \
    puts("");                   \
}
#else
#define dbgf(fmt, ...)
#endif

void pack::sort_px() {
    px.sort([](struct patch_st& a, struct patch_st& b) {
        return a.dst.off < b.dst.off;
    });
}

void pack::fill() {
    sort_px();
    std::list<std::tuple<__u64, __u64>> ll;
    __u64 l = 0;
    for (auto& p : px) {
        __s64 sz = p.dst.off - l;
        if (!!l && sz > 0)
            ll.emplace_back(l, sz);
        l = p.dst.off + p.mm.sz;
    }
    ll.emplace_back(l, s_elf->size - l);

    for (auto& [off, sz] : ll)
        px.elf_add(ElfHdrT::Filling, s_elf, off, sz);
}

#define _each_phdr(mem, sz, _e_)        \
        for (Elf_Phdr *_e_ = (Elf_Phdr*)(mem); (__u64)_e_ < ((__u64)(mem) + (__u64)(sz)); _e_++)

#define foreach_pack_phdr(e, p, ph)                     \
        for (auto& p : (e)->px)                         \
            if (p.src.off == (e)->s_elf->ehdr->e_phoff) \
                _each_phdr(p.mm.mem, p.mm.sz, ph)


hook_ctx pack::hook_fn(struct rel_patch_t *rx, __u64 imm) {
    return (hook_ctx){.ok=true, .v=imm};
}

bool pack::rel_exec() {
    foreach_pack_phdr(this, p, ph) {
        if (ph->p_flags & PF_X) {
            struct mmsz_t mm = {
                .t      = PackPtrT::Elf,
                .mem    = s_elf->off<void*>(ph->p_offset),
                .sz     = ph->p_filesz,
            };
            auto r = RelInstr(this, &pack::hook_fn, ph->p_offset, s_elf, mm);
            r.auto_patch();
            rel.push_back(r);
        }
    }
    return true;
}

struct patch_st *pack::slit_sub_px(__u64 off, __u64 sz) {
    for (auto& p : px)
        if (_contain_(p.src.off, p.src.sz, off)) {
            if (p.src.off + p.src.sz >= off + sz) {
                p.src.sz = off - p.src.off;
                px.elf_add(p.src.hdr_type, s_elf, off + sz, p.src.sz - sz);
                return px.elf_add(ElfHdrT::Instr, s_elf, off, sz);
            }
        }
    return nullptr;
}

void pack::shift(__u64 off, __u64 sz) {
    for (auto& p : px)
        if (p.dst.off > off) p.dst.off += sz;
}

void pack::init() {
    for (auto& r : rel) {
        auto ret = slit_sub_px(r.src.off, r.src.sz);
        if (!ret) asm("int3");
        shift(r.src.off + r.src.sz, ret->mm.sz - r.src.sz);
        ret->mm = *r.init();
    }
}

RelInstr *pack::get_rel(std::shared_ptr<Elf> _elf, __u64 off) {
    return get_rel(_elf.get(), off);
}
RelInstr *pack::get_rel(Elf *_elf, __u64 off) {
    for (auto& r : rel)
        if (r.s_tup.elf.get() == _elf && r.has(off)) return &r;
    
    return nullptr;
}

#define __each_elf(mem, sz, T, _e_)         \
        for (T *_e_ = (T*)(mem); (__u64)_e_ < (__u64)((__u64)(mem) + (sz)); _e_++)

#define each_dyn(mem, sz, _e_)      __each_elf(mem, sz, Elf_Dyn, _e_) if (_e_->d_tag == DT_NULL) break; else
#define each_sym(mem, sz, _e_)      __each_elf(mem, sz, Elf_Sym, _e_)
#define each_rela(mem, sz, _e_)     __each_elf(mem, sz, Elf_Rela, _e_)
#define each_rel(mem, sz, _e_)      __each_elf(mem, sz, Elf_Rel, _e_)

namespace PackPatch {
    void dyn(pack& p, struct patch_st& px);
    void rela(pack& p, struct patch_st& px);
};

void PackPatch::dyn(pack& p, struct patch_st& px) {
    each_dyn(px.mm.mem, px.mm.sz, dyn) {
        if (!!px.src.elf->dyn_is_ptr(dyn)) {
            RelInstr *r = p.get_rel(px.src.elf, dyn->d_un.d_ptr);
            if (!r) break;

            dbgf("%lx --> +%lx", dyn->d_un.d_ptr, r->offset(px.src.elf, dyn->d_un.d_ptr));
            dyn->d_un.d_ptr = r->offset(px.src.elf, dyn->d_un.d_ptr);
        }
    }
}

void PackPatch::rela(pack& p, struct patch_st& px) {
    each_rela(px.mm.mem, px.mm.sz, r) {
        __u64 v = 0;
        switch (ELF64_R_TYPE(r->r_info)) {
            case R_X86_64_RELATIVE:
            {
                RelInstr *rel = p.get_rel(px.src.elf, r->r_addend);
                if (!rel) break;
                dbgf("%lx -->> +%lx", r->r_addend, rel->offset(px.src.elf, r->r_addend));
                r->r_addend = rel->offset(px.src.elf, r->r_addend);          
            }
            break;
            case R_X86_64_GLOB_DAT:
            case R_X86_64_JUMP_SLOT:
            {
                RelInstr *rel = p.get_rel(px.src.elf, r->r_offset);
                if (!rel) break;
                dbgf("%lx -->> +%lx", r->r_offset, rel->offset(px.src.elf, r->r_offset));
                r->r_offset = rel->offset(px.src.elf, r->r_offset);           
            }
            break;
        }
    }
}

void pack::patch_elf() {
    for (auto& p : px) {
        if (p.mm.is_alloc()) p.mm.alloc();

        switch (p.src.hdr_type) {
            case ElfHdrT::Relatab:
                PackPatch::rela(*this, p);
                break;

            case ElfHdrT::Dyntab:
                PackPatch::dyn(*this, p);
                break;
            }
    }
}

__s8 pack::make(char *file) {
    int fd = open(file, O_CREAT|O_RDWR, 0755);
    if (fd == -1) return -1;
    init();
    patch_elf();

    for (auto& p : px)
        pwrite(fd, p.mm.mem, p.mm.sz, p.dst.off);
    
    close(fd);
    return 0;
}


struct patch_st *pack::px_orig_off(__u64 off) {
    for (auto& p : px)
        if (_contain_(p.src.off, p.src.sz, off))
            return &p;
    return nullptr;
}

struct patch_st *pack::px_orig_virt(__u64 virt) {
    for (auto& p : px)
        if (_contain_(p.src.off, p.src.sz, s_elf->vtof(virt)))
            return &p;
    return nullptr;
}
