#include <assert.h>
#ifndef UAPI_
#define UAPI_
#include "../../disass/include/uapi.h"
#endif

#include "../../include/elf.h"

__u64 get_unknown_sz_sym_sz(elf_t *elf, Elf_Sym *sym) {
	if (!sym->st_value || !(sym->st_info & STT_FUNC)) return -1;
	// if (!!sym->st_size) return sym->st_size;

	__u64 x = 0;
	Elf_Phdr *p = elf_virt_to_phdr(elf, sym->st_value);
	foreach_symtab(elf, stab, sym_i) {
		if (elf_virt_to_phdr(elf, sym_i->st_value) != p) continue;
		if ((sym_i->st_value > sym->st_value) && (!x || x > sym_i->st_value))
				x = sym_i->st_value;
	}
	foreach_shdr(elf, sec) {
		Elf_Phdr *sp = shdr_get_phdr(elf, sec);
		if (!sp || sp->p_flags != (PF_R|PF_X)) continue;

		if ((sym->st_value < sec->sh_addr) && (!x || x > sec->sh_addr))
			x = sec->sh_addr;
	}
	// No symbol || Xec section goes after
	if (!x) x = (p->p_vaddr + p->p_memsz);
	x -= sym->st_value;
	
	__u64 sym_off = elf_vtof(elf, sym->st_value);
	assert(sym_off != -1);

	__u64 i = 0;
	__u8 *ptr = elf->map + sym_off;
	foreach_instr_off(in, i, ptr, x) {
		__u64 l = 0;
		for (__u8 *c = ptr + i + in.in_sz; c <= &ptr[x-1]; c++, l++) {
			if (!!(*c)) break;
			if (c == &ptr[x-1])
				return x - l -1;
		}
	}

	assert(sym_off + x <= elf->size);
	return x;
}


Elf_Sym *elf_off_to_sym(elf_t *elf, __u64 off, __u64 sz) {
	foreach_symtab(elf, stab, sym) {
		if (!sym->st_value || !(sym->st_info & STT_FUNC)) continue;
		__u64 sym_off	= elf_vtof(elf, sym->st_value);
		__u64 sym_sz	= get_unknown_sz_sym_sz(elf, sym);
		if (_contains_(sym_off, sym_sz, off, sz))
			return sym;
	}
	return NULL;
}

sym_obj *make_sym_obj(elf_t *elf, Elf_Sym *sym) {
	sym_obj *r = xmalloc(sizeof(sym_obj));
	r->sym	= sym;
	r->off	= elf_vtof(elf, sym->st_value);
	r->size	= get_unknown_sz_sym_sz(elf, sym);

	return r;
}

sym_obj *get_sym(elf_t *elf, __u8 *str) {
	foreach_symtab(elf, stab, sym) {
		if (!strncmp(elf_sym_name(stab, sym), str, strlen(str)+1)) {
			return make_sym_obj(elf, sym);
		}
	}
	return NULL;
}