#include <linux/types.h>
#include <elf.h>
#include "../utils/include/llist.h"
#include "../disass_x86/include/disass.h"

#ifndef ELF_H
#define ELF_H

#define ELF_VIRT	1
#define ELF_OFF		2

/**
 * Supported Architectures */
typedef enum {
	ELF_X86_64,
	ELF_X86_32,
	ELF_INVALID,
} elf_arch_enum;


typedef struct {
	union {
		Elf64_Sym	*sym64;
		Elf32_Sym	*sym32;
	};
	__u64	size;
	__u64	off;
} elf_sym_obj;

typedef struct {
	union {
		void		*ptr;
		Elf64_Rela	*tab64;
		Elf32_Rela	*tab32;
	};
	__u64			count;
} elf_rela_t;

typedef struct {
	union {
		void		*ptr;
		Elf64_Rel	*tab64;
		Elf32_Rel	*tab32;
	};
	__u64			count;
} elf_rel_t;

typedef struct {
	__u8		*tab;	// str.tab
	union {
		Elf64_Shdr	*sec64;
		Elf32_Shdr	*sec32;
	};
	__u64			size;
} elf_strtab_t;

typedef struct {
	__u16		t;
	union {
		void		*ptr;
		Elf64_Sym	*tab64;
		Elf32_Sym	*tab32;
	};
	__u64			count;
	elf_strtab_t	str;
} elf_symtab_t;


typedef struct {
	elf_arch_enum		arch;
	__u8	bits;
	__u8	*file;
	union {
		__u8		*mem;
		void		*map;
		Elf64_Ehdr	*ehdr;
	};
	__u64	size;

	union {
		void		*ptr;
		Elf32_Phdr	*phdr32;
		Elf64_Phdr	*phdr64;
	};
	struct {
		union {
			void		*ptr;
			Elf32_Phdr	*tab32;
			Elf64_Phdr	*tab64;
		};
		__u64			count;
	} phdr;

	struct {
		union {
			void		*ptr;
			Elf32_Shdr	*tab32;
			Elf64_Shdr	*tab64;
		};
		__u64			count;
		elf_strtab_t	str;
	} sec;

	struct {
		union {
			void		*ptr;
			Elf32_Dyn	*tab32;
			Elf64_Dyn	*tab64;
		};
		__u64	count;
	} dynamic;


	llist_t		symtab;		// T elf_symtab_t
	llist_t		rela;		// T elf_rela_t
	llist_t		rel;		// T elf_rel_t
} elf_t;

typedef struct {
	__u8		elf_class;	// eg. EI_CLASS64
	__s8		skip;		// Skip invalid
} elf_opts_t;

#define elf_has_phdr(elf)	((elf)->ehdr->e_phoff && (elf)->ehdr->e_phnum)
#define elf_has_shdr(elf)	((elf)->ehdr->e_shoff && (elf)->ehdr->e_shnum)

#define ELF_PHDR_SZ(elf)	(((elf)->bits==32) ? sizeof(Elf32_Phdr) : sizeof(Elf64_Phdr))
#define ELF_SHDR_SZ(elf)	(((elf)->bits==32) ? sizeof(Elf32_Shdr) : sizeof(Elf64_Shdr))
#define ELF_DYN_SZ(elf)		(((elf)->bits==32) ? sizeof(Elf32_Dyn) : sizeof(Elf64_Dyn))
#define ELF_RELA_SZ(elf)	(((elf)->bits==32) ? sizeof(Elf32_Rela) : sizeof(Elf64_Rela))
#define ELF_REL_SZ(elf)		(((elf)->bits==32) ? sizeof(Elf32_Rel) : sizeof(Elf64_Rel))
#define ELF_SYM_SZ(elf) 	(((elf)->bits==32) ? sizeof(Elf32_Sym) : sizeof(Elf64_Sym))

#define _elf_each_phdr(elf,  bits, p)									\
		for (Elf##bits##_Phdr *p = (elf)->phdr.ptr;						\
			(void*)p < ((elf)->phdr.ptr + ((elf)->phdr.count * sizeof(*p)));	\
			p++)
#define elf_each_phdr32(elf, p) _elf_each_phdr(elf, 32, p)
#define elf_each_phdr64(elf, p) _elf_each_phdr(elf, 64, p)


#define _elf_each_sec(elf, bits, s)										\
		for (Elf##bits##_Shdr *s = (elf)->sec.ptr;						\
			(void*)s < ((elf)->sec.ptr + (elf)->sec.count * sizeof(*s));\
			s++)
#define elf_each_sec32(elf, s) _elf_each_sec(elf, 32, s)
#define elf_each_sec64(elf, s) _elf_each_sec(elf, 64, s)


#define _elf_each_dynamic(elf, bits, d)										\
		for (Elf##bits##_Dyn *d = (elf)->dynamic.ptr;						\
			(void*)d < ((elf)->dynamic.ptr + (elf)->dynamic.count * sizeof(*d));	\
			d++)
