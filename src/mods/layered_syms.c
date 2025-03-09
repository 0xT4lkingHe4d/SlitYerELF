#ifndef UAPI_
#define UAPI_
#include "../../disass/include/uapi.h"
#endif
#include "../../include/main.h"

__s8 stick_layered_syms(rel_patch_t *rel, Elf_Phdr *phdr) {
	elf_t *elf = rel->src.elf;
	llist_t *syms = make_sym_ll(elf, phdr);
	if (!syms) return -1;
	__u64 off = 0;

	while (!sym_ll_is_done(syms)) {
		foreach_ll_reverse(syms, e) {
			struct sym_off_sz_t *st = e->dat;

			__u64 vaddr = st->sym->st_value + st->off;
			__u64 i = 0, total = 0;
			if (!st->sz) TRAP();

			if (st->off == st->sz) continue;

			_assertf((st->off <= st->sz), "[FYUCK !] %s off !(0x%lx <= sz 0x%lx)", 
				elf_sym_name(elf, ((struct sym_off_sz_t*)e->dat)->sym), 
				st->off, st->sz);

			/* Cpy ~0x10b (size) of instr */
			__u8 size = ((st->sz - st->off) < 0x10) ? st->sz - st->off : 0x10;
			__u64 elf_off = st->off + st->sym->st_value;
			const void *ptr = elf->map + elf_off;
			__u64 block_sz = 0;
			foreach_instr_off(in, i, ptr, size) {
				if ((st->off + i) > st->sz) {
					i -= in.in_sz;
					break;
				}

				memcpy(rel->out.mm->mem + off + block_sz, ptr + i, in.in_sz);
				block_sz += in.in_sz;
			}
			_rel_(&rel->out.patches, PATCH_REL, elf_off, i, off, block_sz);
			st->off += i;
			off += block_sz;

			// fix previous JMP
			__u32 v = off - st->prev_jmp_off - 5 - i;

			if (!!st->prev_jmp_off) *(__u32*)(rel->out.mm->mem + st->prev_jmp_off +1) = v;
			prf(PR_DBG "%s[%u / %u]"CRST BBLUE" \t\t [%s]"CRST " %lx    off 0x%lx\n",
				(st->off == st->sz) ? BYLW : BGRN,
				st->off, st->sz,
				elf_find_sym_name(elf, ((struct sym_off_sz_t*)e->dat)->sym),
				(!!st->prev_jmp_off) ? v : 0,
				off);

			// Insert JMP if the sym is not fully written
			if (st->off != st->sz) {
				st->prev_jmp_off = off;
				*(__u8*)(rel->out.mm->mem + off) = '\xe9';
				_rel_(&rel->out.patches, PATCH_ADD, -1, 0, off, 5);
				off += 5;
			}

			if (off + 0x1000 > rel->out.mm->sz) {
				resz_mmsz(rel->out.mm, MEM_MMAP, 0x1000);
			}
		}
	}

	foreach_shdr(elf, sec) {
		const __u8 *name = &elf->sec.strtab_shdr[sec->sh_name];
		if (	!strncmp(name, ".plt", 5)
			||	!strncmp(name, ".plt.got", 9))
		{
			_rel_(&rel->out.patches, PATCH_REL, sec->sh_offset, sec->sh_size, off, sec->sh_size);
			__u64 sec_off = elf_virt_to_off(elf, sec->sh_offset);
			
			memcpy(rel->out.mm->mem + off, elf->map + sec_off, sec->sh_size);
			off += sec->sh_size;

		}
	}

	return 0;
}