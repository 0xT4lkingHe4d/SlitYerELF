#include <linux/types.h>

#ifndef LLIST_H
#define LLIST_H
struct llist_elem {
	__u8	t;
	void	*dat;
	struct llist_elem *next, *prev;
};
typedef struct llist_elem lle;

typedef struct {
	struct llist_elem *head, *tail;
	__u64	size;
} llist_t;

#define llist_each(ll, e)							\
		for (lle *e = (ll)->head->next;				\
			!!e && !!e->next && e != (ll)->tail ;	\
			e=e->next)


#define llist_each_dat(ll, T, e)		\
	llist_each(ll, _e)					\
		for (T *e = _e->dat; !!e; e=NULL)

lle *llist_last(llist_t *ll);
lle *llist_add(llist_t *ll, void *dat);
void llist_new(llist_t *ll, __u64 size);
void llist_free_elem(llist_t *ll, lle *e);
void llist_free_all(llist_t *ll);
void llist_free(llist_t *ll);
#endif