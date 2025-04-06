#include "../include/main.h"

void fix_jmp(__u8 *ptr, __u32 v) {
	_assert(*ptr == u'\xe9', "Not a fucking JMP");
	*((__u32 *)(ptr+1)) = v;
}

__s8 sym_ll_is_done(llist_t *syms) {
	foreach_ll(syms, e) {
		struct sym_off_sz_t *st = e->dat;
		if (st->off < st->sz) return 0;
	}
	return 1;	
}
