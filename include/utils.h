#include <linux/types.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>

#ifndef UTILS_H
#define UTILS_H
#define BRED	"\e[1;31m"
#define RED		"\e[0;31m"
#define BGRN	"\e[1;32m"
#define GRN		"\e[0;32m"
#define BBLUE	"\e[1;34m"
#define BLUE	"\e[0;34m"
#define YLW		"\e[0;33m"
#define BYLW	"\e[1;33m"
#define CYAN	"\e[0;36m"
#define BCYAN	"\e[1;36m"
#define WHT		"\e[0;37m"
#define BWHT	"\e[1;37m"
#define CRST	"\e[0m"

#define color(c, str)	c str CRST

#define prf printf
#define pr	puts

#define PAGE_SZ	0x1000
#define PAGE_MASK (~(PAGE_SZ-1))
#define PAGE_ALIGN(x)	(( (x) + PAGE_SZ -1) & PAGE_MASK)
#define BIT_MASK(n)		(( 1ull << (n) ) -1)
#define ALIGN(v, align)	(( (v) + ((align)-1)) & ~((align)-1))

#define PROT_R		PROT_READ
#define PROT_RW		PROT_READ | PROT_WRITE
#define PROT_RE		PROT_READ | PROT_EXEC
#define PROT_RWE	PROT_READ | PROT_WRITE | PROT_EXEC

#define _assert(b, s) if (!(b)) _die(s);
#define _assertf(b, s, ...) if (!(b)) {		\
			xprf(ERR, s, __VA_ARGS__);		\
			xprf(ERR, "errno %lx (%s)\n", errno, strerror(errno));	\
			exit(-1);						\
		}

#define PR_ERR		BRED "  [ERR]  : "CRST
#define PR_INFO		BBLUE"  ( i )  : "CRST
#define PR_WARN		BYLW "  [WARN] : "CRST
#define PR_DBG		BGRN "  [+++]  : "CRST

#define xprf(t, str, ...)	prf(PR_##t str, __VA_ARGS__);
#define xpr(t, str)			pr(PR_##t str);


#define _contain_(a, sz, off)		(a <= off && (a + sz) > off)
#define _contains_(a, sz1, b, sz2)	(a <= b && (a + sz1) >= (b + sz2))
#define _crossed_(a, sz1, b, sz2)	((a >= b && a < b + sz2) || (b >= a && b < a + sz1))

#define foreach(arr, e, type)		\
		for (type *e = &arr[0]; e < &arr[sizeof(arr)/sizeof(type)]; e++)

#define _zero(ptr, sz) { memset(ptr, 0, sz); }

#define DIE(str)		{ perror(str); exit(-1); }
#define FDIE(str, ...)	{ printf(str "\n", __VA_ARGS__); exit(-1); }

__s8 file_exists(__u8 *file);
__u64 _wr(int fd, __u64 off, __u8 *src, __u64 len);
__u64 _rd(int fd, __u64 off, __u8 *src, __u64 len);
void *map_anon(__u64 sz);
void *xmalloc(__u64 sz);

#define MEM_NONE		0
#define MEM_HEAP		1
#define MEM_MMAP		2
#define MEM_ANY			3

#define MMSZ_TYPE(t, sz)	((t==MEM_ANY) ? ((sz > 0x1000) ? MEM_MMAP : MEM_HEAP) : t)

typedef struct {
	__u8	*mem;
	__u8	t;
	__u64	size;
	__u64	off;
} mmsz_t;

mmsz_t *new_mmsz(__u8 t, __u64 size);
void make_mmsz(mmsz_t *mm, __u8 t, __u64 size);
void mmsz_resz(mmsz_t *mm, __u64 add);
void mmsz_free(mmsz_t *mm);

#endif