#include <algorithm>
#include <x86disass/disass.hpp>
#include "../include/rel.hh"

struct elf_bblock_t *RelInstr::get_elf_bb(std::shared_ptr<Elf> elf) {
    for (auto& tup : elf_tup) {
        if (tup.elf == elf)
            return &tup;
    }
    return nullptr;
}

void RelInstr::sort_patches() {
    patches.sort([](struct rel_patch_t& a, struct rel_patch_t& b) {
        return (a.out.off < b.out.off);
    });
}

void RelInstr::auto_patch() {
    auto& [elf, bblk] = s_tup;
    for (auto& bb : bblk.bb)
        if (_contain_(mm_base.off, mm_base.sz, bb.off))
            _rel_(RelT::InsRel, elf->off<void*>(bb.off), bb.off, bb.size);
}

static x_t_c xtc();

mmsz_t *RelInstr::init(__u64 align) {
    auto mm_src = &mm_base;
    auto mm_ret = mm_make_ret();

    sort_patches();
    for (auto& px : patches) {
        switch (REL_TYPE(px.t)) {
            case RelTypeT::Ins: rel_instr(mm_ret, &px);     break;
            case RelTypeT::Buf: rel_buffer(mm_ret, &px);    break;
        }
    }
    return mm_ret;
}

void RelInstr::rel_instr(mmsz_t *mm_ret, struct rel_patch_t *px) {
    auto elf = px->s_elf;
    d.iter(px->src.mem, px->src.sz, [&](__u64 i, insn_t& in) {
        if (in.IsNull()) return;

        __u64 off   = px->out.off - mm_base.off + i + off_align(px, px->out.off+i);
        void *ptr   = mm_ret->mem + off;
        if (!in.IsRip() && !in.IsPtr()) {
            memcpy(ptr, px->src.mem + i, in.size());
            return;
        }

        __u64 d_virt    = in.PtrAddr(elf->ftov(px->orig.off + i));
        __u64 d_off     = elf->vtof(d_virt);
        auto d_px = get_patch(elf, d_off);
        if (!d_px) {
            // .data / other
            __u64 imm = d_virt  - off_align(px, px->out.off+i);
            // auto ctx = (p->*hook_fn)(px, imm);
            // if (ctx.ok) imm = ctx.v;
            if (d_virt == -1) {
                memcpy(ptr, px->src.mem + i, in.size());
                return;
            }
            in.stick_in(ptr, imm, elf->ftov(px->out.off + i), ReAsmT::REL);
            return;
        }
        __u64 align = off_align(d_px, d_off) - off_align(px, px->out.off+i);
        __u64 imm   = d_virt + align;
        in.stick_in(ptr, imm, elf->ftov(px->out.off + i), ReAsmT::REL);
    });
}

__u64 RelInstr::offset(Elf *elf, __u64 v) {
    return off_align(v);
}
__u64 RelInstr::offset(std::shared_ptr<Elf> elf, __u64 v) {
    auto px = get_patch(elf, v);
    return ((!px) ? -1 : (v + off_align(px, v)));
}

void RelInstr::rel_buffer(mmsz_t *mm_ret, struct rel_patch_t *px) {
    memcpy(mm_ret->mem + px->out.off - mm_base.off + off_align(px, px->out.off), px->src.mem, px->src.sz);
}

mmsz_t *RelInstr::mm_make_ret() {
    return new mmsz_tup(PackPtrT::MMAP, mm_base.sz + off_align(mm_base.off + mm_base.sz));
}

__s64 RelInstr::off_align(__u64 v) {
    return off_align(nullptr, v);
}
__s64 RelInstr::off_align(struct rel_patch_t *rp, __u64 v) {
    __s64 r = 0;
    sort_patches();
    for (auto& p : patches)
        if (    (!rp || (!!rp && !!memcmp(&p, rp, sizeof(p))))
            &&  p.out.off <= v) {
            switch (REL_PATCH(p.t)) {
                case RelPatchT::Insert: r += p.src.sz; break;
                case RelPatchT::Remove: r -= p.src.sz; break;
            }
        }
    return r;
}

struct rel_patch_t *RelInstr::get_patch(std::shared_ptr<Elf> elf, __u64 orig) {
    for (auto& p : patches) if (p.s_elf == elf) {
        if (_contain_(p.orig.off, p.orig.sz, orig))
            return &p;
    }
    return nullptr;
}