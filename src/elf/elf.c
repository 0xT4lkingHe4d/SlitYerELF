// #include "./disass/include/uapi.h"
#include "../../include/elf.h"
#include "../../include/utils.h"

static __u8 *elf_get_file(elf_t *elf);
static __s8 elf_init_symtabs(elf_t *elf);
static __s8 elf_init_versym(elf_t *elf);
static Elf_Dyn *elf_set_dynamic(elf_t *elf);
static int init_elf(elf_t *elf);
static int elf_check_supported(elf_t *elf);
static __s8 elf_set_rela(elf_t *elf);
static __s8 elf_init_got_plt(elf_t *elf);
 
 #define prf_elf(elf, t, str, ...)		\
		prf(t color(BRED, "[ELF]\t") str " - [%s]\n", __VA_ARGS__, elf_get_file(elf))

#define pr_elf(elf, t, str)				\
		prf(t color(BRED, "[ELF]\t") str " - [%s]\n", elf_get_file(elf))

int new_elf(__u8 *f, elf_t *elf) {
	if (load_elf(f, elf) == -1)	return -1;
	if (init_elf(elf) == -1)	return -1;
	return 0;
}

int load_elf(__u8 *f, elf_t *elf) {
	struct stat stats = {0};

	int fd = open(f, O_RDONLY);
	if (fd == -1) return -1;

	if (stat(f, &stats) == -1)
		return -1;

	elf->file = f;
	elf->size = stats.st_size;
	elf->map = mmap(0, elf->size, PROT_READ|PROT_WRITE, MAP_PRIVATE, fd, 0);
	elf->mm_ehdr.sz = sizeof(Elf_Ehdr);
	
	if (elf->map == MAP_FAILED) return -1;

	close(fd);
	return 0;
}

__s8 is_elf(elf_t *elf) {
	__u8 *ptr =  elf->map;
	return (ptr[0] == '\x7f' && ptr[1] == 'E' && ptr[2] == 'L' && ptr[3] == 'F');
}

static __u8 *elf_get_file(elf_t *elf) {
	return ((!elf) ? (color(BBLUE, "[null]")) : (!elf->file) ? (color(BBLUE, "[----]")) : elf->file);
}

static int elf_check_supported(elf_t *elf) {
	if (elf->ehdr->e_machine != EM_X86_64) {
		pr_elf(elf, PR_ERR, "ELF is not a x86_64 - " color(BYLW, "[The only supported]"));
		return 0;
	}
	if (elf->ehdr->e_type != ET_DYN && elf->ehdr->e_type != ET_REL) {
		pr_elf(elf, PR_ERR, "ELF Type is not ET_DYN nor ET_REL (PIE)");
		return 0;
	}
	return 1;
}

#define elf_has_phdr(elf)	((elf)->ehdr->e_phoff && (elf)->ehdr->e_phnum)
#define elf_has_shdr(elf)	((elf)->ehdr->e_shoff && (elf)->ehdr->e_shnum)

static int init_elf(elf_t *elf) {
	void *map = elf->map;
	if (!elf_check_supported(elf))	return -1;

	if (elf_has_phdr(elf)) {
		elf->phdr.tab = (Elf_Phdr*)( map + (elf->ehdr->e_phoff) );
		foreach_phdr(elf, p)
			if (p->p_offset + p->p_filesz > elf->size) {
				pr_elf(elf, PR_ERR, "Overflowing Phdr");
				return -1;
			}
	}

	if (elf_has_shdr(elf)) {
		elf->sec.tab = (Elf_Shdr*)( map + (elf->ehdr->e_shoff) );
		elf->sec.strtab_shdr = &elf->sec.tab[elf->ehdr->e_shstrndx];
		elf->sec.str = (map + elf->sec.strtab_shdr->sh_offset);
	} else {
		pr_elf(elf, PR_WARN, "There is no Shdr");
	}

	if (!elf_set_dynamic(elf)) {
		pr_elf(elf, PR_WARN, "Failed elf_set_dynamic");
	}
	if (elf_init_symtabs(elf) == -1)	return -1;
	if (elf_set_rela(elf) == -1)		return -1;
	if (elf_init_versym(elf) == -1)		return -1;
	if (elf_init_got_plt(elf) == -1)	return -1;

	return 0;
}

