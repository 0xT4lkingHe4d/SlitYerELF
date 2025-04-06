// #include "../include/main.h"

// /* Get all PF_X phdrs from ~elf */


// llist_t *make_exec_phdr_ll(elf_t *elf) {
// 	if (!elf) return NULL;

// 	llist_t *txt = xmalloc(sizeof(llist_t));
// 	llist_new(txt);

// 	foreach_phdr(elf, p) {
// 		if (p->p_flags != (PF_R|PF_X)) continue;
// 		if (!llist_add(txt, 0, p, -1))
// 			return NULL;
// 	}
// 	return txt;
// }


// /** Get All symbols (+ needs SYMTAB) and fix st_size=0
//  * return - "llist_t<sym_sz_tup>"
//  **/
// llist_t *make_sym_ll(elf_t *elf, Elf_Phdr *phdr) {
// 	if (!elf->sym.tab) {
// 		pr("[-] No symbol table found");
// 		return NULL;
// 	}
// 	llist_t *ll = xmalloc(sizeof(llist_t));
// 	llist_new(ll);

// 	foreach_sym(elf, sym) {
// 		if (!sym->st_value || !(sym->st_info & STT_FUNC)) continue;

// 		Elf_Phdr *p = elf_virt_to_phdr(elf, sym->st_value);
// 		if (!p || p != phdr) continue;

// 		if (!sym_fits_phdr(sym, p)) TRAP();

// 		struct sym_off_sz_t my_sym = {
// 			.sym	= sym,
// 			.sz		= ((!sym->st_size) ? get_unknown_sz_sym_sz(elf, sym) : sym->st_size),
// 		};

// 		llist_add(ll, F_LL_MALLOC, &my_sym, sizeof(struct sym_off_sz_t));
// 	}
// 	return ll;
// }
