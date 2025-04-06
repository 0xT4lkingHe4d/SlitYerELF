#include "../../include/packing.h"
#include "../../include/rel_instr.h"

__s8 p_add_got_entry(pack_t *p, got_entry_t *got) {
	Elf_Shdr *sec = elf_sec_by_name(&p->elf, ".got.plt");
	if (!sec) sec = elf_sec_by_name(&p->elf, ".got");
	if (!sec) return -1;

	got->ptr = xmalloc(8);
	got->addr = sec->sh_addr + sec->sh_size;
	p_add_patch(p, got->ptr, pack_vtof(p, &p->elf, got->addr), 8);

	return 0;
}

__u16 p_add_sym(pack_t *p, symtab_t *stab, __u8 *name, __u64 len, Elf_Sym *sym) {
	__u16 i = _elf_symtab_sz(stab) / sizeof(Elf_Sym);
	__u64 str_sz = stab->mm_str.sz;

	pack_ext_hdr(p, _elf_off(&p->elf, stab->str), len + 1);
	memcpy(stab->str + str_sz, name, len);

	if (!sym->st_name) sym->st_name = str_sz;
	pack_ext_hdr(p, stab->off, sizeof(Elf_Sym));
	memcpy(&stab->tab[i], sym, sizeof(Elf_Sym));

	return i;
}

__u16 p_add_rela(pack_t *p, rela_t *rtab, Elf_Rela *rela) {
	__u16 i = _elf_rela_t_sz(rtab) / sizeof(Elf_Rela);

	pack_ext_hdr(p, rtab->off, sizeof(Elf_Rela));
	memcpy(&rtab->rela[i], rela, sizeof(Elf_Rela));

	return i;
}

__u16 p_add_gnu_versym(pack_t *p, __u16 v) {
	__u16 i = p->elf.gnu_ver.mm_sym.sz / sizeof(__u16);

	pack_ext_hdr(p, p->elf.gnu_ver.sym_off, sizeof(__u16));
	p->elf.gnu_ver.sym[i] = v;

	return i;
}
