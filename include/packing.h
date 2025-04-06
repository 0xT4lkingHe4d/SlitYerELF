#include <linux/types.h>
#include "./elf.h"
#include "./pack.h"
#include "./list.h"
#include "./utils.h"
#include "./rel_instr.h"

#ifndef PACKING_H
#define PACKING_H
typedef struct {
	__u64 orig_off;
	__u64 orig_sz;
	__u64 off;
	struct mmsz_tup mm;
} pack_fragment_t;

typedef struct {
	rel_patch_t	*rel;
	void		*dst;
	__u64		off;
} pack_fix_st;

typedef struct {
	elf_t *elf;
	__u8 f;
	__u64 orig_off,	dst_off;
	__u32 orig_sz,	dst_sz;
} pack_patch;

typedef struct {
	elf_t	*orig_elf;
	elf_t	elf;
	struct {
		struct mmsz_tup	mm;
		llist_t		rel;		// rel_patch_t
		llist_t		pack;		// pack_fragment_t
		llist_t		hdr;		// off_sz_t
		llist_t		fixes;
	} modif;
	struct {
		off_sz_t	*ptr;
		__u64		num;
	} hdr;
} pack_t;
#endif

__s8 import_elf(elf_t *elf, pack_t *p);
__s8 make_elf(pack_t *p, __u8 *output);
pack_fragment_t *p_add_patch_ll(llist_t *ll, void *ptr, __u64 off, __u64 sz);
pack_fragment_t *p_add_patch(pack_t *pack, void *ptr, __u64 off, __u64 sz);

void pack_insert(pack_t *pack, __u64 off, struct mmsz_tup *mm);
lle *_hdr_(pack_t *pack, elf_t *elf, __u8 f, __u64 orig_off, __u32 orig_sz, __u64 dst_off, __u32 dst_sz);
__s64 pack_ext_hdr(pack_t *p, __u64 off, __u64 sz);

#define for_each_orig_patch(pack_ptr, e)		\
		foreach_ll_T((&(pack_ptr)->modif.pack), e, pack_fragment_t)


#define for_each_patches_ll(ll, e)					\
		foreach_ll_T((ll), e, pack_fragment_t)

__s8 do_reloc(pack_t *pack);
__u64 rel_phdr_align(pack_t *p, __u64 virt);
__u64 rel_get_off(pack_t *pack, rel_patch_t *rel, __u64 off);
__u64 pack_get_virt(pack_t *pack, elf_t *elf, __u64 s_virt, __u64 d_virt);
__u64 pack_get_off(pack_t *pack, elf_t *elf, __u64 s_off, __u64 d_off);

__u64 pack_vtof(pack_t *p, elf_t *elf, __u64 v);
__u64 pack_ftov(pack_t *p, elf_t *elf, __u64 v);
__u64 pack_vtov(pack_t *p, elf_t *elf, __u64 v);
__u64 pack_ftof(pack_t *p, elf_t *elf, __u64 v);

rel_patch_t *pack_new_rel_t(pack_t *pack, __u64 d_off, elf_t *elf, __u64 s_off, __u64 sz);
rel_patch_t *pack_off_to_rel(pack_t *p, elf_t *elf, __u64 off);
rel_patch_t *pack_get_rel(pack_t *p, elf_t *elf, __u64 off);

lle *pack_fix_u64(pack_t *p, rel_patch_t *rel, void *dst, __u64 off);

#define MRG_CMP_ATTR(f, str) (!_qstrcmp(MRG_##f##_ATTR, str))
#define MRG_SYM_ATTR "\xca\xfe\xad\xd1\xc7@"
#define MRG_SYM 1

typedef struct {
	__u8	ok;
	__u64 s_off;
	__u64 d_off;
} merge_cpy_t;

typedef struct {
	elf_t	*orig_elf;
	elf_t	*modif_elf;
	rel_patch_t *m_rel, *s_rel;

	struct mmsz_tup mm_cpy;
	__u64			mm_cpy_num;
	llist_t	ll_target;
} merge_elf_t;

__s8 merge_elf_init(merge_elf_t *m);
__s8 merge_elf(pack_t *pack, merge_elf_t *m);



typedef struct {
	__u64 addr;
	__u64 *ptr;
} got_entry_t;

__s8 p_add_got_entry(pack_t *p, got_entry_t *got);
__u16 p_add_sym(pack_t *p, symtab_t *stab, __u8 *name, __u64 len, Elf_Sym *sym);
__u16 p_add_rela(pack_t *p, rela_t *rtab, Elf_Rela *rela);
__u16 p_add_gnu_versym(pack_t *p, __u16 v);