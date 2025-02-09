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
		xprf(ERR, s, __VA_ARGS__);			\
		xprf(ERR, "errno %lx (%s)\n", errno, strerror(errno));	\
		exit(-1);							\
	}

#define PR_ERR		BRED "  [ERR]  :"CRST
#define PR_INFO		BBLUE"  ( i )  :"CRST
#define PR_WARN		BYLW "  [WARN] :"CRST
#define PR_DBG		BGRN "  [+++]  :"CRST

#define xprf(t, str, ...)			\
		prf(PR_##t str, __VA_ARGS__);

#define _contain_(a, sz, off)		(a <= off && (a + sz) > off)
#define _contains_(a, sz1, b, sz2)	(a <= b && (a + sz1) >= (b + sz2))
#define _crossed_(a, sz1, b, sz2)	((a >= b && a < b + sz2) || (b >= a && b < a + sz1))

void hexdump(void *addr, __u64 sz);
void *map_anon(__u64 sz);
void *map_anon_shared(__u64 sz);

void _die(__u8 *s);
void *xmalloc(__u64 sz);
__s8 is_string(void *addr);
__s8 file_exists(__u8 *file);
__u64 _wr(int fd, __u64 off, __u8 *src, __u64 len);
__u64 _rd(int fd, __u64 off, __u8 *src, __u64 len);


#define MEM_NONE		0
#define MEM_HEAP		1
#define MEM_MMAP		2

#endif