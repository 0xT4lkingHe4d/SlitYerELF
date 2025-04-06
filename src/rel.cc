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
    xtc_insn();
    for (auto& px : patches) {
        switch (REL_TYPE(px.t)) {
            case RelTypeT::Ins:
                switch (REL_PATCH(px.t)) {
                    case RelPatchT::Rel:    rel_instr(mm_ret, px);  break;
                    case RelPatchT::Insert: ins_instr(mm_ret, px);  break;
                }
            case RelTypeT::Buf: rel_buffer(mm_ret, px);    break;
        }
    }
    _hexdump(mm_ret->mem, mm_ret->sz);
    return mm_ret;
}

void RelInstr::xtc_insn() {
    // for (auto& px : patches) {
    //     auto elf = px.s_elf;
    //     if (REL_TYPE(px.t) == RelTypeT::Ins) {
    //         // switch (REL_PATCH(px.t)) {
    //         //     case RelPatchT::Rel:
    //         //     {
    //         d.iter(px.src.mem, px.src.sz, [&](__u64 i, insn_t& in) {
    //             if (!in.IsPtr() && !in.IsRip()) return;
    //             /**
    //              * Where was it supposed to be */
    //             __u64 imm_virt  = in.PtrAddr(elf->ftov(px.orig.off + i));
    //             __u64 imm_off   = elf->vtof(imm_virt);

    //             __u64 src_align = off_align(&px, px.out.off+i);
    //             // __u64 off = px.out.off - mm_base.off + i + src_align;
    //             auto dst_px     = get_patch(elf, imm_off);
    //             if (!!dst_px) {
    //                 __u64 dst_align = off_align(dst_px, imm_off);
    //                 for (__u8 i = 0; i < in.OperCount(); i++)
    //                     if (in[i]->IsType(OperType::PTR)) {
    //                         __u32 sz = in[i]->size();
    //                         __u64 align = (src_align > dst_align) ? src_align - dst_align : dst_align - src_align;
    //                         __s64 imm = in.PtrAddr();

    //                         // if (    (imm > 0 && imm + align > (1llu << (sz-1)))
    //                         //     ||  (imm <= 0 && imm - align < -(1llu << (sz-1))-1)) {
    //                             prf(BYLW"IMM[%lx] SRC ALIGN[%lx] , DST ALIGN[%lx] MAX[%lx]\n"CRST, imm, src_align, dst_align, 1-(1llu << (sz-1)));
    //                             in.Print();
    //                             pr("");
    //                         // }
    //                         break;
    //                     }
    //             }
    //         });
    //         //     }
    //         //     break;
    //         //     default: asm("int3");
    //         // }
    //     }
    // }
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
        memset(ctx.ptr, u'\x90', in.size());
    });
    pr("BLANK FOR NOW");
}

__u64 RelInstr::offset(Elf *elf, __u64 v) {
    return off_align(v);
}

__u64 RelInstr::offset(std::shared_ptr<Elf> elf, __u64 v) {
    auto px = get_patch(elf, v);
    return ((!px) ? -1 : (v + off_align(px, v)));
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