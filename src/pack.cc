#include <assert.h>
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

#define __each_elf(mem, _n_, T, _e_)         \
        for (T *_e_ = (T*)(mem); (__u64)_e_ < (__u64)((__u64)(mem) + (_n_*sizeof(T))); _e_++)

#define each_dyn(mem, _n_, _e_)      __each_elf(mem, _n_, Elf_Dyn, _e_) if (_e_->d_tag == DT_NULL) break; else
#define each_sym(mem, _n_, _e_)      __each_elf(mem, _n_, Elf_Sym, _e_)
#define each_phdr(mem, _n_, _e_)      __each_elf(mem, _n_, Elf_Phdr, _e_)
#define each_shdr(mem, _n_, _e_)      __each_elf(mem, _n_, Elf_Shdr, _e_)
#define each_rela(mem, _n_, _e_)     __each_elf(mem, _n_, Elf_Rela, _e_)
#define each_rel(mem, _n_, _e_)      __each_elf(mem, _n_, Elf_Rel, _e_)

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
        if (!!l && sz > 0) ll.emplace_back(l, sz);
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

void pack::shift(__u64 off, __u64 sz) { // all the fucking headers
    for (auto& p : px) {
        std::shared_ptr<Elf> elf = p.src.elf;
        __u64 virt = elf->ftov(off);

        switch (p.src.hdr_type) {
            case ElfHdrT::Ehdr:
            {
                auto [ehdr, _] = p.mm.ptr<Elf_Ehdr>();
                if (ehdr->e_phoff >= off) ehdr->e_phoff += sz;
                if (ehdr->e_shoff >= off) ehdr->e_shoff += sz;
            };
            break;
            case ElfHdrT::Phdr:
            {
                auto [phdr, n] = p.mm.ptr<Elf_Phdr>();
                each_phdr(phdr, n, p) {
                    __u64 align_sz = ALIGN(p->p_align, sz);
                    if ((static_cast<ElfX_Phdr*>(p))->hasOff(off)) {
                        p->p_memsz  += align_sz;
                        p->p_filesz += align_sz;
                    } else if (p->p_offset > off) {
                        p->p_offset += sz;
                        p->p_vaddr  += sz;
                        p->p_paddr  += sz;
                    }
                }
            };
            break;
            case ElfHdrT::Shdr:
            {
                auto [shdr, n] = p.mm.ptr<Elf_Shdr>();
                each_shdr(shdr, n, sec) {
                    if ((static_cast<ElfX_Shdr*>(sec))->hasOff(off)) {
                        sec->sh_size    += sz;
                    } else if (sec->sh_offset > off) {
                        sec->sh_offset  += sz;
                        sec->sh_addr    += sz;
                    }
                }
            };
            break;
            case ElfHdrT::Symtab:
            {
                auto [stab, n] = p.mm.ptr<Elf_Sym>();
                each_sym(stab, n, sym)
                    if (sym->st_value >= virt) sym->st_value += sz;
            };
            break;
            // case ElfHdrT::Dyntab:   break;
            // case ElfHdrT::Note:     break;
            // case ElfHdrT::Reltab:   break;
            // case ElfHdrT::Relatab:  break;
            // case ElfHdrT::Strtab:   break;

        }
    }
    for (auto& p : px)
        if (p.dst.off > off) p.dst.off += sz;
}

void pack::init() {
    for (auto& r : rel) {
        auto ret = slit_sub_px(r.src.off, r.src.sz);
        assert(!!ret);
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

namespace PackPatch {
    void ehdr(pack& p, struct patch_st& px);
    void dyn(pack& p, struct patch_st& px);
    void rela(pack& p, struct patch_st& px);
};


void PackPatch::ehdr(pack& p, struct patch_st& px) {
    Elf_Ehdr *ehdr = (Elf_Ehdr*)px.mm.mem;
    ehdr->e_entry = p.vtov(px, ehdr->e_entry);
    ehdr->e_shoff = p.ftof(px, ehdr->e_shoff);
    ehdr->e_phoff = p.ftof(px, ehdr->e_phoff);
}

void PackPatch::dyn(pack& p, struct patch_st& px) {
    auto [dtab, n] = px.mm.ptr<Elf_Dyn>();
    each_dyn(dtab, n, dyn)
        if (!!px.src.elf->dyn_is_ptr(dyn))
            dyn->d_un.d_ptr = p.vtov(px, dyn->d_un.d_ptr);
}

void PackPatch::rela(pack& p, struct patch_st& px) {
    auto [rtab, n] = px.mm.ptr<Elf_Rela>();
    each_rela(rtab, n, r) {
        __u64 v = 0;
        switch (ELF64_R_TYPE(r->r_info)) {
            case R_X86_64_RELATIVE:
                r->r_addend = p.vtov(px, r->r_addend);
                break;
            case R_X86_64_GLOB_DAT:
            case R_X86_64_JUMP_SLOT:
                r->r_offset = p.vtov(px, r->r_offset);
                break;
        }
    }
}


template<typename T> T *pack::_px_(ElfHdrT type) {
    for (auto& p : px) {
        if (p.src.hdr_type == type)
            return reinterpret_cast<T*>(p.mm.mem);
    }
    return nullptr;
}

struct patch_st *pack::_px_(ElfHdrT type) {
    for (auto& p : px) {
        if (p.src.hdr_type == type)
            return &p;
    }
    return nullptr;
}

bool pack::ins_hdr(ElfHdrT t, __u64 off, mmsz_t *mm) {
    for (auto& p : px)
        if (_contain_(p.dst.off, p.mm.sz, off)) {
            assert(p.mm.merge(off - p.dst.off, mm));
            // auto ehdr = _px_<Elf_Ehdr>(ElfHdrT::Ehdr);
            // ehdr->e_shnum   +=2;
            // ehdr->e_shstrndx+=2;
            shift(p.dst.off + off, mm->sz);
            return true;
        }
    return false;
}


void pack::patch_elf() {
    for (auto& p : px) {
        if (p.mm.is_alloc()) p.mm.alloc();

        switch (p.src.hdr_type) {   // entry
            case ElfHdrT::Ehdr:     PackPatch::ehdr(*this, p);  break;
            case ElfHdrT::Relatab:  PackPatch::rela(*this, p);  break;
            case ElfHdrT::Dyntab:   PackPatch::dyn(*this, p);   break;
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