#define elf_each_dynamic32(elf, d) _elf_each_dynamic(elf, 32, d)
#define elf_each_dynamic64(elf, d) _elf_each_dynamic(elf, 64, d)


#define elf_each_symtab(elf, stab)		\
		llist_each(&(elf)->symtab, e)	\
			for (elf_symtab_t *stab = e->dat; !!stab; stab=NULL)

#define _elf_each_sym(bits, stab, sym)	\
		for (Elf##bits##_Sym *sym = (stab)->tab##bits; sym < &(stab)->tab##bits[(stab)->count]; sym++)

#define elf_each_sym64(elf, stab, sym) _elf_each_sym(64, stab, sym)
#define elf_each_sym32(elf, stab, sym) _elf_each_sym(32, stab, sym)

#define elf_each_symtab_sym64(elf, stab, sym)		\
			elf_each_symtab(elf, stab) _elf_each_sym(64, stab, sym)

#define elf_each_symtab_sym32(elf, stab, sym)		\
			elf_each_symtab(elf, stab) _elf_each_sym(32, stab, sym)


#define elf_each_reltab(elf, rtab)		\
		llist_each(&(elf)->rel, e) for (elf_rela_t *rtab = e->dat; !!rtab; rtab=NULL)

#define elf_each_relatab(elf, rtab)		\
		llist_each(&(elf)->rela, e) for (elf_rela_t *rtab = e->dat; !!rtab; rtab=NULL)


#define _elf_each_rel(rtab, bits, rel)			\
		for (Elf##bits##_Rel *rel = rtab->tab; rel < &rtab->tab[rtab->count]; rel++)

#define elf_each_rel64(elf, rtab, rel) _elf_each_rel(elf, 64, rtab, rel)
#define elf_each_rel32(elf, rtab, rel) _elf_each_rel(elf, 32, rtab, rel)


#define _elf_each_rela(rtab, bits, rela)		\
		for (Elf##bits##_Rela *rela = rtab->tab; rela < &rtab->tab[rtab->count]; rela++)

#define elf_each_rela64(elf, rtab, rela) _elf_each_rela(elf, 64, rtab, rela)
#define elf_each_rela32(elf, rtab, rela) _elf_each_rela(elf, 32, rtab, rela)

int elf_init(elf_t *elf, __u8 *f, elf_opts_t *opts);
void elf_free(elf_t *elf);

__u64 elf_off_to_virt(elf_t *elf, __u64 off);
__u64 elf_virt_to_off(elf_t *elf, __u64 virt);
#define elf_vtof	elf_virt_to_off
#define elf_ftov	elf_off_to_virt

__u16 elf_phdr_ndx(elf_t *elf, void *phdr);
elf_symtab_t *elf_get_symtab(elf_t *elf);
elf_symtab_t *elf_get_dyntab(elf_t *elf);
elf_symtab_t *elf_get_symtab_t(elf_t *elf, __u64 t);
Elf64_Phdr *elf_sec_get_phdr(elf_t *elf, Elf64_Shdr *sec);
elf_rela_t *elf_get_plt_rela(elf_t *elf);

__u8 *elf_ver_str(elf_t *elf, __u16 i);
Elf64_Vernaux *elf_vernaux_by_ndx(elf_t *elf, __u64 v);
Elf64_Vernaux *elf_vernaux_by_name(elf_t *elf, __u8 *name);

Elf64_Sym *elf_sym_by_name(elf_t *elf, __u8 *str);
Elf64_Shdr *elf_sec_by_name(elf_t *elf, __u8 *str);
__u8 *elf_rela_name(elf_symtab_t *stab, Elf64_Rela *rela);
__u8 *elf_rel_name(elf_symtab_t *stab, Elf64_Rel *rel);
__u8 *elf_sec_name(elf_t *elf, Elf64_Shdr *sec);
__u8 *elf_sym_name(elf_symtab_t *stab, Elf64_Sym *sym);
__u8 *elf_any_sym_name(elf_t *elf, Elf64_Sym *sym);

elf_symtab_t *elf_find_symtab(elf_t *elf, Elf64_Sym *sym);
Elf64_Dyn *elf_get_got_plt(elf_t *elf);
__s8 elf_dtag_is_addr(__s64 dtag);

Elf64_Phdr *elf_off_to_phdr(elf_t *elf, __u64 off);
Elf64_Phdr *elf_virt_to_phdr(elf_t *elf, __u64 virt);
Elf64_Shdr *elf_virt_to_shdr(elf_t *elf, __u64 virt);
Elf64_Shdr *elf_off_to_shdr(elf_t *elf, __u64 off);
Elf64_Phdr *elf_shdr_get_phdr(elf_t *elf, Elf64_Shdr *sec);

__s64 elf_off_phdr(elf_t *elf, __u8 t);

__u64 get_unknown_sz_sym_sz(elf_t *elf, Elf64_Sym *sym);
Elf64_Sym *elf_off_to_sym(elf_t *elf, __u64 off, __u64 sz);
elf_sym_obj *make_sym_obj(elf_t *elf, void *sym);
elf_sym_obj *get_sym(elf_t *elf, __u8 *str);
#endif
