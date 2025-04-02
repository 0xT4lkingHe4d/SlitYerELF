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

struct rel_patch_t {
    RelT    t;
    mmsz_t  src;
    std::shared_ptr<Elf> s_elf;
    struct {
        __u64 off;
    } out;
    struct {
        __u64 off, sz;
    } orig;
};

struct elf_bblock_t {
    elf_bblock_t() = delete;
    elf_bblock_t(std::shared_ptr<Elf> _elf) : elf{_elf}, bblk{std::move(BBlock(_elf))} {}
    std::shared_ptr<Elf>    elf;
    BBlock                  bblk;
};
class pack;
typedef hook_ctx (pack::*RelPluginFn)(struct rel_patch_t *rx, __u64 imm);

class RelInstr {
    pack        *p;
    RelPluginFn hook_fn;
    Disass      d;
    mmsz_t      mm_base;

    std::list<struct elf_bblock_t>      elf_tup;
    std::list<struct rel_patch_t>       patches;

public:
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
    struct elf_bblock_t *ptr_to_elf(void *ptr) {
        for (auto& st : elf_tup) {
            if (_contain_(st.elf->map, st.elf->size, ptr))
                return &st;
        }
        return nullptr;
    }
    struct elf_bblock_t *get_elf_bb(std::shared_ptr<Elf> elf);
    void add_elf(std::shared_ptr<Elf> elf) {
        elf_tup.emplace_back(elf);
    }
    bool has(__u64 off) {
        return _contain_(mm_base.off, mm_base.sz, off);
    }
    struct rel_patch_t& _rel_(RelT t, void *ptr, __u64 dst, __u64 size) {
        return _rel_(patches, t, ptr, dst, size);
    }
    
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
    mmsz_t *init() { return init(0); }
    mmsz_t *init(__u64 align);
    void sort_patches();
    void auto_patch();
    __u64 offset(Elf *elf, __u64 v);
    __u64 offset(std::shared_ptr<Elf> elf, __u64 v);
    void rel_instr(mmsz_t *mm_ret, struct rel_patch_t *px);
    void rel_buffer(mmsz_t *mm_ret, struct rel_patch_t *px);
    struct rel_patch_t *get_patch(std::shared_ptr<Elf> elf, __u64 orig);
    __s64 off_align(__u64 v);
    __s64 off_align(struct rel_patch_t *rp, __u64 v);
    mmsz_t *mm_make_ret();
};
#endif