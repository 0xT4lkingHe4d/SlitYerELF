#include <linux/types.h>
#include <elf.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "./utils.h"
#include "./list.h"

#define ELF_CHECK
// #include "./llist.h"
#ifndef UAPI_
#define UAPI_
typedef __s8 bool;
#endif

#define Elf_Ehdr	Elf64_Ehdr
#define Elf_Phdr	Elf64_Phdr
#define Elf_Shdr	Elf64_Shdr
#define Elf_Dyn		Elf64_Dyn
#define Elf_Rel		Elf64_Rel
#define Elf_Rela	Elf64_Rela
#define Elf_Sym		Elf64_Sym
#define Elf_Off		Elf64_Off
#define Elf_Verneed	Elf64_Verneed
#define Elf_Vernaux	Elf64_Vernaux


#ifndef ELF_T_STRUCT
#define ELF_T_STRUCT

typedef struct {
	Elf_Shdr	*sec;
	__u64		off;
	__u32		t;
	union {
		void		*ptr;
		Elf_Rela	*rela;
		Elf_Rel		*rel;
		mmsz_tup	mm;
	};
} rela_t;

typedef struct {
	Elf_Sym	*sym;
	__u64	size;
	__u64	off;
} sym_obj;

typedef struct {
	__u16		t;
	Elf_Shdr	*sec;
	__u64		off;
	union {
		Elf_Sym		*tab;
		mmsz_tup	mm_tab;
	};
	union {
		__u8		*str;
		mmsz_tup	mm_str;
	};
} symtab_t;

typedef struct {
	__u64 sym_off;
	union {
		__u16			*sym;
		struct mmsz_tup mm_sym;
	};
	__u64 need_off;
	union {
		Elf_Verneed		*need;
		struct mmsz_tup mm_need;
	};
	__u64 num;
} gnu_ver_t;

typedef struct {
	union {
		__u8		*map;
		Elf_Ehdr	*ehdr;
		struct mmsz_tup		mm_ehdr;
	};
	__u64	size;
	__u8	*file;

	union {
		Elf_Phdr	*tab;
		mmsz_tup	mm;
	} phdr;

	struct {
		union {
			Elf_Shdr	*tab;
			mmsz_tup	mm_tab;
		};
		union {
			__u8 *str;
			mmsz_tup	mm_str;
		};
		Elf_Shdr *strtab_shdr;
	} sec;

	struct {
		Elf_Phdr	*phdr;
		Elf_Shdr	*sec;
		__u64		off;
		__u64		hdr_sz;
		union {
			Elf_Dyn		*tab;
			mmsz_tup	mm;
		};
	} dynamic;

	gnu_ver_t gnu_ver;
	
	llist_t ll_sym;
	llist_t ll_rela;
	llist_t ll_rel;

	Elf_Shdr *got, *plt, *got_plt, *plt_got;
} elf_t;
#endif


#define N_PHDR(n)	(sizeof(Elf_Phdr)	* n)
#define N_SHDR(n)	(sizeof(Elf_Shdr)	* n)
#define N_SYM(n)	(sizeof(Elf_Sym)	* n)

#define ELF_N_PHDR(elf, n) (elf->ehdr->e_phentsize * n)
#define ELF_N_SHDR(elf, n) (elf->ehdr->e_shentsize * n)

#define _elf_phdr_sz(elf)		(!(elf)->phdr.mm.t		? ELF_N_PHDR(elf, (elf)->ehdr->e_phnum) : (elf)->phdr.mm.sz)
#define _elf_shdr_sz(elf)		(!(elf)->sec.mm_tab.t	? ELF_N_SHDR(elf, (elf)->ehdr->e_shnum) : (elf)->sec.mm_tab.sz)
#define _elf_dynamic_sz(elf)	(!(elf)->dynamic.mm.t	? (elf)->dynamic.hdr_sz : ((elf)->dynamic.mm.sz))
#define _elf_symtab_sz(stab)	(stab)->mm_tab.sz
#define _elf_rela_t_sz(rtab)	(rtab)->mm.sz

#define _elf_off(elf, ptr)		\
		((_contain_((elf)->map, (elf)->size, (void*)(ptr))) ? ((void*)(ptr) - (void*)(elf)->map) : 0)

#define foreach_shdr(elf, s)					\
		for (Elf_Shdr *s = (elf)->sec.tab;		\
			!!s && s < (elf)->sec.mm_tab.mem + _elf_shdr_sz((elf)); s++)

#define foreach_phdr(elf, p)					\
		for (Elf_Phdr *p = (elf)->phdr.tab;		\
			!!p && p < (elf)->phdr.mm.mem + _elf_phdr_sz((elf)); p++)

#define foreach_dynamic(elf, dyn)				\
		for (Elf_Dyn *dyn = (elf)->dynamic.tab;	\
			dyn < (elf)->dynamic.mm.mem + _elf_dynamic_sz((elf)); dyn++)

#define foreach_dynamic_ptr(elf, dyn)			\
		foreach_dynamic(elf, dyn) if (elf_dtag_is_addr(dyn->d_tag))

/**
 *	Symbols
 **/
#define foreach_ll_symtab(elf, stab)		\
			foreach_ll_T((&(elf)->ll_sym), stab, symtab_t)

#define feech_syms(stab, sym)		\
		for (Elf_Sym *sym = (stab)->tab; sym < (void*)(stab)->tab + _elf_symtab_sz((stab)); sym++)

