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

	// merge_elf_t mrg = {
	// 	.orig_elf	=	&elf,
	// 	.modif_elf	=	&modif_elf,
	// };

	// if (merge_elf_init(&mrg) == -1) return -1;

	// merge_elf(&pack, &mrg);
	Elf_Phdr *p = NULL;
	foreach_phdr((&elf), e) if (e->p_flags & PF_X) p = e;

	rel_patch_t *rel = pack_new_rel_t(&pack, p->p_offset, &elf, p->p_offset, p->p_filesz + 5);
	void *out = rel->out.shared_mm->mem;
	memcpy(out, elf.map + p->p_offset, p->p_filesz);
	_rel_(&rel->out.patches, PATCH_REL, p->p_vaddr, p->p_filesz, 0, p->p_filesz);

	memcpy(out + (p->p_filesz - 331), elf.map + p->p_offset, 331);
	_rel_(&rel->out.patches, PATCH_REL, p->p_vaddr, 331, (p->p_filesz - 331), 331);

	memcpy(out, elf.map + p->p_offset + 331, (p->p_filesz - 331));
	_rel_(&rel->out.patches, PATCH_REL, p->p_vaddr + 331, (p->p_filesz - 331), 0, (p->p_filesz - 331));

	*(__u8*)(out + p->p_filesz) = 0xe9;
	*(__s32*)(out + p->p_filesz + 1) = -(p->p_filesz + 5);

	_rel_(&rel->out.patches, PATCH_ADD, -1, 0, p->p_filesz, 5);

	do_reloc(&pack);

	make_elf(&pack, "./oi.fuck.you");

	return 0;
}

