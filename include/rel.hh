#include <assert.h>
#include <elflib/elf.hpp>

#ifndef FREAK_REL_H
#define FREAK_REL_H
#include "./bblock.hh"
#include "./bridge.hh"
#include "./util.hh"

#define REL_TYPE(t) (static_cast<RelTypeT>((static_cast<__u8>((t)) & 0b100)))
#define REL_PATCH(t) (static_cast<RelPatchT>((static_cast<__u8>((t)) & 0b11)))

enum class RelTypeT : __u8
{
    Buf=0, Ins=4
};

enum class RelPatchT : __u8
{
    Rel=1, Insert=2, Remove=3
};

enum class RelT : __u8
{
    BufRel=1, BufInsert=2, BufRemove=3,
    InsRel=5, InsInsert=6, InsRemove=7
};

struct rel_hook_st {
    __u64 src_off, dst_off;
    std::shared_ptr<Elf> elf;
    rel_hook_st(__u64 s, __u64 d, std::shared_ptr<Elf> _elf)
        : src_off{s}, dst_off{d}, elf{_elf} {}
};

struct rel_patch_t {
    RelT    t;
    mmsz_t  src;
    __s64 align;
    std::shared_ptr<Elf>            s_elf; 
    std::list<struct rel_hook_st>   hooks;
    struct {
        __u64 off;
    } out;
    struct {
        __u64 off, sz;
    } orig;
    std::list<struct rel_patch_t>   ll;
};

struct elf_bblock_t {
    elf_bblock_t() = delete;
    elf_bblock_t(std::shared_ptr<Elf> _elf)
        : elf{_elf}, bblk{std::move(BBlock(_elf))} {}

    std::shared_ptr<Elf>    elf;
    BBlock                  bblk;
};
class pack;
typedef hook_ctx (pack::*RelPluginFn)(struct rel_patch_t *rx, __u64 imm);

class RelBits;

class RelInstr {
    pack        *p;
protected:
    RelPluginFn hook_fn;
    Disass      d;
    mmsz_t      mm_base;

    std::list<struct elf_bblock_t>      elf_tup;
    std::list<struct rel_patch_t>       patches;

public:
    friend class RelBits;
    struct elf_bblock_t s_tup;
    struct {
        __u64 off, sz;
    } src;
    RelInstr() = delete;
    RelInstr(pack *p_obj, RelPluginFn fn, __u64 off, std::shared_ptr<Elf> elf, mmsz_t& px_mm)
            : p{p_obj}, hook_fn{fn}, mm_base{px_mm}, src{off, px_mm.sz}, s_tup(elf) {
        add_elf(elf);
        mm_base.off = off;
        mm_base.alloc();
    }
    bool hook(struct rel_patch_t& rx, __u64 s, Elf *elf, __u64 d);

    struct rel_patch_t& _rel_(RelT t, void *ptr, __u64 dst, __u64 size);
    struct rel_patch_t& _rel_(RelT t, void *ptr, __u64 dst, __u64 size, __s64 align);
    
    struct rel_patch_t& _rel_(std::list<struct rel_patch_t>& ll, RelT t, void *ptr, __u64 dst, __u64 size) {
        auto elf_bb = ptr_to_elf(ptr);
        auto elf = (!!elf_bb) ? elf_bb->elf : nullptr;

        struct rel_patch_t rx = {
            .t      = t,
            .src    = {
                .t      = (!!elf) ? PackPtrT::Elf : PackPtrT::SC,
                .mem    = ptr,
                .sz     = size
            },
            .s_elf  = (!!elf) ? elf : nullptr,
            .out    = { .off = dst, },
            .orig   = {
                .off    = (!!elf) ? (__u64)ptr - (__u64)elf->map : -1,
                .sz     = size,
            },
        };
        
        return ll.emplace_back(rx);
    }
    struct rel_patch_t *_rx_(__u64 off) {
        return get_patch(s_tup.elf, off);
    }
    bool has(__u64 off);
    mmsz_t *init() { return init(0); }
    mmsz_t *init(__u64 align);
    void each_px(mmsz_t *mm, std::list<struct rel_patch_t>& ll);
    void sort_patches(std::list<struct rel_patch_t>& ll);
    void auto_patch();  // Exec PHDR > BBlocks to ll_px
    __u64 offset(std::shared_ptr<Elf> elf, __u64 v);
    __u64 virt(std::shared_ptr<Elf> elf, __u64 v);
    struct elf_bblock_t *ptr_to_elf(void *ptr); // Find ELF containing ~ptr at ELF+?
    void xtc_insn();
    void rel_instr(mmsz_t *mm_ret, struct rel_patch_t& px);
    void ins_instr(mmsz_t *mm_ret, struct rel_patch_t& px);
    void rel_buffer(mmsz_t *mm_ret, struct rel_patch_t& px);
    void add_elf(std::shared_ptr<Elf> elf);
    struct elf_bblock_t *get_elf_bb(std::shared_ptr<Elf> elf);
    struct rel_patch_t *get_patch(std::shared_ptr<Elf> elf, __u64 orig);
    __s64 off_align(__u64 v);
    __s64 off_align(struct rel_patch_t *rp, __u64 v);
    __s64 each_off_align(std::list<struct rel_patch_t>& ll, struct rel_patch_t *rp, __u64 v);
    mmsz_t *mm_make_ret();
};

typedef struct {
    __u64 off;
    __u64 virt;
} off_virt_t;

// Its a fucking mess
class RelBits {
public:
    typedef RelBits R;
    struct Ctx {
        RelInstr&           r;
        struct rel_patch_t& rx;
        insn_t&             in;
        __u64               i;
        void *ptr;
        struct {
            __u64 off, virt;
        } imm;
        __u64   offset;

        // RelInstr >> Patch >> insn & offset
        Ctx(RelInstr& _r, struct rel_patch_t& _rx, insn_t& _in, __u64 _i)
            : r{_r}, rx{_rx}, in{_in}, i{_i} {}

        Ctx& operator<<(void *mem) {
            ptr = mem + R::out_off(*this);
            return *this;
        }
    };
    /* Where shall it lay now */
    static __u64 out_off(RelBits::Ctx& ctx) {
        auto rx = ctx.rx;
        __u64 align = ctx.r.off_align(&rx, rx.out.off + ctx.i);
        return rx.out.off - ctx.r.mm_base.off + ctx.i + align;
    }
    /* Where was it supposed to point to */
    static off_virt_t imm(RelBits::Ctx& ctx) {
        auto rx     = ctx.rx;
        auto elf    = ctx.rx.s_elf;
        __u64 virt  = ctx.in.PtrAddr(elf->ftov(rx.orig.off + ctx.i));
        __u64 off   = elf->vtof(virt);

        return (off_virt_t){ .off=off, .virt=virt };
    }
    /* Where Shall it point now */
    static __u64 ptr(RelBits::Ctx& ctx) {
        auto rx     = ctx.rx;
        auto elf    = ctx.rx.s_elf;
        auto [f, v] = imm(ctx);

        __u64 align = ctx.r.off_align(&rx, rx.out.off+ctx.i);
        auto dst_px = ctx.r.get_patch(elf, f);
        return (!!dst_px)
            ? (v + ctx.r.off_align(dst_px, f) - align)
            : (v - align);
    }

    static __u8 stick_ya(RelBits::Ctx& ctx, __u64 imm, ReAsmT t) {
        return ctx.in.stick_in(ctx.ptr, imm, ctx.rx.s_elf->ftov(ctx.rx.out.off + ctx.i), t);
    }
};
#endif