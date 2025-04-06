#include <linux/types.h>
#include "./elf.h"
#include "./list.h"
#include "./pack.h"

#define PATCH_REMOVE	1
#define PATCH_ADD		2
#define PATCH_REPLACE	3
#define PATCH_REL		4		// Block
#define PATCH_EXT		5
#define P_F_INNER		0x10
#define P_F_MAIN		0x20

#define REL_T_ELF		1
#define REL_T_MM		2

#define REL_MAP_CREAT	0x10

#ifndef _REL_INSTR_H
#define _REL_INSTR_H
typedef struct {
	__u8	t;
	elf_t	*elf;
	struct mmsz_tup	mm_src;
	struct mmsz_tup mm_dst;
	llist_t	patches;
} rel_t;


#define HOOK_T_ORIG		1
#define HOOK_T_DST		2
#define HOOK_T_TOKEN	3

struct rel_hook {
	__u8 t;
	__u64 src;
	__u64 v;
};

typedef struct {
	__u8 t;
	struct mmsz_tup	*mm;	// PATCH_ADD

	__u64 orig_off, dst_off;
	__u32 orig_sz,	dst_sz;
	__u64 off, sz;

	llist_t		ll_hook;
	__u8 any;
	llist_t		patches;
} patches_t;

struct patched_in {
	llist_t		ll;
	mm_t		sc;
};

struct rel_hijack {
	__u64	orig_vaddr;
	__u64	dst_off;
};

typedef struct {
	__u32	flags;
	struct {
		elf_t	*elf;
		__u64	off;
		__u64	sz;
	} src;
	struct patched_in	*pin;
	llist_t				ll_hijack;

	struct {
		__u64 off;
		__u64 sz;
		struct mmsz_tup *shared_mm;
		llist_t	patches;		// patches_t

		__s64	align;
	} out;

} rel_patch_t;
#endif

// #define pack_each_rel(pack, rel_e)		\
// 		foreach_ll_T(&(pack)->modif.rel, rel_e, rel_patch_t)

#define for_each_patches(ll, p)					\
		for (patches_t *p = NULL; !!(p = get_first_patch((ll), p)); )


#define for_each_rel(p, s_elf, x)					\
			for (rel_patch_t *x = NULL; !x; x=1)	\
				foreach_ll((&(p)->modif.rel), _e_)	\
					if ((x = _e_->dat)->src.elf == s_elf || !s_elf)

patches_t *get_first_patch(llist_t *ll, patches_t *min);
lle *_rel_(llist_t *ll, __u8 t, __u64 src_off, __u32 src_sz, __u64 dst_off, __u64 dst_sz);
lle *_rel_add_(llist_t *ll, __u8 t, struct mmsz_tup *mm, __u64 dst_off, __u64 dst_sz);
struct rel_hook *_rel_hook_(patches_t *p, __u8 t, __u64 src, __u64 v);
