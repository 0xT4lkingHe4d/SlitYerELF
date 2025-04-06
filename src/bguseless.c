
// 	for (int i = 0; i < 0x1000; i++)
// 		memcpy(elf_get_plt_rela(&pack.elf)->mm.mem + 1 + i, elf_get_plt_rela(&pack.elf)->mm.mem, sizeof(Elf_Rela));

// 	_hdr_(&pack, NULL, PATCH_REL, 0, -1, pack.elf.dynamic.off + sizeof(Elf_Dyn) * 30, 0x1000);


// 	for_each_orig_patch(&pack, frag) {
// 		if (frag->off > pack.elf.dynamic.off || _contain_(frag->off, frag->mm.sz, pack.elf.dynamic.off + pack.elf.dynamic.mm.sz)) frag->off += sizeof(Elf_Dyn) * 0x10;
// 		// if (_contain_(frag->off, frag->mm.sz, off)) prf("$$ %lx %lx\n", frag->off, frag->mm.sz);
// 	}
// 	pack.elf.dynamic.tab = xmalloc(pack.elf.dynamic.mm.sz + sizeof(Elf_Dyn) * 0x100);
// 	pack.elf.dynamic.mm.sz += sizeof(Elf_Dyn) * 0x100;
// 	memset(pack.elf.dynamic.tab, 'A', pack.elf.dynamic.mm.sz - sizeof(Elf_Dyn) * 5);
// 	elf_shift_off(&pack.elf, sec->sh_offset + sec->sh_size, sizeof(Elf_Dyn));

// 	foreach_phdr(&pack.elf, p) if (p->p_type == PT_DYNAMIC) {
// 		p->p_filesz += sizeof(Elf_Dyn) * 0x100;
// 		p->p_memsz += sizeof(Elf_Dyn) * 0x100;
// 	}
// 	foreach_shdr(&pack.elf, sec) if (sec->sh_type == SHT_DYNAMIC) sec->sh_size += sizeof(Elf_Dyn) * 0x100;


// 	Elf_Phdr *p = NULL;
// 	foreach_phdr((&elf), e) if (e->p_flags & PF_X) p = e;

// 	rel_patch_t *rel = pack_new_rel_t(&pack, p->p_offset, &elf, p->p_offset, p->p_filesz + 5);
// 	memcpy(rel->out.shared_mm->mem, elf.map + p->p_offset, p->p_filesz);
// 	_rel_(&rel->out.patches, PATCH_REL, p->p_vaddr, p->p_filesz, 0, p->p_filesz);

// 	memcpy(rel->out.shared_mm->mem + (p->p_filesz - 331), elf.map + p->p_offset, 331);
// 	_rel_(&rel->out.patches, PATCH_REL, p->p_vaddr, 331, (p->p_filesz - 331), 331);

// 	memcpy(rel->out.shared_mm->mem, elf.map + p->p_offset + 331, (p->p_filesz - 331));
// 	_rel_(&rel->out.patches, PATCH_REL, p->p_vaddr + 331, (p->p_filesz - 331), 0, (p->p_filesz - 331));

// 	*(__u8*)(rel->out.shared_mm->mem + p->p_filesz) = 0xe9;
// 	*(__s32*)(rel->out.shared_mm->mem + p->p_filesz + 1) = -(p->p_filesz + 5);

// 	_rel_(&rel->out.patches, PATCH_ADD, -1, 0, p->p_filesz, 5);



// __u64 i = 0;
// 	foreach_rela(&pack.elf, rtab, r) if (rtab->off == 0x618 && i++ >= 1) memcpy(r, rtab->mm.mem, sizeof(Elf_Rela));
// 	pack_ext_hdr(&pack, pack.elf.dynamic.off, sizeof(Elf_Dyn)*(0x1000));
// 	for (int i = 0; i < 0x1000-1; i++)
// 		memcpy(&pack.elf.dynamic.tab[25+i], (i == 0xfff) ? (pack.elf.dynamic.tab) : (&(Elf_Dyn){ .d_tag=0, .d_un={ .d_val=0 }}), sizeof(Elf_Dyn));

// TRAP();

// 	foreach_X_phdr((&elf), p) {
// 		if (p->p_type != PT_LOAD) continue;

// 		// __u8 *ptr = elf.map + p->p_offset;
// 		// void *out = rel->out.shared_mm->mem;
// 		// __u64 off = 0;
// 		// __u64 main_off = main_sym->off - p->p_offset;

// 		// /* Cpy from 0 to main_sym offset (from X phdr offset) */
// 		memcpy(out, ptr, main_off);
// 		_rel_(&rel->out.patches, PATCH_REL, p->p_vaddr, main_off, off, main_off);
// 		off += main_off;

// 		// memcpy(out + off, "\xccR3main IN L1gh7 *~\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 50);
// 		// _rel_(&rel->out.patches, PATCH_ADD, -1, 0, off, 50);
// 		// off += 50;

// 		// // Cpy the rest
// 		// __u64 sz = p->p_filesz - main_off;
// 		// memcpy(out + off, ptr + main_off, sz);
// 		// _rel_(&rel->out.patches, PATCH_REL, p->p_vaddr + main_off, sz, off, sz);
// 		if (stick_layered_syms(rel, p) == -1)
// 			return -1;

// 		break;
// 	}