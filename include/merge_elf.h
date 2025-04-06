// #include <linux/types.h>
// #include "./packing.h"
// #include "./elf.h"
// #include "./utils.h"

// #define MRG_CMP_ATTR(f, str) (_strcmp(MRG_##f##_ATTR, str))
// #define MRG_SYM_ATTR "\xca\xfe\xad\xd1\xc7@"
// #define MRG_SYM 1

// typedef struct {
// 	__u8	t;
// 	__u8	*str;
// 	sym_obj	*orig_fn;
// 	sym_obj *modif_fn;
// } me_target_t;

// typedef struct {
// 	elf_t	*orig_elf;
// 	elf_t	*modif_elf;
// 	llist_t	ll_target;
// } merge_elf_t;

// __s8 merge_elf_init(merge_elf_t *m);
// __s8 merge_elf(pack_t *pack, merge_elf_t *m);
// __s8 merge_elf_init_modif(pack_t *p, merge_elf_t *m, me_target_t *trg);
// // __s8 merge_elf_add_plt(pack_t *p, merge_elf_t *m, __u64 imm);
