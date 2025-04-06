// #include <assert.h>
// #ifndef UAPI_
// #define UAPI_
// #include "../disass/include/uapi.h"
// #endif
// #include "../include/main.h"
// #include "../include/xtc.h"
// #include "../include/packing.h"

// __s8 stick_layered_syms(rel_patch_t *rel, Elf_Phdr *phdr);

// __s8 is_JMP_imm8(instr_dat_t *in) {
// 	const instr *e = in->instr;
// 	// (get_inst_type(in, &in->oper[0]) & IMM)
// 	return (!e->two_byte && (e->opcode1&~0xf) == 0x70);
// }

// void __attribute__((constructor)) init_xtc() {
// 	struct mmsz_tup *x = x_t_c_init();
// 	if (!x->mem) DIE("FUCK");
// }

// int do_init(struct arg_lst *args) {
// 	elf_t elf = {0};
// 	assert(!new_elf(args->input, &elf));

// 	pack_t pack = {0};
// 	import_elf(&elf, &pack);

// 	__u8 c = 0;
// 	// foreach_phdr((&elf), p) {
// 	// 	if (_contains_(p->p_offset, p->p_filesz, 0x5c0, 1)) {
// 	// 		phdr_st *ph_e = NULL;
// 	// 		ll_each(&pack.ll_phdr, ph_e) if (ph_e->phdr.p_offset == p->p_offset) {
// 	// 			ph_e->mm.mem 
// 	// 			break;
// 	// 		}
// 	// 	}
// 	// }

// 	// Dyn rela
// 	foreach_rela(&elf, elf.r_dyn_a, rela) {
// 		if (rela->r_addend == 0x1170) rela->r_addend = 0x1050;
// 		if (rela->r_addend == 0x1130) rela->r_addend = 0x1059;
// 	}

// 	// PLT Rela
// 	for (Elf_Rela *rel = elf.r_plt.rela; (void*)rel < (void*)(elf.r_plt.rela) + elf.r_plt.size; rel++) {
// 		__u64 *v = elf.map + elf_virt_to_off(&elf, rel->r_offset);
// 		*v += 0x33b;
// 	}

// 	// Find TXT Phdr
// 	foreach_phdr((&elf), p) {
// 		if (p->p_type != PT_LOAD || p->p_flags != (PF_R|PF_X)) continue;

// 		rel_patch_t r = {0};
// 		__u64 sz = p->p_filesz + 0x1000;
// 		new_rel_t(&r, sz, &elf, p->p_offset, p->p_filesz);

// 		lle *e = llist_add(&pack.modif.rel, F_LL_MALLOC, &r, sizeof(rel_patch_t));
// 		if (!e) DIE("FUCK!!");

// 		// if (!!stick_layered_syms(e->dat, p)) DIE("FUCK!");
// 		// do_reloc(&r);

// 		phdr_st *ph_e = NULL;
// 		ll_each(&pack.ll_phdr, ph_e) if (ph_e->phdr.p_offset == p->p_offset) {
// 			ph_e->phdr.p_filesz = r.out.mm.sz;
// 			ph_e->phdr.p_memsz = r.out.mm.sz;
// 			ph_e->mm_t = MEM_MMAP;
// 			ph_e->mm = r.out.mm;
// 			break;
// 		}
// 		patches_t *patch = NULL;
// 		ll_each(&r.out.patches, patch) {
// 			if (_contains_(patch->orig_off, patch->orig_sz, pack.ehdr.e_entry, 1)) {
// 				pack.ehdr.e_entry = 0x1030;
// 				break;
// 			}
// 		}

// 		if (c++) DIE("more than 1 PF_X phdr");
// 	}

// 	memset(pack.sym.tab, 0, N_SYM(pack.sym.num));
// 	prf("%lu \n", pack.sym.num);
// 	for (__u16 i = 0; i < pack.sec.num; i++) {
// 		Elf_Shdr *sec = &pack.sec.tab[i];
// 		if (sec->sh_type == SHT_PROGBITS) sec->sh_size = 0x2000;//memset(sec, 0, N_SHDR(1));
// 	}

// 	make_elf(&pack, "./oi.fuck.you");	

// 	return 0;
// }
