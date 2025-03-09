#include <linux/types.h>
#include "./mem.h"

#define F_LL_MMAP	3
#define F_LL_MALLOC	1

#define LL_HEAD 0x1
#define LL_TAIL 0xf

#ifndef LIST_H
#define LIST_H
struct lnode_st {
	__u8	type;
	struct lnode_st *next;
	struct lnode_st *prev;

	__u8	mem_type;
	void	*dat;
	__u64	sz;
};
typedef struct lnode_st lle;

typedef struct {
	lle *head;
	lle *tail;
	__u64 num;
} llist_t;
#endif

#define _OR_(a, b) ((!!a) ? a : b)


#define ll_each(ll, e) foreach_ll((ll), _e_) if (e=((_e_)->dat))

#define foreach_ll(ll, x)															\
		for (lle *x = ((ll)->head->next->type == LL_TAIL) ? NULL : (ll)->head->next;	\
			!!x && !!x->next && x->type != LL_TAIL;									\
			x = _OR_(x->next, 0))

#define foreach_ll_T(ll, x, T)			\
			for (T *x = NULL; !x; x=1) foreach_ll(ll, _e_) if (x = _e_->dat)

#define foreach_ll_reverse(ll, x)													\
		for (lle *x = ((ll)->tail->prev->type == LL_HEAD) ? NULL : (ll)->tail->prev;	\
			!!x && !!x->prev && x->type != LL_HEAD;									\
			x = _OR_(x->prev, 0))

lle *ll_get_last(llist_t *ll);
lle *llist_add(llist_t *ll, __u8 flags, void *dat, __u64 sz);
void llist_new(llist_t *ll);
llist_t *new_ll();
void lle_free(llist_t *ll, lle *e);
void free_ll_content(llist_t *ll);