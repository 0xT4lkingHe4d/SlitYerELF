#include <sys/mman.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/pack.h"
#include "../../include/utils.h"
#include "../../include/list.h"

#define DST_ADDR 	1
#define DST_FD		2

/* rewrite list */
typedef struct {
	__u8 dst_t;
	union {
		void	*dst;
		__u64	fd;
	};
	__u64 	soff;
	void	*src;
	__u64 	sz;
	llist_t patches;
} rl_t;

#define mem_sz(sz)	(((sz) < 0x1000) ? MEM_HEAP : MEM_MMAP)

struct mmsz_tup *new_mmsz_tup(__u64 sz) {
	struct mmsz_tup *m = xmalloc(sz);
	new_mmsz_t(m, 0, sz);
	return m;
}

__s8 mmsz_alloc(struct mmsz_tup *mm, __u64 sz) {
	if (mm->t != MEM_NONE) return 0;
	cpy_new_mmsz_t(mm, mem_sz(sz), mm->mem, sz);
	return 0;
}

__s8 new_mmsz_t(struct mmsz_tup *mm, __u8 t, __u64 sz) {
	_zero(mm, sizeof(mmsz_tup));
	if (!t) t = mem_sz(sz);
	switch ((mm->t = t)) {
		case MEM_HEAP:	mm->mem = xmalloc(sz);		break;
		case MEM_MMAP:	mm->mem = map_anon(sz);		break;
		default: DIE("FUCK!");
	}
	mm->sz = sz;
	return 1;
}

__s8 cpy_new_mmsz_t(struct mmsz_tup *mm, __u8 t, void *src, __u64 sz) {
	if (!new_mmsz_t(mm, t, sz)) return -1;
	memcpy(mm->mem, src, sz);
	return 0;
}

bool new_mmsz(struct mmsz_tup *mmsz, __u64 sz) {
	void *map = map_anon(sz);
	if (map == MAP_FAILED) return -1;
	memset(map, 0, sz);

	mmsz->t		= MEM_MMAP;
	mmsz->mem	= map;
	mmsz->sz	= sz;
	return 0;
}

bool new_mmsz_cpy(struct mmsz_tup *mmsz, void *src, __u64 sz) {
	if (new_mmsz(mmsz, sz) == -1) return -1;
	mmsz_memcpy(mmsz, src, sz);
	return 0;
}

void *mmsz_memcpy(struct mmsz_tup *mmsz, void *src, __u64 sz) {
	if (sz > mmsz->sz) return NULL;
	return memcpy(mmsz->mem, src, sz);
}

void mmsz_hexdump(struct mmsz_tup *mmsz) {
	_hexdump(mmsz->mem, mmsz->sz);
}

void mmsz_zero(struct mmsz_tup *mmsz) {
	memset(mmsz->mem, 0, mmsz->sz);
}


// void *mmsz_realloc(struct mmsz_tup *mmsz, __u64 sz) {
// 	void *tmp = malloc(sz);
// 	if (!tmp) return (void*)-1;

// 	memset(tmp, 0, sz);
// 	memcpy(tmp, mmsz->mem, mmsz->sz);
// 	free(mmsz->mem);

// 	*mmsz = (struct mmsz_tup){
// 		.mem = tmp,
// 		.sz	 = sz,
// 	};

// 	return mmsz->mem;
// }

void free_mmsz(struct mmsz_tup *mm) {
	switch (mm->t) {
		case MEM_MMAP:
			munmap(mm->mem, mm->sz);
			break;
		case MEM_HEAP:
			free(mm->mem);
			break;
	}

	mm->mem	= NULL;
	mm->sz	= 0;
}

__s8 resz_mm(mm_t *mm, __u64 add) {
	if (!mm || !mm->mem) return -1;
	void *map = map_anon(mm->sz + add);
	if (!map) return -1;

	memcpy(map, mm->mem, mm->sz);
	switch (mm->t) {
		case MEM_MMAP: munmap(mm->mem, mm->sz);	break;
		case MEM_HEAP: free(mm->mem);			break;
	}

	mm->t	= MEM_MMAP;
	mm->mem = map;
	mm->sz += add;
	return 0;
}

__s8 resz_mmsz(struct mmsz_tup *mm, __u8 t, __u64 add) {
	if (!mm || !mm->mem) return -1;
	void *ptr	= NULL;
	__u64 sz	= mm->sz + add;

	switch ((t = (!t ? mem_sz(sz) : t))) {
		case MEM_HEAP:	ptr = xmalloc(sz);		break;
		case MEM_MMAP:	ptr = map_anon(sz);		break;
	}

	memcpy(ptr, mm->mem, mm->sz);
	free_mmsz(mm);

	*mm = (struct mmsz_tup){
		.t = t, .mem = ptr, .sz = sz
	};
	return 0;
}

void just_stick_in(__u8 **dst, void *src, __u64 sz) {
	memmove(*dst, src, sz);
	*dst += sz;
}

void *stick_in(void *dst, void *src, __u64 sz, __u64 *off) {
	memcpy(dst + ((!off) ? 0 : *off), src, sz);
	if (!!off) *off += sz;
	return dst;
}

void mmsz_stick_in(void *dst, struct mmsz_tup *mmsz, __u64 *off) {
	stick_in(dst, mmsz->mem, mmsz->sz, off);
}

int wr_output(__u8 *output, void *mem, __u64 sz) {
	int fd = open(output, O_CREAT|O_RDWR, 0755);
	if (fd == -1) return -1;
	write(fd, mem, sz);
	close(fd);
	prf("[+] Written 0x%lx / %1$lu into '%s'\n", sz, output);
	return 0;
}
