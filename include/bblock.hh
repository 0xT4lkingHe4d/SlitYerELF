#include <linux/types.h>
#include <tuple>
#include <algorithm>

#include <x86disass/disass.hpp>
#include <elflib/elf.hpp>
#ifndef FREAK_BBLOCK_H
#define FREAK_BBLOCK_H

typedef std::vector<std::tuple<bool, __u64>> iter_vec_t;
class iter_t : public iter_vec_t {
public:
    bool done(__u64 off);
    void sort();
    bool has(__u64 off);
    void add(__u64 off);
    void del(__u64 i);
    void del(__u64 l, __u64 r);
private:
    iter_vec_t& raw() {
        return *dynamic_cast<iter_vec_t*>(this);
    }
};

struct bblock_st {
    __u64 off, size;
};

struct plt_st {
    __u64       off;
    union {
        Elf_Rel     *rel;
        Elf_Rela    *rela;
    };
    elf_rela_t      *rtab;
    Elf_Sym         *sym;
    elf_symtab_t    *stab;
};

class BBlock {
    Disass  d;
    iter_t  q;
    std::shared_ptr<Elf>        elf;
    std::vector<__u64>          sz_vec;

public:
    std::map<__u64, struct plt_st> plt_map;
    std::list<struct bblock_st> bb;
    
    BBlock() = delete;
    BBlock(Elf *_elf) { BBlock(std::shared_ptr<Elf>{_elf}); }
    BBlock(std::shared_ptr<Elf> _elf) : elf{_elf}, d() {
        init();
        for (auto& [e, off] : q)
            bb.push_back((struct bblock_st){
                .off=off, .size=size(off)
            });
    }
    ~BBlock() = default;

    __u64 size(__u64 off);
private:
    void init();
    void del_double();
    void init_plt();
    struct plt_st *plt_by_ndx(__u64 i);
    __u64 chop_instr_ptr();
    void init_sz_vec();
    void init_iter_vec();
};
#endif
