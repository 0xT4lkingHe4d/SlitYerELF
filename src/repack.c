#include <linux/types.h>
#include <assert.h>
#include "../include/main.h"
#include "../include/packing.h"

// __s8 pack_bin(elf_t *elf) {
// 	pack_t pack = {0};
// 	import_elf(elf, &pack);

// 	Elf_Phdr *ph_x = NULL;
// 	__u64 ph_x_orig_filesz = 0;
// 	foreach_ll((&pack.ll_phdr), e) {
// 		phdr_st *ph = e->dat;
// 		Elf_Phdr *phdr = &ph->phdr;
// 		if (phdr->p_type == PT_LOAD && phdr->p_flags == (PF_R|PF_X)) {
// 			assert(_contains_(phdr->p_vaddr, phdr->p_memsz, pack.ehdr.e_entry, 1));
// 			*(__u8*)(ph->mm.mem + (pack.ehdr.e_entry - phdr->p_vaddr)) = 0xcc;
// 			ph_x_orig_filesz = phdr->p_filesz;
// 			phdr->p_filesz	+= 0x50000;
// 			phdr->p_memsz	+= 0x50000;
// 			ph_x = phdr;
// 			break;
// 		}
// 	}
// 	foreach_ll((&pack.ll_phdr), e) {
// 		phdr_st *ph = e->dat;

// 		if (ph->phdr.p_offset > ph_x->p_offset) {
// 			ph->phdr.p_offset	+= 0x50000;
// 			ph->phdr.p_vaddr	+= 0x50000;
// 			ph->phdr.p_paddr	+= 0x50000;
// 		}
// 	}

// 	pack.ehdr.e_shoff += 0x50000;
// 	Elf_Shdr *last = NULL;
// 	foreach_sec_tab(pack.sec.tab, sec, pack.sec.num) {
// 		if (_contains_(ph_x->p_offset, ph_x_orig_filesz, sec->sh_offset, 1)) {

// 		}
// 		if (sec->sh_offset > ph_x->p_offset + ph_x_orig_filesz) {
// 			sec->sh_offset	+= 0x50000;
// 			sec->sh_addr	+= 0x50000;
// 		}
// 	}

// 	for (Elf_Dyn *dyn = pack.dynamic.tab; dyn <= (void*)pack.dynamic.tab + pack.dynamic.mm_tab.sz; dyn++) {
// 		// if (dyn->d_un.d_ptr > ph_x->p_offset)
// 		switch (dyn->d_tag) {
// 			case DT_PLTGOT:
// 			case DT_INIT_ARRAY:
// 			case DT_FINI_ARRAY:
// 				dyn->d_un.d_val += 0x50000;
// 		}
// 	}

// 	foreach_ll((&pack.ll_rela), e) {
// 		rela_st *st = e->dat;

// 		if (st->t == SHT_RELA) {
// 			for (Elf_Rela *rela = st->rela; rela < (void*)st->rela + st->mm.sz; rela++) {
// 				if (rela->r_offset > ph_x->p_offset + ph_x_orig_filesz) rela->r_offset += 0x50000;
// 			}
// 		}
// 	}
	
// 	make_elf(&pack, "./oi.fuck.you");
// }