#define foreach_sym(elf, stab, sym)			\
		foreach_ll_symtab((elf), stab)		\
			feech_syms(stab, sym)

#define foreach_dynsym(elf, stab, sym)			\
		foreach_ll_symtab((elf), stab) if (stab->t == SHT_DYNSYM)	\
			feech_syms(stab, sym)

#define foreach_symtab(elf, stab, sym)			\
		foreach_ll_symtab((elf), stab) if (stab->t == SHT_SYMTAB)	\
			feech_syms(stab, sym)

/**
 *	Rel/Rela
 **/
#define foreach_ll_rela(ll, rtab)	foreach_ll_T((ll), (rtab), rela_t)
#define foreach_rela_t(rtab, e, T)				\
		for (T *e = (rtab)->ptr; !!e && (void*)e < (rtab)->ptr + _elf_rela_t_sz((rtab)); e++)

#define foreach_rel(elf, rtab, rel)				\
		foreach_ll_rela((&(elf)->ll_rel), rtab)	\
			foreach_rela_t(rtab, rel, Elf_Rel)

#define foreach_rela(elf, rtab, rela)			\
		foreach_ll_rela((&(elf)->ll_rela), rtab)	\
			foreach_rela_t(rtab, rela, Elf_Rela)

#define _rel_check(rel) ((rel)->ptr && (rel)->mm.sz)

#define elf_get_ll_rel(elf, t)											\
		(((t) == DT_REL || (t) == SHT_REL)	? (&(elf)->ll_rel)	:		\
		((t) == DT_RELA || (t) == SHT_RELA)	? (&(elf)->ll_rela)	: NULL)	\


#define for_each_gnu_verneed(elf, e)						\
		for (Elf_Verneed *i = 0, *e = (elf)->gnu_ver.need ;	\
			i < (elf)->gnu_ver.num ;						\
			i = (void*)i + 1, e = (void*)e + e->vn_next)

#define for_each_gnu_vernaux(vn, e)								\
		for (Elf_Vernaux *i = 0, *e = (void*)vn + vn->vn_aux;	\
			i < vn->vn_cnt;										\
			i = (void*)i + 1, e = (void*)e + e->vna_next)


int new_elf(__u8 *f, elf_t *elf);
int load_elf(__u8 *, elf_t *);

Elf_Phdr *shdr_get_phdr(elf_t *elf, Elf_Shdr *sec);
Elf_Phdr *get_last_PT_LOAD(Elf_Phdr *phdr, __u16 num);
Elf_Shdr *sec_by_shtype(__u32 t, elf_t *elf);
Elf_Sym *elf_sym_by_name(elf_t *elf, __u8 *str);

__u64 elf_off_to_virt(elf_t *elf, __u64 off);
__u64 elf_virt_to_off(elf_t *elf, __u64 virt);
#define elf_ftov	elf_off_to_virt
#define elf_vtof	elf_virt_to_off

Elf_Shdr *elf_sec_by_name(elf_t *elf, __u8 *str);
void pr_sec(elf_t *elf, Elf_Shdr *sec);
void pr_sym(elf_t *elf, Elf_Sym *sym);
Elf_Phdr *phdr_by_ptype(__u32 t, elf_t *elf);
rela_t *elf_get_plt_rela(elf_t *elf);

__s32 get_phdr_ndx(elf_t *elf, Elf_Phdr *phdr);
__s32 get_shdr_ndx(elf_t *elf, Elf_Shdr *sec);
__u8 *elf_ver_str(elf_t *elf, __u16 i);
Elf_Vernaux *elf_vernaux_by_ndx(elf_t *elf, __u64 i);
Elf_Vernaux *elf_vernaux_by_name(elf_t *elf, __u8 *name);

void elf_alloc_all(elf_t *elf);

symtab_t *elf_get_symtab(elf_t *elf);
symtab_t *elf_get_dyntab(elf_t *elf);
symtab_t *elf_get_symtab_t(elf_t *elf, __u64 t);
__u8 *elf_sec_name(elf_t *elf, Elf_Shdr *sec);
__u8 *elf_sym_name(symtab_t *stab, Elf_Sym *sym);
__u8 *elf_find_sym_name(elf_t *elf, Elf_Sym *sym);
__u8 *elf_rela_name(symtab_t *stab, Elf_Rela *rela);
__u8 *elf_rel_name(symtab_t *stab, Elf_Rel *rel);

Elf_Phdr *elf_virt_to_phdr(elf_t *elf, __u64 virt);
Elf_Phdr *elf_off_to_phdr(elf_t *elf, __u64 off);
Elf_Shdr *elf_virt_to_shdr(elf_t *elf, __u64 virt);
Elf_Shdr *elf_off_to_shdr(elf_t *elf, __u64 off);
Elf_Sym *elf_off_to_sym(elf_t *elf, __u64 v_off, __u64 v_sz);

__s8 elf_dtag_is_addr(__s64 dtag);
Elf_Dyn *elf_get_got_plt(elf_t *elf);
__u8 sym_fits_phdr(Elf_Sym *sym, Elf_Phdr *p);

__u64 get_unknown_sz_sym_sz(elf_t *elf, Elf_Sym *sym);
sym_obj *get_sym(elf_t *elf, __u8 *str);
sym_obj *make_sym_obj(elf_t *elf, Elf_Sym *sym);

