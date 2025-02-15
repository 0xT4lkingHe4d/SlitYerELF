#include <linux/types.h>
#include "./include/pack.h"
#include "./include/utils.h"
#include "./include/llist.h"
#include "./include/carve.h"
#include "./lib-x86-binary/x86.h"
#include "./include/xtc.h"

void __attribute__((constructor)) init_xtc() {
	if (!x_t_c_init()) DIE("FUCK");
}

void pack_reloc(pack_t *pack) {
	llist_each_dat(&pack->ll_rel, ptx_rel_t, e) {
		ptx_patch_t *rr = e->patch.list_elem->dat;
		mmsz_t *ret = do_reloc(&e->rel);
		if (!ret) DIE("$FUCK!");
		rr->mm = *ret;
	}
}

void main() {
	pack_t pack = {0};
	pack_load_elf(&pack, "./specimen/xx");

	pack_test_plugin(&pack);
	ptx_shift(&pack, 0x648, 0x10000);
	ptx_shift(&pack, 0x2000, 0x10000);

	pack_reloc(&pack);

	make_elf(&pack,"./output");
}

void pack_test_plugin(pack_t *pack) {
	elf_t *elf = pack->out_elf;
	rel_t *rel = pack_new_rel(pack, 0x1000);
	if (!rel) DIE("FU#CK!");

	rel->plugin	= (rel_plugin_t){
		.dat	= pack,
		.virt	= pack_rel_vtov,
		.off	= pack_rel_ftof,
		.addr	= pack_rel_addr,
	};

	Elf64_Phdr *p_exec = NULL;
	elf_each_phdr64(elf, p)
		if (p->p_flags & PF_X) p_exec = p;
	if (!p_exec) _die("No exec PHDR FUCK!");
	__u16 align = 3;

	// rel_hijack_t *h = rel_hijack(rel, elf, 0x115a, NULL);
	// rel_hijack_add_target(h, REL_HIJACK_ADDR, 0x1139);

	elf_each_symtab(elf, stab) {
		if (stab->t == SHT_SYMTAB)
			elf_each_sym64(elf, stab, sym)
				if (!!sym->st_value && !!(sym->st_info & STT_FUNC)) {
					elf_sym_obj *sym_obj = make_sym_obj(elf, sym);

					/* Symbol is within the executable segment */
					if (_contain_(p_exec->p_offset, p_exec->p_filesz, sym_obj->off)) {
						rel_insn(rel, PATCH_REL, elf, elf->map+sym_obj->off, sym_obj->off, sym_obj->off-p_exec->p_offset + align, sym_obj->size);
					}
				}
	}

	__u8 *sc = "0xR3ma1nINLigh7\0";
	rel_buff(rel, PATCH_ADD, NULL, sc, -1, 0, 0x10);

	// PLT stubs
	rel_insn(rel, PATCH_REL, elf, elf->map+0x1020, 0x1020, 0x1020 - 0x1000 + align, 0x30);
}
