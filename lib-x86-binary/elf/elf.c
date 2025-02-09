#include <linux/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <string.h>
#include "./elf.h"
#include "../utils/include/utils.h"
#include "../utils/include/llist.h"

static __s8 load_elf(elf_t *elf, __u8 *f, elf_opts_t *opts);
static __s8 init_elf(elf_t *elf, elf_opts_t *opts);
static __s8 elf_init_dynamic(elf_t *elf);
static __s8 elf_init_symtab(elf_t *elf);
static __s8 elf_init_rela(elf_t *elf);
static __u8 *elf_filename(elf_t *elf);

#define prf_elf(elf, t, str, ...)		\
		xprf(t, "[ELF] - " str ", file (%s)\n", __VA_ARGS__, elf_filename(elf))

#define pr_elf(elf, t, str)				\
		xprf(t, "[ELF] - %s, file (%s)\n", (str), elf_filename(elf))


static __u8 _elf_magic(elf_t *elf) {
	__u8 *p = elf->map;
	return (p[0]=='\x7f' && p[1]=='E' && p[2]=='L' && p[3]=='F');
}
static __u8 *elf_filename(elf_t *elf) {
	return ((!elf) ? (color(BBLUE, "[null]")) : (!elf->file) ? (color(BBLUE, "[----]")) : (void*)elf->file);
}


static __s8 _elf_set_arch(elf_t *elf, elf_opts_t *opts) {
	__u8 class = elf->ehdr->e_ident[EI_CLASS];
	if (class == ELFCLASSNONE) {
		if (!opts->elf_class) {
			pr_elf(elf, ERR, "EI_CLASS is Invalid (not 64,32)");
			return -1;
		}	
		elf->ehdr->e_ident[EI_CLASS] = opts->elf_class;
	}

	// Set ELF_... type
	switch (elf->ehdr->e_machine) {
		case EM_X86_64:
			if (class == ELFCLASS64) elf->arch = ELF_X86_64;
			if (class == ELFCLASS32) elf->arch = ELF_X86_32;
			break;
		default:
			pr_elf(elf, ERR, "Architecture not supported");
			return -1;
	}
	elf->bits = (class == ELFCLASS32) ? 32 : 64;
	return 0;
}

static __s8 _elf_check_ehdr(elf_t *elf, elf_opts_t *opts) {
	// _assert(sizeof(Elf32_Ehdr) == sizeof(Elf64_Ehdr),
	// 	"unlikely");
	if (!_elf_magic(elf)) {
		pr_elf(elf, ERR, "Invalid Magic bytes (\\x7fELF) - not an ELF");
		return -1;
	}

	// Little endian
	__u8 *ei = (__u8*)elf->ehdr->e_ident;
	if (ei[EI_DATA] != ELFDATA2LSB) {
		if (!opts->skip) {
			pr_elf(elf, ERR, "Not little-endian");
			return -1;
		}
		ei[EI_DATA] = ELFDATA2LSB;
	}
	// ELF version current
	if (ei[EI_VERSION] != EV_CURRENT) {
		if (!opts->skip) {
			pr_elf(elf, ERR, "Invalid ELF Version (not current)");
			return -1;
		}
		ei[EI_VERSION] = EV_CURRENT;
	}
	// Check Shdr entry size
	if (elf_has_shdr(elf)) {
		if (	(elf->bits == 32 && elf->ehdr->e_shentsize != sizeof(Elf32_Shdr))
			||	(elf->bits == 64 && elf->ehdr->e_shentsize != sizeof(Elf64_Shdr)))
		{
			pr_elf(elf, ERR, "Invalid Shdr Entsize");
			return -1;
		}
	}

	// Check Phdr entry size
	if (elf_has_phdr(elf)) {
		if (	(elf->bits == 32 && elf->ehdr->e_phentsize != sizeof(Elf32_Phdr))
			||	(elf->bits == 64 && elf->ehdr->e_phentsize != sizeof(Elf64_Phdr)))
		{
			pr_elf(elf, ERR, "Invalid Phdr Entsize");
			return -1;
		}
	}

	return 0;
}

// static ELF_RET _elf_check_hdrs(elf_t *elf) {
	// __s8 r = 0;
	// elf_each_phdr64(elf, p) {
	// 	if (p->p_offset + p->p_filesz > elf->size) {
	// 		xprf(ERR, "Overflowing ELF phdr (%lu) / over file size (%lu)\n",
	// 			p->p_offset + p->p_filesz, elf->size);
	// 		r = -1;
	// 	}
	// }
	// return ELF_RET(r, NULL);
// }

