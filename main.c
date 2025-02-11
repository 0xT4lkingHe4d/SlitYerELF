#include <linux/types.h>
#include "./include/pack.h"
#include "./include/utils.h"
#include "./include/llist.h"
#include "./lib-x86-binary/x86.h"
#include "./include/xtc.h"

void __attribute__((constructor)) init_xtc() {
	if (!x_t_c_init()) DIE("FUCK");
}

void pack_reloc(pack_t *pack) {
	llist_each_dat(&pack->ll_rel, ptx_rel_t, e) {
		ptx_patch_t *pr = e->patch.list_elem->dat;
		mmsz_t *ret = do_reloc(&e->rel);
		if (!ret) DIE("$FUCK!");
		pr->mm = *ret;
	}
}

#define sym_each_reverse(elf, stab, sym)				\
	for (__u64 i = 0; !i; i=1)							\
		elf_each_sym64((elf), stab, _s_)				\
			if (++i) elf_each_sym64((elf), stab, sym)	\
				if ((void*)s - stab->ptr + (stab->count - i-1) * sizeof(Elf64_Sym) == stab->count * sizeof(Elf64_Sym))

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

	rel->plugin	= pack;
	rel->hook_fn= pack_rel_value;
	rel->off_fn = pack_rel_off;

	Elf64_Phdr *p_exec = NULL;
	elf_each_phdr64(elf, p)
		if (p->p_flags & PF_X) p_exec = p;
	if (!p_exec) _die("No exec PHDR FUCK!");
	__u16 align = 3;

	elf_each_symtab(elf, stab) {
		if (stab->t == SHT_SYMTAB) {
			sym_each_reverse(&elf, stab, s) {
				if (!!s->st_value && !!(s->st_info & STT_FUNC)) {
					elf_sym_obj *sym = make_sym_obj(elf, s);

					/* Symbol is within the executable segment */
					if (_contain_(p_exec->p_offset, p_exec->p_filesz, sym->off))
						rel_insn(rel, elf, elf->map+sym->off, sym->off, sym->off-p_exec->p_offset, sym->size);
				}
			}
		}
	}


	// PLT stubs
	rel_insn(rel, elf, elf->map+0x1020, 0x1020, 0x1020 - 0x1000, 0x1250 -0x1020);
}
