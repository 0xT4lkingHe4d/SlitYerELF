#include <linux/types.h>
#include "../lib-x86-binary/x86.h"
#include "./utils.h"

#define PATCH_REPLACE	1
#define PATCH_ADD		2
#define PATCH_REL		3

#define REL_T_INSN	5
#define REL_T_DAT	6

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


#define REL_HIJACK_STUB		1
#define REL_HIJACK_ADDR		2
#define REL_HIJACK_ARRAY	3

typedef __s8 (*rel_hijack_stub_fn)(void *h, void *rel, rel_patch_t *p, __u64 p_off, __u64 orig_imm);
typedef struct {
	__u8 type;
	union {
		__u64		v;
		__u64		addr;
		union {
			__u64	*off;
			mmsz_t	off_array;
		};
		rel_hijack_stub_fn	fn;
	};
} rel_hijack_target;

#define REL_HIJACK_DST_ELF	 1
#define REL_HIJACK_DST_SC	2
typedef struct {
	__u8 dst_type;
	union {
		struct {
			elf_t	*elf;
			__u64	off;
		};
		void *patch;	// sc / pack_patch_t
	} dst;

	llist_t	target;
} rel_hijack_t;

struct patched_in {
	llist_t	ll;
	mmsz_t	sc;
};

typedef __s64 (*rel_plugin_fn_t)(void *plugin, void *rel, rel_patch_t *p, __u64 v);
typedef __u64 (*rel_plugin_fn_addr_t)(void *pack, void *rel, elf_t *elf, __u8 t, __u64 v);
typedef struct {
	void *dat;		// eg. pack_t*
	rel_plugin_fn_t			off;
	rel_plugin_fn_t			virt;
	rel_plugin_fn_addr_t	addr;
} rel_plugin_t;

typedef struct {
	llist_t				patches;
	llist_t				ll_hijack;
	struct patched_in	pin;
	rel_plugin_t		plugin;
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
rel_patch_t *_rel_(rel_t *rel, __u8 pt, __u8 dt, elf_t *elf, void *ptr, __u64 src, __u64 dst, __u64 sz);


__u64 rel_hijack_ret(rel_t *rel, rel_hijack_t *h, rel_patch_t *p, __u64 orig_imm);
ok_t rel_get_hijack(rel_t *rel, rel_patch_t *p, __u64 p_off, __u64 orig_imm);
rel_hijack_t *rel_hijack(rel_t *rel, elf_t *elf, __u64 off, void *pack_patch);
rel_hijack_target *rel_hijack_add_target(rel_hijack_t *h, __u8 t, void *v);

rel_patch_t *rel_insn(rel_t *rel, __u8 t, elf_t *elf, void *ptr, __u64 src, __u64 dst, __u64 sz);
rel_patch_t *rel_buff(rel_t *rel, __u8 t, elf_t *elf, void *ptr, __u64 src, __u64 dst, __u64 sz);
#endif