#include <stdlib.h>
#include <string.h>
#include "../include/llist.h"
#include "../include/utils.h"
			
#define _ll_twine_(a, b, c) ({		\
		_ll_connect_(a, b);			\
		_ll_connect_(b, c);			\
})

#define _ll_connect_(a, b) ({		\
		(a)->next = (b);			\
		(b)->prev = (a);			\
})

lle *llist_last(llist_t *ll) {
	lle *ret = NULL;
	llist_each(ll, e) ret=e;
	return ret;
}

lle *llist_add(llist_t *ll, lle *e_prev, lle *e_next, void *dat) {
	_assert(ll->size > 0, "LList not created");
	lle *new	= xmalloc(sizeof(lle));
	lle *last	= llist_last(ll);

	_ll_twine_((!last) ? ll->head : last, new, ll->tail);

	new->dat = xmalloc(ll->size);
	memcpy(new->dat, dat, ll->size);
	
	return new;
}

lle *llist_add(llist_t *ll, void *dat) {
	return llist_add_pos((!last) ? ll->head : last, ll->tail);
}


void llist_free_elem(llist_t *ll, lle *e) {
	free(e->dat);
	_ll_connect_(e->prev, e->next);
	free(e);
}

void llist_free_all(llist_t *ll) {
	llist_each(ll, e) llist_free_elem(ll, e);
}

void llist_free(llist_t *ll) {
	llist_free_all(ll);
	free(ll);
}

void llist_new(llist_t *ll, __u64 size) {
	ll->size = size;
	ll->head = xmalloc(sizeof(lle));
	ll->tail = xmalloc(sizeof(lle));
	_ll_connect_(ll->head, ll->tail);
}