/* Init ELF file */
int elf_init(elf_t *elf, __u8 *f, elf_opts_t *opts) {
	if (!opts) opts = &(elf_opts_t){0};
	if (load_elf(elf, f, opts)	== -1) return -1;
	if (init_elf(elf, opts)		== -1) return -1;
	return 0;
}

static __s8 load_elf(elf_t *elf, __u8 *f, elf_opts_t *opts) {
	struct stat st = {0};

	int fd = open(f, O_RDONLY);
	if (fd == -1) return -1;

	if (stat(f, &st) == -1)
		return -1;

	void *map = mmap(0, st.st_size, PROT_RW, MAP_PRIVATE, fd, 0);
	if (map == MAP_FAILED) return -1;
	*elf = (elf_t){
		.file	= xmalloc(strlen(f)),
		.size	= st.st_size,
		.map	= map,
		.ehdr	= (Elf64_Ehdr*)map,
	};
	memcpy(elf->file, f, strlen(f));

	close(fd);
	return 0;
}

static __s8 init_elf(elf_t *elf, elf_opts_t *opts) {
	if (!elf) return -1;
	if (_elf_set_arch(elf, opts) == -1) return -1;
	if (_elf_check_ehdr(elf, opts) == -1)
		return -1;

	void *map = elf->map;
	void *phdr = map + elf->ehdr->e_phoff;
	void *shdr = map + elf->ehdr->e_shoff;
	__u16 shstrndx = elf->ehdr->e_shstrndx;

	if (elf->size < elf->ehdr->e_phoff + elf->ehdr->e_phnum * ELF_PHDR_SZ(elf)) {
		pr_elf(elf, ERR, "Invalid Phdr table");
		return -1;
	}

	if (elf_has_phdr(elf)) {
		if (elf->bits == 32) elf->phdr.tab32 = phdr;
		if (elf->bits == 64) elf->phdr.tab64 = phdr;
		elf->phdr.count = elf->ehdr->e_phnum;
	}

	if (elf_has_shdr(elf)) {
		elf->sec.tab32 = shdr;	// union
		elf->sec.count = elf->ehdr->e_shnum;

		if (elf->bits == 32) {
			elf->sec.str.tab = (map + elf->sec.tab32[shstrndx].sh_offset);
			elf->sec.str.size = elf->sec.tab32[shstrndx].sh_size;
		}

		if (elf->bits == 64) {
			elf->sec.str.tab = (map + elf->sec.tab64[shstrndx].sh_offset);
			elf->sec.str.size = elf->sec.tab64[shstrndx].sh_size;
		}
	}
	// if (_elf_check_hdrs(elf) == -1) 	return -1;

	if (elf_init_dynamic(elf) == -1)	return -1;
	if (elf_init_symtab(elf) == -1)		return -1;
	if (elf_init_rela(elf) == -1)		return -1;
	
	return 0;
}

void elf_free(elf_t *elf) {
	llist_free_all(&elf->symtab);
	if (!!elf->symtab.head) free(&elf->symtab);

	llist_free_all(&elf->rel);
	if (!!elf->rel.head) free(&elf->rel);

	llist_free_all(&elf->rela);
	if (!!elf->rela.head) free(&elf->rela);
}
 

static __s8 elf_init_dynamic(elf_t *elf) {
	if (!elf_has_phdr(elf)) {
		if (!elf_has_shdr(elf)) return -1;

		elf_each_sec64(elf, sec) {
			if (sec->sh_type == SHT_DYNAMIC) {
				elf->dynamic.ptr	= elf->map + sec->sh_offset;
				elf->dynamic.count	= sec->sh_size / ELF_DYN_SZ(elf);
				return 0;
			}
		}
	} else {
		elf_each_phdr64(elf, p) if (p->p_type == PT_DYNAMIC) {
			elf->dynamic.ptr	= (elf->map + p->p_offset);
			elf->dynamic.count	= p->p_filesz / ELF_DYN_SZ(elf);
			return 0;
		}
	}
	return -1;
}


#define RELA_T_SZ(t, sz)			\
		((t==DT_RELA) ? (sz / sizeof(Elf64_Rela)) : (t==DT_REL) ? (sz / sizeof(Elf64_Rel)) : 0)

#define RELA_SET_SZ(st_ptr, t, sz)	{		\
		(st_ptr)->mm.sz = sz;				\
		(st_ptr)->count = RELA_T_SZ(t, sz);	\
	}

