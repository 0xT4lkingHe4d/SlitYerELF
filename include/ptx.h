// #include <linux/types.h>
// #include "./llist.h"
// #include "./elf.h"
// #include "./pack.h"

// #ifndef PTX_H
// #define PTX_H
// typedef struct {
// 	elf_t	*elf;
// 	__u64 off, size;
// } ptx_src_t;

// typedef struct {
// 	__u64	id;
// 	__u16	type;

// 	ptx_src_t src;

// 	void	*mem;
// 	__u64	off, size;
// 	__u16	count;
// 	__u32	entry_size;
// } ptx_header_t;

// typedef struct {
// 	ptx_src_t src;
// 	void	*mem;
// 	__u64	off, size;
// } ptx_fill_t;

// typedef void (*ptx_fn_t)(pack_t *p, __u8 action, __u64 off, __u64 sz);

// typedef struct {
// 	__u16		type;
// 	ptx_fn_t	fn;
// } ptx_fn_tup;

// typedef struct {
// 	llist_t		headers;	// ptx_header_t
// 	llist_t		fills;		// ptx_fill_t

// 	llist_t		fn_type;	// ptx_fn_tup
// 	__u64		id_counter;
// } ptx_engine_t;

// void ptx_add_header(ptx_engine_t *ptx, __u8 t, elf_t *elf, void *ptr, __u64 count, __u64 hdr_sz);
// #endif