static Elf_Dyn *elf_set_dynamic(elf_t *elf) {
	if (!elf || !elf->map) return NULL;
	if (!elf_has_phdr(elf)) {
		if (!elf_has_shdr(elf)) return NULL;

		foreach_shdr(elf, sec) {
			if (sec->sh_type == SHT_DYNAMIC) {
				elf->dynamic.hdr_sz = sec->sh_size;
				elf->dynamic.sec	= sec;
				elf->dynamic.tab	= (Elf_Dyn*)(elf->map + sec->sh_offset);
				return elf->dynamic.tab;
			}
		}
	} else {
		foreach_phdr(elf, p) if (p->p_type == PT_DYNAMIC) {
			elf->dynamic.hdr_sz = p->p_filesz;
			elf->dynamic.phdr	= p;
			elf->dynamic.tab	= (Elf_Dyn*)(elf->map + p->p_offset);

			if (elf_has_shdr(elf)) {
				foreach_shdr(elf, sec)
					if (sec->sh_type == SHT_DYNAMIC && sec->sh_offset == p->p_offset) {
						elf->dynamic.sec = sec;	break;
					}
			}
			return elf->dynamic.tab;
		}
	}
	return NULL;
}

static __s8 elf_init_versym(elf_t *elf) {
	gnu_ver_t *ver	= &elf->gnu_ver;
	symtab_t *dyntab	= elf_get_dyntab(elf);

	if (!!elf->dynamic.tab && !!dyntab) {
		foreach_dynamic(elf, dyn) {
			__u64 v		= dyn->d_un.d_val;
			void *ptr	= elf->map + v;
			switch (dyn->d_tag) {
				case DT_VERSYM:
					ver->sym		= ptr;
					ver->sym_off	= v;
					ver->mm_sym.sz	= sizeof(__u16) * (_elf_symtab_sz(dyntab) / sizeof(Elf_Sym));
					break;
				case DT_VERNEED:
					ver->need		= ptr;
					ver->need_off	= v;
					break;
				case DT_VERNEEDNUM:	ver->num = v;	break;
			}
		}
		return 0;
	}
	return -1;
}

static __s8 elf_set_rela(elf_t *elf) {
	llist_new(&elf->ll_rela);
	llist_new(&elf->ll_rel);

	if (!!elf->phdr.tab) {
		if (!elf->dynamic.tab) return -1;

		rela_t plt = {0}, rel = { .t = DT_REL }, rela = { .t = DT_RELA };

		foreach_dynamic(elf, e) {
			void *ptr = (elf->map + elf_vtof(elf, e->d_un.d_ptr));
			__u64 v = e->d_un.d_val;

			switch (e->d_tag) {
				case DT_PLTREL:		plt.t		= v;			break;
				case DT_PLTRELSZ:	plt.mm.sz	= v;			break;
				case DT_JMPREL:		plt.off=v; plt.ptr=ptr;		break;
				case DT_REL:		rel.off=v; rel.ptr=ptr;		break;
				case DT_RELSZ:		rel.mm.sz	= v;			break;
				case DT_RELA:		rela.off=v; rela.ptr=ptr;	break;
				case DT_RELASZ:		rela.mm.sz	= v;			break;
			}
		}
		if (_rel_check(&rel))	llist_add(&elf->ll_rel, F_LL_MALLOC, &rel, sizeof(rel));
		if (_rel_check(&rela))	llist_add(&elf->ll_rela, F_LL_MALLOC, &rela, sizeof(rela));
		if (_rel_check(&plt)) {
			llist_t *ll = elf_get_ll_rel(elf, plt.t);
			if (!ll) return -1;
			llist_add(ll, F_LL_MALLOC, &plt, sizeof(plt));
		}
	} else if (!!elf->sec.tab) {
		foreach_shdr(elf, sec) {
			llist_t *ll = elf_get_ll_rel(elf, sec->sh_type);
			if (!ll) continue;

			rela_t st = {
				.t		= sec->sh_type,
				.sec	= sec,
				.rel	= elf->map + sec->sh_offset,
			 };
			llist_add((&elf->ll_rela), F_LL_MALLOC, &st, sizeof(rela_t));
		}
	} else return -1;

	return 0;
}