static __s8 elf_init_rela(elf_t *elf) {
	llist_new(&elf->rela, sizeof(elf_rela_t));
	llist_new(&elf->rel, sizeof(elf_rela_t));

	/* Set Rel, Rela, JMPREL (.rela.plt) from Dynamic */
	if (elf_has_phdr(elf)) {
		if (!elf->dynamic.ptr) return -1;

		elf_rela_t rela = {0};
		elf_rel_t	rel = {0};
		__u64 plt_t = 0, plt_sz = 0, plt_ptr = 0;

		elf_each_dynamic64(elf, e) {
			void *ptr = (elf->map + elf_vtof(elf, e->d_un.d_ptr));
			__u64 v = e->d_un.d_val;

			switch (e->d_tag) {
				case DT_REL:		rel.ptr		= ptr;	break;
				case DT_RELSZ:
					rel.count = v / ELF_REL_SZ(elf);	break;

				case DT_RELA:		rela.ptr	= ptr;	break;
				case DT_RELASZ:
					rela.count = v / ELF_RELA_SZ(elf); break;

				case DT_PLTREL:		plt_t	= v; 		break;
				case DT_PLTRELSZ:	plt_sz	= v; 		break;
				case DT_JMPREL:		plt_ptr = (__u64)ptr;		break;
			}
		}
		if (rel.ptr)	llist_add(&elf->rel, &rel);
		if (rela.ptr)	llist_add(&elf->rela, &rela);
		if (plt_ptr) {
			if (plt_t == DT_REL) {		// JMPREL type is Rel
				llist_add(&elf->rel, &(elf_rel_t){
					.ptr	= (void*)plt_ptr,
					.count	= plt_sz / ELF_REL_SZ(elf),
				});
			}
			if (plt_t == DT_RELA) {		// Rela -
				llist_add(&elf->rela, &(elf_rel_t){
					.ptr	= (void*)plt_ptr,
					.count	= plt_sz / ELF_RELA_SZ(elf),
				});
			}
		}
	} else if (elf_has_shdr(elf)) {
		elf_each_sec64(elf, sec) {
			void *ptr		= elf->map + sec->sh_offset;
			__u64 sec_sz	= sec->sh_size;

			if (sec->sh_type == SHT_REL) {		// Rel
				llist_add(&elf->rel, &(elf_rel_t){
					.ptr	= ptr,
					.count	= sec_sz / ELF_REL_SZ(elf),
				});
			}
			if (sec->sh_type == SHT_RELA) {		// Rela
				llist_add(&elf->rela, &(elf_rela_t){
					.ptr	= ptr,
					.count	= sec_sz / ELF_RELA_SZ(elf),
				});
			}
		}
	} else return -1;

	return 0;
}


static __s8 elf_init_symtab(elf_t *elf) {
	if (!elf_has_shdr(elf)) return -1;
	llist_new(&elf->symtab, sizeof(elf_symtab_t));

	elf_each_sec64(elf, sec) {
		if (sec->sh_type != SHT_DYNSYM && sec->sh_type != SHT_SYMTAB)
			continue;
 
		elf_symtab_t sym = {
			.t		= sec->sh_type,
			.ptr	= elf->map + sec->sh_offset,
			.count	= sec->sh_size / ELF_SYM_SZ(elf),
		};
		if (elf->bits == 32) {
			sym.str.tab		= (elf->map + elf->sec.tab32[sec->sh_link].sh_offset);
			sym.str.size	= elf->sec.tab32[sec->sh_link].sh_size;
		}
		if (elf->bits == 64) {
			sym.str.size	= elf->sec.tab64[sec->sh_link].sh_size;
			sym.str.tab		= (elf->map + elf->sec.tab64[sec->sh_link].sh_offset);
		}
		llist_add(&elf->symtab, &sym);
	}

	return 0;
}



elf_symtab_t *elf_get_symtab(elf_t *elf) {
	return elf_get_symtab_t(elf, SHT_SYMTAB);
}
elf_symtab_t *elf_get_dyntab(elf_t *elf) {
	return elf_get_symtab_t(elf, SHT_DYNSYM);
}

elf_symtab_t *elf_get_symtab_t(elf_t *elf, __u64 t) {
	elf_each_symtab(elf, stab) if (stab->t == t) return stab;
	return NULL;
}

// Get Phdr containing ~sec (section)
Elf64_Phdr *elf_sec_get_phdr(elf_t *elf, Elf64_Shdr *sec) {
	elf_each_phdr64(elf, p) {
		if (p->p_vaddr <= sec->sh_addr && p->p_vaddr + p->p_memsz >= sec->sh_addr + sec->sh_size)
			return p;
	}
}

Elf64_Sym *elf_sym_by_name(elf_t *elf, __u8 *str) {
	elf_each_symtab_sym64(elf, stab, sym) {
		__u8 *symname = &stab->str.tab[sym->st_name];
		if (strncmp(symname, str, strlen(str)+1))	// nullbyte
			return sym;
	}
	return NULL;
}

