#include <linux/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <errno.h>
#include "../include/utils.h"

void _die(__u8 *s) {
	prf("[-!-] FAILED - %s\n", s);
	prf("         - errno (%02x) - %s\n", errno, strerror(errno));
	pr("");
	exit(-1);
}

static __u8 *hexdump_char_color(__u8 c) {
	__u8 *clr = CRST;
	if (isprint(c)) {
		clr = BLUE;
	} else if (isspace(c) || !c) {
		clr = RED;
	} else if (c == 0xff) {
		clr = GRN;
	}
	return clr;
}

void hexdump(void *addr, __u64 sz) {
	__u8 *ptr = addr;

	for (__u64 i = 0; i <= sz; i++) {
		__u8 ch = ptr[i];

		if ( ( !(i % 0x10) && i) || i >= sz) {
			__u8 n = 0x10;

			if (i >= sz) {
				n = !(sz % 0x10) ? 0x10 : (sz % 0x10);
				for (int x = n; x < 0x10; x++) {
					if (!(i % 4)) prf("  ");
					prf("   ");
				}
			}

			prf("\t|\t");

			for (__u8 l = 0; l < n; l++) {
				__u8 c = ptr[ (i-n)+l ];
				__u8 *clr = hexdump_char_color(c);
				prf("%s%c" CRST, clr, isprint(c) ? c : '.');
			}

			pr("");
			if (i >= sz) return;
		}

		if (!i || !(i % 0x10))
			prf(CRST "0x%06x :\t", i);

		if ( !(i % 4) && i && (i % 0x10))
			prf("| ");

		__u8 *clr = hexdump_char_color(ptr[i]);
		prf("%s%02x " CRST, clr, ch);
	}
}

__s8 file_exists(__u8 *file) {
	struct stat stats = {0};
	__s8 r = stat(file, &stats);
	errno = 0;
	return !r;
}

__u64 _wr(int fd, __u64 off, __u8 *src, __u64 len) {
	__u64 ret = pwrite(fd, src, len, off);
	_assertf((len == ret), "pwrite - %lx != %lx", len, ret);
}

__u64 _rd(int fd, __u64 off, __u8 *src, __u64 len) {
	__u64 ret = pread(fd, src, len, off);
	_assertf((len == ret), "pread - %lx != %lx", len, ret);
}

void *map_anon(__u64 sz) {
	void *map = mmap(0, sz, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	memset(map, 0, sz);
	return map;
}

void *map_anon_shared(__u64 sz) {
	void *map = mmap(0, sz, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
	memset(map, 0, sz);
	return map;
}

void *xmalloc(__u64 sz) {
	void *ret = malloc(sz);
	_assertf((!!ret), "Malloc got fucked! sz (0x%lx)", sz);
	memset(ret, 0, sz);
	return ret;
}

__s8 is_string(void *addr) {
	for (__u8 *ptr = addr; (__u64)ptr < PAGE_ALIGN((__u64)addr); ptr++) {
		if (ptr != addr && *ptr == '\0') return 1;
		if (!isprint(*ptr)) return 0;
	}
	return 0;
}

mmsz_t *new_mmsz(__u8 t, __u64 size) {
	mmsz_t *ret = xmalloc(sizeof(mmsz_t));
	make_mmsz(ret, t, size);
	return ret;
}

void make_mmsz(mmsz_t *mm, __u8 t, __u64 size) {
	*mm = (mmsz_t){ .t=MMSZ_TYPE(t, size), .size=size };
	switch (mm->t) {
		case MEM_HEAP: mm->mem = xmalloc(size);	break;
		case MEM_MMAP: mm->mem = map_anon(size);break;
	}
}

void mmsz_alloc(mmsz_t *mm) {
	if (mm->t != MEM_NONE) return;

	void *ptr = NULL;
	mm->t = MMSZ_TYPE(MEM_ANY, mm->size);
	switch (mm->t) {
		case MEM_HEAP: ptr = xmalloc(mm->size);		break;
		case MEM_MMAP: ptr = map_anon(mm->size);	break;
	}

	memcpy(ptr, mm->mem, mm->size);
	mm->mem	= ptr;
}

void mmsz_resz(mmsz_t *mm, __u64 add) {
	void *ptr = mm->mem;

	switch (mm->t) {
		case MEM_NONE: mmsz_alloc(mm);	// no break
		case MEM_HEAP:
		{
			if (mm->size + add >= 0x1000) {
				mm->t	= MEM_MMAP;
				mm->mem = map_anon(mm->size + add);
				memcpy(mm->mem, ptr, mm->size);
				free(ptr);
			} else {
				mm->mem = realloc(mm->mem, mm->size+add);
			}
			mm->size += add;
		}
		break;
		case MEM_MMAP:
		{
			if (mm->size + add >= PAGE_ALIGN(mm->size)) {
				mm->mem = map_anon(mm->size + add);
				memcpy(mm->mem, ptr, mm->size);
				munmap(ptr, PAGE_ALIGN(mm->size));
			}
			mm->size += add;
		}
		break;
	}
}


void mmsz_free(mmsz_t *mm) {
	switch (mm->t) {
		case MEM_MMAP:
			munmap(mm->mem, mm->size);
			break;
		case MEM_HEAP:
			free(mm->mem);
			break;
	}

	mm->mem	= NULL;
	mm->size	= 0;
}