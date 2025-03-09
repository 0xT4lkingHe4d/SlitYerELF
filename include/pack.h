#include <linux/types.h>
#include <fcntl.h>

#define MEM_NONE 0
#define MEM_MMAP 1
#define MEM_HEAP 2

#ifndef UAPI_
#define UAPI_
typedef __s8 bool;
typedef unsigned long long u64;
#define NULL (void*)0
#endif

#ifndef PACK_H
#define PACK_H
typedef struct mmsz_tup {
	__u8	*mem;
	__u8	t;
	__u64	sz;
} mmsz_tup;


typedef struct {
	__u64 off;
	__u64 sz;
} off_sz_t;

typedef struct {
	__u64 off;
	struct mmsz_tup *mm;
} off_mmsz_t;

typedef struct {
	__u8	t;
	__u8	*mem;
	__u64	sz;
	__u64	off;
} mm_t;
#endif

bool new_mmsz(struct mmsz_tup *, __u64);
__s8 mmsz_alloc(struct mmsz_tup *mm, __u64 sz);
struct mmsz_tup *new_mmsz_tup(__u64 sz);
__s8 new_mmsz_t(struct mmsz_tup *mm, __u8 t, __u64 sz);
__s8 cpy_new_mmsz_t(struct mmsz_tup *mm, __u8 t, void *src, __u64 sz);
bool new_mmsz_cpy(struct mmsz_tup *mmsz, void *src, __u64 sz);
void free_mmsz(struct mmsz_tup *mm);
void *mmsz_memcpy(struct mmsz_tup *, void *, __u64);
void mmsz_hexdump(struct mmsz_tup *);
void *mmsz_realloc(struct mmsz_tup *, __u64 );
void *stick_in(void *, void *, __u64, __u64 *);
void mmsz_stick_in(void *, struct mmsz_tup *, __u64 *);
int wr_output(__u8 *, void *, __u64);
void mmsz_zero(struct mmsz_tup *mmsz);
void just_stick_in(__u8 **dst, void *src, __u64 sz);
__s8 resz_mmsz(struct mmsz_tup *mm, __u8 t, __u64 add);
__s8 resz_mm(mm_t *mm, __u64 add);