/**
 * Get Names
 **/
Elf64_Shdr *elf_sec_by_name(elf_t *elf, __u8 *str) {
	elf_each_sec64(elf, sec) {
		if (!strncmp(elf_sec_name(elf, sec), str, strlen(str)+1))
			return sec;
	}
	return NULL;
}

__u8 *elf_rela_name(elf_symtab_t *stab, Elf64_Rela *rela) {
	return stab->str.tab + stab->tab64[ELF64_R_SYM(rela->r_info)].st_name;
}
__u8 *elf_rel_name(elf_symtab_t *stab, Elf64_Rel *rel) {
	return stab->str.tab + stab->tab64[ELF64_R_SYM(rel->r_info)].st_name;
}
__u8 *elf_sec_name(elf_t *elf, Elf64_Shdr *sec) {
	return &elf->sec.str.tab[sec->sh_name];
}
__u8 *elf_sym_name(elf_symtab_t *stab, Elf64_Sym *sym) {
	return &stab->str.tab[sym->st_name];
}

// Go through each symbol table to find the symbol
// elf_symtab_t *elf_find_symtab(elf_t *elf, Elf64_Sym *sym) {
// 	elf_each_symtab_sym64(elf, stab, i)
// 		if (sym == i) return stab;
// 	return NULL;
// }


// Get GOT.PLT
// Elf64_Dyn *elf_get_got_plt(elf_t *elf) {
// 	elf_each_dynamic64(elf, dyn) if (dyn->d_tag == DT_PLTGOT) return dyn;
// 	return NULL;
// }

// Dynamic is address
__s8 elf_dtag_is_addr(__s64 dtag) {
	switch (dtag) {
		case DT_RUNPATH:
		case DT_SONAME:
		case DT_NEEDED:
		case DT_HASH:
		case DT_STRTAB:
		case DT_SYMTAB:
		case DT_JMPREL:
		case DT_RELA:
		case DT_REL:
		case DT_INIT:
		case DT_FINI:
		case DT_RPATH:
		case DT_PLTGOT:
		case DT_INIT_ARRAY:
		case DT_FINI_ARRAY:
		case DT_VERSYM:
		case DT_VERNEED:
			return 1;
	}

	return 0;
}

/**
 * Offset / Virt Addr to -
 **/

// Offset to Phdr
Elf64_Phdr *elf_off_to_phdr(elf_t *elf, __u64 off) {
	elf_each_phdr64(elf, p)
		if (_contain_(p->p_offset, p->p_filesz, off))
			return p;
	return NULL;
}
// Virtual addr to Phdr
Elf64_Phdr *elf_virt_to_phdr(elf_t *elf, __u64 virt) {
	elf_each_phdr64(elf, p)
		if (_contain_(p->p_vaddr, p->p_memsz, virt))
			return p;
	return NULL;
}

// Virtual Addr to Section
// Elf64_Shdr *elf_virt_to_shdr(elf_t *elf, __u64 virt) {
// 	elf_each_sec64(elf, sec)
// 		if (_contain_(sec->sh_addr, sec->sh_size, virt))
// 			return sec;
// 	return NULL;
// }
// // Offset to section
// Elf64_Shdr *elf_off_to_shdr(elf_t *elf, __u64 off) {
// 	elf_each_sec64(elf, sec)
// 		if (_contain_(sec->sh_offset, sec->sh_size, off))
// 			return sec;
// 	return NULL;
// }


Elf64_Phdr *elf_shdr_get_phdr(elf_t *elf, Elf64_Shdr *sec) {
	elf_each_phdr64(elf, p) {
		if (_contains_(p->p_vaddr, p->p_memsz, sec->sh_addr, sec->sh_size))
			return p;
	}
}

// ELF offset to virt addr
__u64 elf_off_to_virt(elf_t *elf, __u64 off) {
	elf_each_phdr64(elf, p)
		if (_contain_(p->p_offset, p->p_filesz+1, off))
			return p->p_vaddr + (off - p->p_offset);
	return -1;
}
// ELF virt addr to offset
__u64 elf_virt_to_off(elf_t *elf, __u64 virt) {
	elf_each_phdr64(elf, p)
		if (_contain_(p->p_vaddr, ALIGN(p->p_memsz, p->p_align), virt))
			return p->p_offset + (virt - p->p_vaddr);
	return -1;
}

// __u16 pack_phdr_ndx(patch_header_t *e, void *phdr) {
// 	return ((e->mm.mem - elf->phdr.ptr) / (ELF_PHDR_SZ(elf)));
// }
