auto p = elf->vtoph(entry);
if (!p) return;

void *ptr	= elf->off<void*>(entry);
__u64 size	= p->p_filesz - (entry - p->p_offset);

d.iter(ptr, size, [&](__u64 i, insn_t& in) {
	if (in.IsNull() || !in.IsPtr()) return;
	__u64 virt	= in.PtrAddr(elf->ftov(entry + i));
	__u64 off	= elf->vtof(virt);

	if (virt != -1) {
		auto ph = elf->ftoph(off);
		if (!!ph && ph->Is(PF_X))
			q.push_back(off);
	}
});
		foreach_rela_tab(elf, rtab, r) {
	__u64 v;
	switch (ELF64_R_TYPE(r->r_info)) {
		case R_X86_64_RELATIVE:
			v = r->r_offset + r->r_addend;
			break;
		case R_X86_64_GLOB_DAT:
		case R_X86_64_JUMP_SLOT:
			v = r->r_offset;
			break;
	}
	Elf_Shdr *s = elf->vtosh(v);
	if (!!s)
		if (elf->sec_name(s) == ".got" || elf->sec_name(s) == ".got.plt") printf("HEY!\n");
	// &elf->sec.str[s->sh_name]
	if (elf->OffPerm(v) & PF_X) q.push_back(elf->vtof(v));
}