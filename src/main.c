#include <assert.h>
#ifndef UAPI_
#define UAPI_
#include "../disass/include/uapi.h"
#endif
#include "../include/main.h"
#include "../include/xtc.h"
#include "../include/packing.h"
#include "../include/rel_instr.h"

void __attribute__((constructor)) init_xtc() {
	struct mmsz_tup *x = x_t_c_init();
	if (!x->mem) DIE("FUCK");
}

int do_init(struct arg_lst *args) {
	pr(" \e[1;30m-<[\e[1;40m "BCYAN"SlitYerELF \e[0m\e[1;30m]>-"CRST);

	pack_t pack = {0};
	elf_t elf = {0};
	assert(!new_elf(args->input, &elf));
	import_elf(&elf, &pack);



	elf_t modif_elf = {0};
	assert(!new_elf(args->modif, &modif_elf));

	merge_elf_t mrg = {
		.orig_elf	= &elf,
		.modif_elf	= &modif_elf,
	};
	if (merge_elf_init(&mrg) == -1) return -1;
	merge_elf(&pack, &mrg);

	do_reloc(&pack);
	make_elf(&pack, "./oi.fuck.you");

	return 0;
}

	// for (int i = 0; i < 0x1000; i++)
	// 	memcpy(elf_get_plt_rela(&pack.elf)->mm.mem + 1 + i, elf_get_plt_rela(&pack.elf)->mm.mem, sizeof(Elf_Rela));

	// _hdr_(&pack, NULL, PATCH_REL, 0, -1, pack.elf.dynamic.off + sizeof(Elf_Dyn) * 30, 0x1000);


	// for_each_orig_patch(&pack, frag) {
	// 	if (frag->off > pack.elf.dynamic.off || _contain_(frag->off, frag->mm.sz, pack.elf.dynamic.off + pack.elf.dynamic.mm.sz)) frag->off += sizeof(Elf_Dyn) * 0x10;
	// 	// if (_contain_(frag->off, frag->mm.sz, off)) prf("$$ %lx %lx\n", frag->off, frag->mm.sz);
	// }
	// pack.elf.dynamic.tab = xmalloc(pack.elf.dynamic.mm.sz + sizeof(Elf_Dyn) * 0x100);
	// pack.elf.dynamic.mm.sz += sizeof(Elf_Dyn) * 0x100;
	// memset(pack.elf.dynamic.tab, 'A', pack.elf.dynamic.mm.sz - sizeof(Elf_Dyn) * 5);
	// elf_shift_off(&pack.elf, sec->sh_offset + sec->sh_size, sizeof(Elf_Dyn));

	// foreach_phdr(&pack.elf, p) if (p->p_type == PT_DYNAMIC) {
	// 	p->p_filesz += sizeof(Elf_Dyn) * 0x100;
	// 	p->p_memsz += sizeof(Elf_Dyn) * 0x100;
	// }
	// foreach_shdr(&pack.elf, sec) if (sec->sh_type == SHT_DYNAMIC) sec->sh_size += sizeof(Elf_Dyn) * 0x100;


	// Elf_Phdr *p = NULL;
	// foreach_phdr((&elf), e) if (e->p_flags & PF_X) p = e;

	// rel_patch_t *rel = pack_new_rel_t(&pack, p->p_offset, &elf, p->p_offset, p->p_filesz + 5);
	// // memcpy(rel->out.shared_mm->mem, elf.map + p->p_offset, p->p_filesz);
	// // _rel_(&rel->out.patches, PATCH_REL, p->p_vaddr, p->p_filesz, 0, p->p_filesz);

	// memcpy(rel->out.shared_mm->mem + (p->p_filesz - 0x80), elf.map + p->p_offset, 0x80);
	// _rel_(&rel->out.patches, PATCH_REL, p->p_vaddr, 0x80, (p->p_filesz - 0x80), 0x80);

	// memcpy(rel->out.shared_mm->mem, elf.map + p->p_offset + 0x80, (p->p_filesz - 0x80));
	// _rel_(&rel->out.patches, PATCH_REL, p->p_vaddr + 0x80, (p->p_filesz - 0x80), 0, (p->p_filesz - 0x80));

	// *(__u8*)(rel->out.shared_mm->mem + p->p_filesz) = 0xe9;
	// *(__s32*)(rel->out.shared_mm->mem + p->p_filesz + 1) = -(p->p_filesz + 5);

	// _rel_(&rel->out.patches, PATCH_ADD, -1, 0, p->p_filesz, 5);
