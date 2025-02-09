#include <assert.h>
#include <string.h>
#include "./elf.h"
#include "../disass_x86/include/uapi.h"
#include "../utils/include/utils.h"

__u64 get_unknown_sz_sym_sz(elf_t *elf, Elf64_Sym *sym) {
	if (!sym->st_value || !(sym->st_info & STT_FUNC)) return -1;
	// if (!!sym->st_size) return sym->st_size;

	__u64 x = 0;
	Elf64_Phdr *p = elf_virt_to_phdr(elf, sym->st_value);
	elf_each_symtab_sym64(elf, stab, sym_i) {
		if (elf_virt_to_phdr(elf, sym_i->st_value) != p) continue;
		if ((sym_i->st_value > sym->st_value) && (!x || x > sym_i->st_value))
				x = sym_i->st_value;
	}
	elf_each_sec64(elf, sec) {
		Elf64_Phdr *sp = elf_shdr_get_phdr(elf, sec);
		if (!sp || sp->p_flags != (PF_R|PF_X)) continue;

		if ((sym->st_value < sec->sh_addr) && (!x || x > sec->sh_addr))
			x = sec->sh_addr;
	}
	// No symbol || Xec section goes after
	if (!x) x = (p->p_vaddr + p->p_memsz);
	x -= sym->st_value;
	
	__u64 sym_off = elf_vtof(elf, sym->st_value);
	assert(sym_off != -1);
	__u8 *ptr = elf->map + sym_off;
	__u64 i = 0;
	foreach_instr_off(X86_64, in, i, ptr, x) {
		__u64 l = 0;
		for (__u8 *c = ptr + i + in.in_sz; c <= &ptr[x-1]; c++, l++) {
			if (!!(*c)) return x;
			if (c == &ptr[x-1]) {
				return x - l -1;
			}
		}
	}
	assert(sym_off + x <= elf->size);
	return x;
}


Elf64_Sym *elf_off_to_sym(elf_t *elf, __u64 off, __u64 sz) {
	elf_each_symtab_sym64(elf, stab, sym) {
		if (!sym->st_value || !(sym->st_info & STT_FUNC)) continue;
		__u64 sym_off	= elf_vtof(elf, sym->st_value);
		__u64 sym_sz	= get_unknown_sz_sym_sz(elf, sym);
		if (_contains_(sym_off, sym_sz, off, sz))
			return sym;
	}
	return NULL;
}

elf_sym_obj *make_sym_obj(elf_t *elf, void *sym) {
	elf_sym_obj *r = xmalloc(sizeof(elf_sym_obj));
	if (elf->bits == 64) {
		r->sym64 = sym;
		r->off	 = elf_vtof(elf, r->sym64->st_value);
	}
	if (elf->bits == 32) {
		r->sym32 = sym;
		r->off	 = elf_vtof(elf, r->sym32->st_value);
	}
	r->size	 = get_unknown_sz_sym_sz(elf, sym);

	return r;
}

elf_sym_obj *get_sym(elf_t *elf, __u8 *str) {
	elf_each_symtab_sym64(elf, stab, sym) {
		if (!strncmp(elf_sym_name(stab, sym), str, strlen(str)+1)) {
			return make_sym_obj(elf, sym);
		}
	}
	return NULL;
}