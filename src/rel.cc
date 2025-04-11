#include <linux/types.h>
#include <assert.h>
#include <algorithm>
#include <x86disass/disass.hpp>
#include "../include/rel.hh"

bool RelInstr::hook(struct rel_patch_t& rx, __u64 s, Elf *elf, __u64 d) {
    auto elf_bb = ptr_to_elf(elf->map);
    if (!elf_bb) return false;

    rx.hooks.emplace_back(s, d, elf_bb->elf);
    return true;
}

struct rel_patch_t& RelInstr::_rel_(RelT t, void *ptr, __u64 dst, __u64 size) {
    return _rel_(patches, t, ptr, dst, size);
}

struct rel_patch_t& RelInstr::_rel_(RelT t, void *ptr, __u64 dst, __u64 size, __s64 align) {
    auto rx = _rel_(patches, t, ptr, dst, size);
    rx.align = align;
}

struct elf_bblock_t *RelInstr::get_elf_bb(std::shared_ptr<Elf> elf) {
    for (auto& tup : elf_tup) {
        if (tup.elf == elf) return &tup;
    }
    return nullptr;
}

void RelInstr::sort_patches(std::list<struct rel_patch_t>& px) {
    px.sort([](struct rel_patch_t& a, struct rel_patch_t& b) {
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
    auto mm_ret = mm_make_ret();
    each_px(mm_ret, patches);
    _hexdump(mm_ret->mem, mm_ret->sz);
    return mm_ret;
}

void RelInstr::each_px(mmsz_t *mm, std::list<struct rel_patch_t>& ll) {
    sort_patches(ll);
    for (auto& px : ll) {
        if (!px.ll.empty()) each_px(mm, px.ll);
        switch (REL_TYPE(px.t)) {
            case RelTypeT::Ins:
                switch (REL_PATCH(px.t)) {
                    case RelPatchT::Rel:    rel_instr(mm, px);  break;
                    case RelPatchT::Insert: ins_instr(mm, px);  break;
                }
            break;
            case RelTypeT::Buf: rel_buffer(mm, px);    break;
        }
    }
}
typedef RelBits R;

void RelInstr::rel_instr(mmsz_t *mm_ret, struct rel_patch_t& px) {
    auto elf = px.s_elf;

    d.iter(px.src.mem, px.src.sz, [&](__u64 i, insn_t& in) {
        if (in.IsNull()) return;
        auto ctx = R::Ctx(*this, px, in, i) << mm_ret->mem;

        void *ptr = ctx.ptr;
        if (!in.IsRip() && !in.IsPtr()) {
            memcpy(ptr, px.src.mem + i, in.size());
            return;
        }
        /* Where was it supposed to go */
        auto [imm_off, imm_virt] = R::imm(ctx);
        auto dst_px = get_patch(elf, imm_off);
        if (!dst_px) {
            /* Outside of _rel_'d PHDR */
            __u64 imm = R::ptr(ctx);
            if (imm_virt == -1) {
                memcpy(ptr, px.src.mem + i, in.size());
                return;
            }
            R::stick_ya(ctx, imm, ReAsmT::REL);
            return;
        }
        /* Where is the ptr now */
        __u64 imm = R::ptr(ctx);
        R::stick_ya(ctx, imm, ReAsmT::REL);
    });
}

void RelInstr::ins_instr(mmsz_t *mm_ret, struct rel_patch_t& px) {
    d.iter(px.src.mem, px.src.sz, [&](__u64 i, insn_t& in) {
        auto ctx = R::Ctx(*this, px, in, i) << mm_ret->mem;
        prf(BRED "[+++]" CRST "0x%lx\n", R::out_off(ctx));
        memset(ctx.ptr, u'\x90', in.size());
    });
    pr("BLANK FOR NOW");
}

__u64 RelInstr::offset(std::shared_ptr<Elf> elf, __u64 v) {
    auto px = get_patch(elf, v);
    return ((!px) ? -1 : (v + off_align(px, v)));
}

__u64 RelInstr::virt(std::shared_ptr<Elf> elf, __u64 v) {
    auto px = get_patch(elf, elf->vtof(v));
    return ((!px) ? -1 : (v + off_align(px, elf->vtof(v))));
}

void RelInstr::rel_buffer(mmsz_t *mm_ret, struct rel_patch_t &px) {
    memcpy(mm_ret->mem + px.out.off - mm_base.off + off_align(&px, px.out.off), px.src.mem, px.src.sz);
}

mmsz_t *RelInstr::mm_make_ret() {
    return new mmsz_tup(PackPtrT::MMAP, mm_base.sz + off_align(mm_base.off + mm_base.sz));
}

__s64 RelInstr::off_align(__u64 v) {
    return off_align(nullptr, v);
}
__s64 RelInstr::off_align(struct rel_patch_t *rp, __u64 v) {
    return each_off_align(patches, rp, v);
}

__s64 RelInstr::each_off_align(std::list<struct rel_patch_t>& ll, struct rel_patch_t *rp, __u64 v) {
    __s64 r = 0;
    sort_patches(ll);
    for (auto& p : ll) {
        if (!p.ll.empty()) r += each_off_align(p.ll, rp, v);
        if (    (!rp || (!!rp && !!memcmp(&p, rp, sizeof(p))))
            &&  p.out.off <= v) {   //  && (!rp || (!!rp && REL_PATCH(rp->t) != RelPatchT::Insert))
            switch (REL_PATCH(p.t)) {
                case RelPatchT::Insert: r += p.src.sz; break;
                case RelPatchT::Remove: r -= p.src.sz; break;
            }
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

struct elf_bblock_t *RelInstr::ptr_to_elf(void *ptr) {
    for (auto& st : elf_tup)
        if (_contain_(st.elf->map, st.elf->size, ptr))
            return &st;
    return nullptr;
}

void RelInstr::add_elf(std::shared_ptr<Elf> elf) {
    elf_tup.emplace_back(elf);
}
bool RelInstr::has(__u64 off) {
    return _contain_(mm_base.off, mm_base.sz, off);
}