static __s8 elf_init_symtabs(elf_t *elf) {
	if (!elf_has_shdr(elf)) return -1;
	llist_new(&elf->ll_sym);

	foreach_shdr(elf, sec) {
		if (sec->sh_type != SHT_DYNSYM && sec->sh_type != SHT_SYMTAB)
			continue;
 
		symtab_t sym = {
			.off	= sec->sh_offset,
			.t		= sec->sh_type,
			.sec	= sec,
			.mm_tab	= {
				.mem	= elf->map + sec->sh_offset,
				.sz		= sec->sh_size,
			},
			.mm_str	= {
				.mem	= (__u8*)(elf->map + elf->sec.tab[sec->sh_link].sh_offset),
				.sz		= elf->sec.tab[sec->sh_link].sh_size,
			},
		};
		if (!llist_add(&elf->ll_sym, F_LL_MALLOC, &sym, sizeof(sym)))
			return -1;
	}

	return 0;
}

Elf_Shdr *elf_sec_by_name(elf_t *elf, __u8 *str) {
	foreach_shdr(elf, sec) {
		if (!_strncmp(elf_sec_name(elf, sec), str, strlen(str)+1))
			return sec;
	}
	return NULL;
}

__u64 elf_off_to_virt(elf_t *elf, __u64 off) {
	foreach_phdr(elf, p) {
		if (_contain_(p->p_offset, p->p_filesz, off))
			return p->p_vaddr + (off - p->p_offset);
	}
	return -1;
}

__u64 elf_virt_to_off(elf_t *elf, __u64 virt) {
	foreach_phdr(elf, p) {
		if (_contain_(p->p_vaddr, p->p_memsz, virt))
			return p->p_offset + (virt - p->p_vaddr);
	}
	return -1;
}

Elf_Shdr *sec_by_shtype(__u32 t, elf_t *elf) {
	foreach_shdr(elf, sec) {
		if (sec->sh_type == t) return sec;
	}
	return NULL;
}

Elf_Phdr *phdr_by_ptype(__u32 t, elf_t *elf) {
	foreach_phdr(elf, p) {
		if (p->p_type == t) return p;
	}
	return NULL;
}

static __s8 elf_init_got_plt(elf_t *elf) {
	if (elf_has_shdr(elf)) {
		elf->got	 = elf_sec_by_name(elf, ".got");
		elf->got_plt = elf_sec_by_name(elf, ".got.plt");
		elf->plt	 = elf_sec_by_name(elf, ".plt");
		elf->plt_got = elf_sec_by_name(elf, ".plt.got");

		return 0;
	}
	return -1;
}

void elf_alloc_symtab(elf_t *elf, symtab_t *stab) {
	stab->off = _elf_off(elf, stab->tab);
	mmsz_alloc(&stab->mm_tab, _elf_symtab_sz(stab));
	mmsz_alloc(&stab->mm_str, elf->sec.tab[stab->sec->sh_link].sh_size);
	elf_init_symtabs(elf);
}

void elf_alloc_rela(elf_t *elf, rela_t *rtab) {
	rtab->off = _elf_off(elf, rtab->ptr);
	mmsz_alloc(&rtab->mm, _elf_rela_t_sz(rtab));
	elf_set_rela(elf);
}

