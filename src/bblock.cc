#include "../include/bblock.hh"

void BBlock::init() {
    init_sz_vec();      // To find size of basic blocks
    init_plt();         // plt_map
    init_iter_vec();    // init Basic Block clues
    chop_instr_ptr();   // find more clues at each RIP/PTR instr
    del_double();       // from interleaving Basci Blocks remove the smaller/internal ones
}

void BBlock::init_plt() {
    auto dynsym = elf->dynsym();
    if (!dynsym) return;

    auto plt_sec = elf->PLT();
    if (!plt_sec) return;
    __u64 plt_off   = plt_sec->Offset();
    __u64 plt_sz    = size(plt_off);

    d.iter(elf->off<void*>(plt_off), plt_sz, [&](__u64 i, insn_t& in) {
        // JMP [ GOT + n*8 ]
        if (!in.IsJump() && in.PtrAddr() == -1) return;
        __u64 virt  = in.PtrAddr(elf->ftov(plt_off + i));
        __u64 e_off = (plt_off + i) & ~plt_sec->sh_addralign;
        
        foreach_rela_tab(elf, rtab, r) {
            switch (ELF64_R_TYPE(r->r_info)) {
                case R_X86_64_GLOB_DAT:
                case R_X86_64_JUMP_SLOT:
                    if (r->r_offset == virt) {
                        auto sym = &dynsym->tab[ELF64_R_SYM(r->r_info)];
                        plt_map[virt] = {
                            .off    = e_off,
                            .rela   = r,    .rtab = &rtab,
                            .sym    = sym,  .stab = dynsym,
                        };
                    }
            }
        }
    });
}

__u64 BBlock::chop_instr_ptr() {
    auto got = elf->GOT();
    __u64 ret = 0;
    for (auto& [ok, off] : q) if (!ok) {
        *&ok = true;
        auto p = elf->vtoph(off);
        if (!p || !p->Is(PF_X)) continue;

        void *ptr   = elf->off<void*>(off);
        __u64 sz    = size(off);
        d.iter(ptr, sz, [&](__u64 i, insn_t& in) {
            if (in.IsNull() || in.IsShortBranch() || (!in.IsPtr() && !in.IsRip())) return;
            __u64 virt  = in.PtrAddr(elf->ftov(off + i));
            __u64 off   = elf->vtof(virt);

            if (virt != -1 && elf->VirtPerm(virt) & PF_X) {
                q.add(off);
                sz_vec.push_back(off);
                ret++;
            }
        });
    }
    q.sort();
    std::sort(sz_vec.begin(), sz_vec.end());
    return ret;
}

struct plt_st *BBlock::plt_by_ndx(__u64 i) {
    for (auto& [_, v] : plt_map)
        if (i == ((__u64)v.rela - (__u64)v.rtab->ptr) / sizeof(Elf_Rela))
            return &v;
    return nullptr;
}

__u64 BBlock::size(__u64 off) {
    for (__u64 i : sz_vec) if (i > off) return i - off;
    return 0;
}

void BBlock::del_double() {
    _start:
    q.sort();
    for (__u64 l=0; l < q.size(); l++) {
        auto& [_, v] = q[l];
        __u64 i = l+1;
        for (__u64 iv = std::get<__u64>(q[i]); i < q.size(); i++)
            if (!(_contain_(v, size(v), iv))) break;

        if (i > l+1) {  // There're doubles
            q.del(l+1, i);
            goto _start;
        }
    }
}

void BBlock::init_iter_vec() {
    q.add(elf->ehdr->e_entry);

    /* EACH exec Section */
    foreach_shdr(elf, sec) if (sec->Is(PF_X))
        q.add(sec->sh_offset);
    
    /* EACH exec SYMBOL */
    for (auto& stab : elf->symtab)
        foreach_sym(&stab, sym) {
            __u64 v = sym->st_value;
            if (!!v && elf->VirtPerm(v) & PF_X)
                q.add(elf->vtof(v)); 
        }
        
    /* EACH exec DYNAMIC */
    foreach_dynamic(elf, d) {
        __u64 v = d->d_un.d_val;
        if (elf->VirtPerm(v) & PF_X)
            q.add(elf->vtof(v));
    }
    q.sort();
}


void BBlock::init_sz_vec() {
    foreach_phdr(elf, p) {
        sz_vec.push_back(p->p_offset);
        sz_vec.push_back(p->p_offset + p->p_filesz);
    }
    foreach_shdr(elf, s) {
        sz_vec.push_back(s->sh_offset);
        sz_vec.push_back(s->sh_offset + s->sh_offset);
    }

    for (auto& stab : elf->symtab) {
        if (stab.t & SHT_SYMTAB)
            foreach_sym(&stab, sym) if (!!sym->st_value)
                sz_vec.push_back(elf->vtof(sym->st_value));
    }

    foreach_rela_tab(elf, rtab, r)  sz_vec.push_back(r->r_offset);
    foreach_rel_tab(elf, rtab, r)   sz_vec.push_back(r->r_offset);

    std::sort(sz_vec.begin(), sz_vec.end());
}

void iter_t::sort() {
    std::sort(begin(), end());
}

void iter_t::add(__u64 off) {
    if (!has(off)) emplace_back(false, off);
}
void iter_t::del(__u64 i) {
    erase(std::next(begin(), i));
    sort();
}
void iter_t::del(__u64 l, __u64 r) {
    erase(std::next(begin(), l), std::prev(end(), size() - r));
    sort();
}

bool iter_t::has(__u64 off) {
    for (auto& [ok, e] : raw()) if (e == off) return true;
    return false;
}

bool iter_t::done(__u64 off) {
    for (auto& [ok, e] : raw()) if (e == off) return ok;
    return false;
}