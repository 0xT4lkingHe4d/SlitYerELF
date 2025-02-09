#include <linux/types.h>
#include "../lib-x86-binary/x86.h"
#include "./utils.h"

#define PATCH_REPLACE	1
#define PATCH_ADD		2
#define PATCH_REL		3

#define REL_T_INSN	1
#define REL_T_DAT	2

#define REL_T_ELF		1
#define REL_T_MM		2

#ifndef REL_H
#define REL_H
typedef struct {
	__u8	type;
	elf_t	*elf;
	union {
		void	*ptr;
		mmsz_t	mm;
	};

	__u64 orig_off, orig_size;
	__u32 dst_off,	dst_size;

	__u64 off, size;
	
	__u64 base_off;
	__u64 base_virt;
} rel_patch_t;

struct patched_in {
	llist_t	ll;
	mmsz_t	sc;
};

typedef __s64 (*rel_hook_fn_t)(void *plugin, void *rel, rel_patch_t *p, __u64 orig_imm);
typedef __s64 (*rel_off_fn_t)(void *pack, rel_patch_t *rx, __u64 off);

typedef struct {
	llist_t		patches;
	llist_t		ll_hijack;
	struct patched_in pin;
	void			*plugin;
	rel_hook_fn_t	hook_fn;
	rel_off_fn_t	off_fn;
} rel_t;


#define REL_TYPE_DAT(t)		(t & 0xf)
#define REL_TYPE_PATCH(t)	(t >> 4)

#define rel_each_patch(rel, p)		\
		llist_each_dat(&(rel)->patches, rel_patch_t, p)

void rel_init(rel_t *rel);
mmsz_t *do_reloc(rel_t *rel);
__u64 rel_get_off(rel_t *rel, __u64 imm);
void rel_instr(rel_t *rel, mmsz_t *mm, rel_patch_t *p);
rel_patch_t *_rel_ll_(llist_t *ll, __u16 patch_type, __u8 rel_type, elf_t *elf, void *ptr, __u64 src, __u64 dst, __u64 orig_size, __u64 dst_size);
rel_patch_t *_rel_(rel_t *rel, __u8 t, elf_t *elf, void *ptr, __u64 src, __u64 dst, __u64 sz);

rel_patch_t *rel_insn(rel_t *rel, elf_t *elf, void *ptr, __u64 src, __u64 dst, __u64 sz);
rel_patch_t *rel_buff(rel_t *rel, elf_t *elf, void *ptr, __u64 src, __u64 dst, __u64 sz);
#endif