void elf_alloc_all(elf_t *elf) {
	if (!!elf->phdr.tab) {
		mmsz_alloc(&elf->phdr.mm, _elf_phdr_sz(elf));
	}
	if (!!elf->sec.tab) {
		mmsz_alloc(&elf->sec.mm_tab, _elf_shdr_sz(elf));
		mmsz_alloc(&elf->sec.mm_str, elf->sec.strtab_shdr->sh_size);
	}
	if (!!elf->dynamic.tab) {
		elf->dynamic.off = _elf_off(elf, elf->dynamic.tab);
		mmsz_alloc(&elf->dynamic.mm, _elf_dynamic_sz(elf));
	}
	if (!!elf->gnu_ver.sym) {
		mmsz_alloc(&elf->gnu_ver.mm_sym, elf->gnu_ver.mm_sym.sz);
	}

	foreach_ll_rela(&elf->ll_rela, rtab)	elf_alloc_rela(elf, rtab);
	foreach_ll_rela(&elf->ll_rel, rtab)		elf_alloc_rela(elf, rtab);

	foreach_ll_symtab(elf, stab) elf_alloc_symtab(elf, stab);
}

symtab_t *elf_get_symtab(elf_t *elf) {
	return elf_get_symtab_t(elf, SHT_SYMTAB);
}
symtab_t *elf_get_dyntab(elf_t *elf) {
	return elf_get_symtab_t(elf, SHT_DYNSYM);
}

symtab_t *elf_get_symtab_t(elf_t *elf, __u64 t) {
	foreach_ll_symtab(elf, stab) if (stab->t == t) return stab;
	return NULL;
}

__u8 *elf_sec_name(elf_t *elf, Elf_Shdr *sec) {
	return &elf->sec.str[sec->sh_name];
}

__u8 *elf_sym_name(symtab_t *stab, Elf_Sym *sym) {
	return &stab->str[sym->st_name];
}

__u8 *elf_find_sym_name(elf_t *elf, Elf_Sym *sym) {
	foreach_sym(elf, stab, i) if (sym == i) return elf_sym_name(stab, i);
	return NULL;
}

__u8 *elf_rela_name(symtab_t *stab, Elf_Rela *rela) {
	return stab->str + stab->tab[ELF64_R_SYM(rela->r_info)].st_name;
}

__u8 *elf_rel_name(symtab_t *stab, Elf_Rel *rel) {
	return stab->str + stab->tab[ELF64_R_SYM(rel->r_info)].st_name;
}

__u8 sym_fits_phdr(Elf_Sym *sym, Elf_Phdr *p) {
	return !!_contains_(p->p_vaddr, _align(p->p_memsz, p->p_align), sym->st_value, sym->st_size);
}

Elf_Phdr *shdr_get_phdr(elf_t *elf, Elf_Shdr *sec) {
	foreach_phdr(elf, p) {
		if (p->p_vaddr <= sec->sh_addr && p->p_vaddr + p->p_memsz >= sec->sh_addr + sec->sh_size)
			return p;
	}
}

rela_t *elf_get_plt_rela(elf_t *elf) {
	foreach_dynamic(elf, dyn) {
		foreach_ll_rela(&elf->ll_rel, rtab)
			if (elf_ftov(elf, rtab->off) == dyn->d_un.d_val)
				return rtab;

		foreach_ll_rela(&elf->ll_rela, rtab)
			if (elf_ftov(elf, rtab->off) == dyn->d_un.d_val)
				return rtab;
	}
	return NULL;
}

Elf_Shdr *elf_virt_to_shdr(elf_t *elf, __u64 virt) {
	foreach_shdr(elf, sec) {
		if (_contain_(sec->sh_addr, sec->sh_size, virt))
			return sec;
	}
	return NULL;
}

Elf_Shdr *elf_off_to_shdr(elf_t *elf, __u64 off) {
	foreach_shdr(elf, sec) {
		if (_contain_(sec->sh_offset, sec->sh_size, off))
			return sec;
	}
	return NULL;
}

int get_phdr_ndx(elf_t *elf, Elf_Phdr *phdr) {
	int i=0;
	foreach_phdr(elf, p) {
		if (p == phdr) return i;
		i++;
	}
	return -1;
}

