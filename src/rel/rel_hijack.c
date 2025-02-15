#include <linux/types.h>
#include "../../include/rel_instr.h"
#include "../../include/llist.h"
#include "../../lib-x86-binary/x86.h"

__u64 rel_hijack_ret(rel_t *rel, rel_hijack_t *h, rel_patch_t *p, __u64 orig_imm) {
	switch (h->dst_type) {
		case REL_HIJACK_DST_ELF:
			__u64 ret = rel->plugin.addr(rel->plugin.dat, rel, h->dst.elf, ELF_OFF, h->dst.off);
			ret -= rel->plugin.off(rel->plugin.dat, rel, p, p->base_off);
			return ret;
		// case REL_HIJACK_DST_SC:
		// 	return rel->plugin.addr(rel->plugin.dat, rel, h->dst.elf, ELF_OFF, h->dst.off);
	}
	return -1;
}

ok_t rel_get_hijack(rel_t *rel, rel_patch_t *p, __u64 p_off, __u64 orig_imm) {
	llist_each_dat(&rel->ll_hijack, rel_hijack_t, h) {
		llist_each_dat(&h->target, rel_hijack_target, t) {
			switch (t->type) {
				case REL_HIJACK_ARRAY:
					__u64 i = 0;
					__u64 *arr = t->off_array.mem;
					for_range(i, t->off_array.size) {
						if (arr[i] == p->orig_off + p_off)
							goto retn;
					}
					break;

				case REL_HIJACK_ADDR:
					if (t->addr == orig_imm) goto retn;
					break;

				case REL_HIJACK_STUB:
					if (t->fn(h, rel, p, p_off, orig_imm));
						goto retn;
			}
		}
		continue;
		retn:
			__s64 ret = rel_hijack_ret(rel, h, p, orig_imm);
			return _OK((ret != -1), ret);
	}
	return _OK(0, -1);

}

rel_hijack_t *rel_hijack(rel_t *rel, elf_t *elf, __u64 off, void *patch) {
	rel_hijack_t h = {
		.dst_type	= (!!elf) ? REL_HIJACK_DST_ELF : REL_HIJACK_DST_SC,
		.dst		= {.elf=elf, .off=off}
	};
	llist_new(&h.target, sizeof(rel_hijack_target));
	if (!!patch) h.dst.patch = patch;
	
	lle *e = llist_add(&rel->ll_hijack, &h);
	return (!e) ? NULL : e->dat;
}

rel_hijack_target *rel_hijack_add_target(rel_hijack_t *h, __u8 t, void *v) {
	rel_hijack_target target = { .type = t, .v = v, };
	if (t == REL_HIJACK_ARRAY) {
		make_mmsz(&target.off_array, MEM_HEAP, sizeof(__u64));
		target.off[0] = v;
	}

	lle *e = llist_add(&h->target, &target);
	return (!e) ? NULL : e->dat;
}
