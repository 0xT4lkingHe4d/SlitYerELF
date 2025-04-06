#include <linux/types.h>
#include <sys/mman.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "../../include/utils.h"
#include "../../include/list.h"


#define _ll_twine_(a, b, c) ({		\
		_ll_connect_(a, b);			\
		_ll_connect_(b, c);			\
})

#define _ll_connect_(a, b) ({		\
		a->next = b;				\
		b->prev = a;				\
})


lle *ll_get_last(llist_t *ll) {
	lle *last = NULL;
	foreach_ll(ll, e) last = e;
	return (!last) ? ll->head : last;
}

lle *llist_add(llist_t *ll, __u8 flags, void *dat, __u64 sz) {
	ll->num++;
	lle *new	= xmalloc(sizeof(lle));
	lle *last	= ll_get_last(ll);
	_ll_twine_(last, new, ll->tail);
	
	new->sz = sz;
	new->mem_type = flags;
	switch (flags) {
		case F_LL_MMAP:
			new->dat = map_anon(sz);
			new->sz	 = PAGE_ALIGN(sz);
			break;
		case F_LL_MALLOC:
			new->dat = xmalloc(sz);
			break;
		default:
			new->dat = dat;
			return new;
	}
	if (!!dat) memcpy(new->dat, dat, sz);

	return new;
}

void lle_free(llist_t *ll, lle *e) {
	if (e->type == LL_HEAD || e->type == LL_TAIL) return;
	if (!!e->dat) {
		switch (e->mem_type) {
			case F_LL_MMAP:		munmap(e->dat, e->sz);	break;
			case F_LL_MALLOC:	free (e->dat);			break;
		}
	}

	_ll_connect_(e->prev, e->next);
	free (e);
	ll->num--;
}

void free_ll_content(llist_t *ll) {
	foreach_ll(ll, e) lle_free(ll, e);
	free (ll->head);
	free (ll->tail);
	// free (ll);
}

void llist_new(llist_t *ll) {
	*ll = (llist_t){
		.head	= xmalloc(sizeof(lle)),
		.tail	= xmalloc(sizeof(lle)),
		.num = 0,
	};
	ll->head->type = LL_HEAD;
	ll->tail->type = LL_TAIL;
	_ll_connect_(ll->head, ll->tail);
	_ll_connect_(ll->tail, ll->head);
}

llist_t *new_ll() {
	__u8 *tmp = xmalloc(sizeof(llist_t));
	llist_new(tmp);
	return tmp;
}