__u8 *elf_ver_str(elf_t *elf, __u16 i) {
	symtab_t *m_dyn	= elf_get_dyntab(elf);
	if (!m_dyn) return -1;

	Elf_Vernaux *vna = elf_vernaux_by_ndx(elf, elf->gnu_ver.sym[i]);
	if (!vna) return -1;

	return &m_dyn->str[vna->vna_name];
}

Elf_Vernaux *elf_vernaux_by_ndx(elf_t *elf, __u64 v) {
	for_each_gnu_verneed(elf, vn) {
		for_each_gnu_vernaux(vn, vna)
			if (vna->vna_other == v)
				return vna;
	}
	return NULL;
}

Elf_Vernaux *elf_vernaux_by_name(elf_t *elf, __u8 *name) {
	symtab_t *dyntab = elf_get_dyntab(elf);
	if (!dyntab) return -1;
	
	for_each_gnu_verneed(elf, vn) {
		for_each_gnu_vernaux(vn, vna)
			if (!_qstrcmp(&dyntab->str[vna->vna_name], name))
				return vna;
	}
	return NULL;
}

// __s32 get_shdr_ndx(elf_t *elf, Elf_Shdr *sec) {
// 	__u64 tabl_sz = N_SHDR(elf->ehdr->e_shnum);
// 	if (!_contains_(elf->shdr, tabl_sz, sec, SHDR_SZ))
// 		return -1;

// 	__u64 off = (void*)sec - (void*)elf->shdr;

// 	#ifdef ELF_CHECK
// 		_assertf(!(off % SHDR_SZ), PR_ERR "%s", __FUNCTION__);
// 		return off / SHDR_SZ;
// 	#else
// 		return (!(off % SHDR_SZ) ? off/SHDR_SZ : -1);
// 	#endif
// }

// void pr_sec(elf_t *elf, Elf_Shdr *sec) {
// 	prf("Section name - [%s]\t\tsh_offset - [0x%lx]\t\tsh_size - [0x%lx]\n",
// 		&elf->sh_strtab[sec->sh_name], sec->sh_offset, sec->sh_size);
// }

// void pr_sym(elf_t *elf, Elf_Sym *sym) {
// 	prf("===[++ (%s) ++]---\tValue 0x%lx\tSize 0x%lx\n",
// 		elf->sym.str+sym->st_name, sym->st_value, sym->st_size);
// }

// Elf_Sym *elf_sym_by_name(elf_t *elf, __u8 *str) {
// 	foreach_sym(elf, sym) {
// 		__u8 *symname = &elf->sym.str[sym->st_name];
// 		if (!_strncmp(symname, str, strlen(str)))
// 			return sym;
// 	}
// 	return NULL;
// }

Elf_Dyn *elf_get_got_plt(elf_t *elf) {
	foreach_dynamic(elf, dyn) if (dyn->d_tag == DT_PLTGOT) return dyn;
	return NULL;
}
__s8 elf_dtag_is_addr(__s64 dtag) {
	switch (dtag) {
		case DT_RUNPATH:
		case DT_SONAME:
		case DT_NEEDED:
		case DT_HASH:
		case DT_STRTAB:
		case DT_SYMTAB:
		case DT_RELA:
		case DT_INIT:
		case DT_FINI:
		case DT_RPATH:
		case DT_PLTGOT:
		case DT_INIT_ARRAY:
		case DT_FINI_ARRAY:
		case DT_REL:
		case DT_JMPREL:
		case DT_VERSYM:
		case DT_VERNEED:
			return 1;
	}

	return 0;
}

Elf_Phdr *elf_off_to_phdr(elf_t *elf, __u64 off) {
	foreach_phdr(elf, p) {
		if (_contain_(p->p_offset, p->p_filesz, off))
			return p;
	}
	return NULL;
}


Elf_Phdr *elf_virt_to_phdr(elf_t *elf, __u64 virt) {
	foreach_phdr(elf, p) {
		if (_contain_(p->p_vaddr, p->p_memsz, virt))
			return p;
	}
	return NULL;
}
