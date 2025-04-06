#include <string.h>
#include <memory>
#include <unistd.h>
#include <linux/types.h>
#include <stdio.h>
#include <errno.h>
#include <vector>
#include <tuple>
#include <algorithm>
#include <fcntl.h>
#include <elflib/elf.hpp>

#include "./util.hh"
#include "./rel.hh"
#include "./bridge.hh"
#ifndef FREAK_PACK_H
#define FREAK_PACK_H

enum class ElfHdrT : __u8
{
    Ehdr, Phdr, Shdr, Symtab, Dyntab, Note, Reltab, Relatab, Strtab,
    Filling, Instr
};

struct patch_st {
    PackPtrT    src_type;
    struct {
        ElfHdrT     hdr_type;
        __u64 off, sz;
        std::shared_ptr<Elf> elf;
        void    *sc;
    } src;
    mmsz_t  mm;
    struct {
        __u64 off;
        __u64 h_pad, l_pad;
    } dst;
};

// LinkedList of patches
struct ll_px : public std::list<struct patch_st>
{
    struct patch_st *elf_add(ElfHdrT h_type, std::shared_ptr<Elf> elf, __u64 off, __u64 sz) {
        auto px = add(PackPtrT::Elf, elf->off<void*>(off), h_type, off, sz);
        px->src.elf = elf;
        return px;
    }
    struct patch_st *add(PackPtrT s_type, void *src, ElfHdrT h_type, __u64 off, __u64 sz) {
        auto ll = raw();
        struct patch_st px = {
            .src_type   = s_type,
            .src        = {
                .hdr_type = h_type,
                .off    = off,
                .sz     = sz,
            },
            .mm = {
                .t      = s_type,
                .mem    = src,
                .sz     = sz,
            },
            .dst = { .off = off },
        };
        // if (s_type == PackPtrT::SC) px.src.sc = src;
        ll->push_back(px);
        return &ll->back();
    }
private:
    std::list<struct patch_st> *raw() {
        return dynamic_cast<std::list<struct patch_st> *>(this);
    }
};

class pack {
    std::shared_ptr<Elf>        s_elf;
    std::list<RelInstr>         rel;
    ll_px                       px;
public:
    pack() = delete;
    pack(Elf *elf) : s_elf{elf} {
        Elf_Ehdr *ehdr = s_elf->ehdr;
        px.elf_add(ElfHdrT::Ehdr, s_elf, 0, ehdr->e_ehsize);
        px.elf_add(ElfHdrT::Phdr, s_elf, ehdr->e_phoff, ehdr->e_phnum * ehdr->e_phentsize);
        px.elf_add(ElfHdrT::Shdr, s_elf, ehdr->e_shoff, ehdr->e_shnum * ehdr->e_shentsize);
        px.elf_add(ElfHdrT::Dyntab, s_elf, s_elf->dyn.src.off, s_elf->dyn.src.size);

        for (auto& stab : s_elf->symtab) {
            px.elf_add(ElfHdrT::Symtab, s_elf, stab.src.off, stab.src.sec->sh_size);
        }
        for (auto& rtab : s_elf->relatab) {
            px.elf_add(ElfHdrT::Relatab, s_elf, rtab.off, rtab.size);
        }
        for (auto& rtab : s_elf->reltab) {
            px.elf_add(ElfHdrT::Reltab, s_elf, rtab.off, rtab.size);
        }
        fill();
    }
    RelInstr *get_rel(std::shared_ptr<Elf> _elf, __u64 off);
    RelInstr *get_rel(Elf *_elf, __u64 off);
    void patch_elf();
    void merge_elf(Elf *elf);
    void fill();
    bool rel_exec();
    struct hook_ctx hook_fn(struct rel_patch_t *rx, __u64 imm);
    void sort_px();
    struct patch_st *slit_sub_px(__u64 off, __u64 sz);
    struct patch_st *px_orig_off(__u64 off);
    struct patch_st *px_orig_virt(__u64 virt);
    void init();
    void shift(__u64 off, __u64 sz);
    __s8 make(char *file);
};
#endif