#include "./utils.h"
#include "./pack.h"
#include "./elf.h"
#include "./rel_instr.h"

#ifndef TRAP
#define TRAP() asm("int3");
#endif

#ifndef ARG_H
#define ARG_H
struct arg_lst {
	__u8 *input;
	__u8 *output;
	__u8 *modif;
};

// typedef struct {
// #pragma pack(1)
// 	__u64	addr;
// 	__u8	key[16];
// 	__u32	size;	// size of data in bytes
// 	__u8	*data;
// #pragma pack()
// } symbol_cell;


struct sym_off_sz_t {
	Elf_Sym	*sym;
	__u64	off;
	__u64	sz;
	__u64	prev_jmp_off;
};


#endif

int do_init(struct arg_lst *args);
llist_t *make_exec_phdr_ll(elf_t *elf);
llist_t *make_sym_ll(elf_t *elf, Elf_Phdr *phdr);
void fix_jmp(__u8 *ptr, __u32 v);
__s8 sym_ll_is_done(llist_t *syms);

__s8 pack_bin(elf_t *elf);

__s8 stick_layered_syms(rel_patch_t *rel, Elf_Phdr *phdr);
void MD5_hash(__u8 hash[16], __u8 *msg, __u64 len);