#include <linux/types.h>
#include "../lib-x86-binary/x86.h"
#include "./llist.h"
#include "./utils.h"
#include "./rel_instr.h"

#define ELF_VIRT	1
#define ELF_OFF		2

#define ELF_T_EHDR		1
#define ELF_T_PHDR		2
#define ELF_T_SHDR		3
#define ELF_T_DYN		4
#define ELF_T_REL		5
#define ELF_T_RELA		6
#define ELF_T_SYM		7
#define ELF_T_STRTAB	8

#define PTX_T_FILL		1
#define PTX_T_HEADER	2

#ifndef PACK_H
#define PACK_H
typedef struct {
	elf_t	*elf;
	__u64 off, size;
} ptx_src_t;

typedef struct {
	ptx_src_t src;		// The order i fucking important
	mmsz_t	mm;
	__u64	off;

	__u16	type;
	__u16	count;
	__u32	entry_size;
} ptx_header_t;

typedef struct {
	ptx_src_t src;
	mmsz_t	mm;
	__u64	off;
} ptx_patch_t;

typedef ptx_patch_t ptx_fill_t;

typedef struct ptx_engine_st {
	llist_t		headers;	// ptx_header_t
	llist_t		fills;		// ptx_fill_t
	llist_t 	patches;	// ptx_patch_t
} ptx_engine_t;

typedef struct {
	__u8	type;
	lle		*list_elem;
} ptx_patch_tup;

typedef struct {
	ptx_patch_tup	patch;
	rel_t			rel;
} ptx_rel_t;

typedef struct {
	elf_t			*out_elf;
	llist_t			ll_rel;	// ptx_rel_t
	ptx_engine_t	ptx;
} pack_t;

// typedef void (*ptx_fn_t)(pack_t *p, ptx_ctx_t *ctx);

// typedef struct {
// 	__u16		type;
// 	ptx_fn_t	fn;
// } ptx_fn_tup;

#define ptx_each_entry(p, T, e)							\
		for (__u16 _i_ = 0; _i_ < p->count; _i_++)		\
			for (T *e=(void*)p->mm.mem + (_i_ * p->entry_size); !!e; e=NULL)

#define patch_each_x(_p_, f, T, v, hdr)				\
		patch_each(_p_, f, T, v)

#define patch_each(_p_, f, T, v)					\
		ptx_each_header(&(_p_)->ptx, hdr)			\
			if (hdr->type == ELF_T_##f)				\
				ptx_each_entry(hdr, T, v)


__u64 pack_mem_conv(pack_t *p, __u8 from, __u8 to, __u64 n);
#define pack_vtof(p, virt)	pack_mem_conv((p), ELF_VIRT, ELF_OFF, virt)
#define pack_ftov(p, off)	pack_mem_conv((p), ELF_OFF, ELF_VIRT, off)
#define pack_vtov(p, virt)	pack_mem_conv((p), ELF_VIRT, ELF_VIRT, virt)
#define pack_ftof(p, off)	pack_mem_conv((p), ELF_OFF, ELF_OFF, off)

// void pack_cut_elf(pack_t *p);
// void pack_add_header(pack_t *p, __u64 off, void *ptr, __u64 sz);
// __u64 *pack_qword_ptr(pack_t *p, __u64 off);
// void pack_reloc_dynamic(pack_t *p, patch_header_t *e, __u64 off, __s64 sz);


#define pack_base_vtof(p, elf, v)	pack_base_off(p, elf, ELF_VIRT, ELF_OFF, v)
#define pack_base_ftof(p, elf, v)	pack_base_off(p, elf, ELF_OFF, ELF_OFF, v)
#define pack_base_ftov(p, elf, v)	pack_base_off(p, elf, ELF_OFF, ELF_VIRT, v)
#define pack_base_vtov(p, elf, v)	pack_base_off(p, elf, ELF_VIRT, ELF_VIRT, v)

void ptx_init(ptx_engine_t *ptx);
__s8 pack_load_elf(pack_t *pack, __u8 *file);

#define ptx_each_header(ptx, i)			\
		for (ptx_header_t *i = NULL; !!(i = ptx_header_next((ptx), i)); )

#define ptx_each_fill(ptx, f)			\
		llist_each_dat(&(ptx)->fills, ptx_fill_t, f)

#define ptx_each_any(p, e)						\
		for (llist_t *ll = NULL; !ll; )			\
			for (ptx_header_t *e = NULL; !e; )	\
				ptx_each_any_ll(p, ll, undefined, elem) if (e=elem->dat)

#define ptx_each_any_ll(p, ll, _t_, e)			\
		for (__u8 _l_ = 0, _t_=0; !_l_;)				\
			for (llist_t *_ll_[2][2] = {{&(p)->ptx.fills, PTX_T_FILL}, {&(p)->ptx.headers, PTX_T_HEADER}}; _l_<=1; _l_++)	\
				if ((_t_=_ll_[_l_][1]))llist_each((ll = _ll_[_l_][0]), e)


ptx_header_t *ptx_header_next(ptx_engine_t *ptx, ptx_header_t *min);
void ptx_add_header(ptx_engine_t *ptx, __u8 t, elf_t *elf, void *ptr, __u64 count, __u64 hdr_sz);
__s8 make_elf(pack_t *p, __u8 *output);
ptx_header_t *ptx_type(ptx_engine_t *ptx, __u16 t);
void pack_split_chunk(pack_t *pack, __u64 size);
void ptx_fill(pack_t *p, elf_t *elf, __u64 s_off, __u64 s_sz);
__s8 ptx_stick_in(pack_t *pack, ptx_patch_tup *ret, __u64 off, __u64 size);
void ptx_split(pack_t *p, void *ptr, __u64 off);
__u64 pack_base_off(pack_t *pack, elf_t *elf, __u8 st, __u8 dt, __u64 v);
__s64 pack_rel_off(pack_t *pack, rel_patch_t *rx, __u64 off);
ptx_rel_t *ptx_get_rel(pack_t *pack, __u64 off, __u64 size);
void pack_get_src(pack_t *p, ptx_src_t *ret, __u64 off);
void pack_reloc(pack_t *pack);
__s64 pack_rel_value(pack_t *pack, rel_t *rel, rel_patch_t *p, __u64 orig_imm);
rel_t *pack_new_rel(pack_t *pack, __u64 off);

#endif