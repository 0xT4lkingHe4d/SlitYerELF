#include "../../include/pack.h"
#include "../../include/elf.h"
#include "../../include/llist.h"
#include "../../include/rel_instr.h"

__u64 ptx_addr(pack_t *p, __u8 v, __u64 sz);

// Section headers
__u64 pack_mem_conv(pack_t *pack, __u8 from, __u8 to, __u64 n) {
	ptx_header_t *phdr = ptx_type(&pack->ptx, ELF_T_PHDR);
	ptx_header_t *shdr = ptx_type(&pack->ptx, ELF_T_SHDR);

	if (!!phdr) {
		patch_each(pack, PHDR, Elf64_Phdr, p) {
			__u64 v = (to == ELF_VIRT) ? p->p_vaddr : p->p_offset;

			if (from == ELF_VIRT && _contain_(p->p_vaddr, ALIGN(p->p_memsz, p->p_align), n))
					return v + n - p->p_vaddr;

			if (from == ELF_OFF && _contain_(p->p_offset, p->p_filesz+1, n))
				return v + n - p->p_offset;
		}
	} else if (!!shdr) {
		patch_each(pack, SHDR, Elf64_Shdr, sec) {
			__u64 v = (to == ELF_VIRT) ? sec->sh_addr : sec->sh_offset;

			if (from == ELF_VIRT && _contain_(sec->sh_addr, ALIGN(sec->sh_size, sec->sh_addralign), n))
				return v + n - sec->sh_addr;

			if (from == ELF_OFF && _contain_(sec->sh_offset, sec->sh_size+1, n))
				return v + n - sec->sh_offset;
		}
	}

	return 0;
}

rel_t *pack_new_rel(pack_t *pack, __u64 off) {
	llist_t *ll	= NULL;
	lle *e		= NULL;
	ptx_each_any_ll(pack, ll, t, e) {
		ptx_patch_t *px = e->dat;
		if (_contain_(px->src.off, px->src.size, off)) {
			ptx_rel_t x = { .patch={ .type=t, .list_elem=e}, .rel={0} };
			lle *new = llist_add(&pack->ll_rel, &x);
			if (!new) return NULL;

			ptx_rel_t *pr = new->dat;
			rel_init(&pr->rel);
			return &pr->rel;
		}
	}
	return NULL;
}

__s8 pack_load_elf(pack_t *pack, __u8 *file) {
	elf_t *elf = xmalloc(sizeof(elf_t));
	if (elf_init(elf, file, NULL) == -1)
		return -1;
	pack_init_elf(pack, elf);
	return 0;
}

void pack_new(pack_t *p, elf_t *elf) {
	*p = (pack_t){ .out_elf = elf };
	llist_new(&p->ll_rel, sizeof(ptx_rel_t));
	ptx_init(&p->ptx);
}

void pack_init_elf(pack_t *p, elf_t *elf) {
	pack_new(p, elf);

	ptx_add_header(&p->ptx, ELF_T_EHDR,	elf, elf->ehdr, 1, 0x40);
	ptx_add_header(&p->ptx, ELF_T_PHDR,	elf, elf->phdr.ptr, elf->ehdr->e_phnum, ELF_PHDR_SZ(elf));
	ptx_add_header(&p->ptx, ELF_T_SHDR,	elf, elf->sec.ptr,	elf->ehdr->e_shnum, ELF_SHDR_SZ(elf));
	ptx_add_header(&p->ptx, ELF_T_STRTAB, elf, elf->sec.str.tab, elf->sec.str.size, 1);
	ptx_add_header(&p->ptx, ELF_T_DYN, elf, elf->dynamic.ptr, elf->dynamic.count, ELF_DYN_SZ(elf));

	elf_each_reltab(elf, rtab)
		ptx_add_header(&p->ptx, ELF_T_REL, elf, rtab->ptr, rtab->count, ELF_REL_SZ(elf));

	elf_each_relatab(elf, rtab)
		ptx_add_header(&p->ptx, ELF_T_RELA, elf, rtab->ptr, rtab->count, ELF_RELA_SZ(elf));

	elf_each_symtab(elf, stab)
		ptx_add_header(&p->ptx, ELF_T_SYM, elf, stab->ptr, stab->count, ELF_SYM_SZ(elf));
	
	ptx_fill(p, elf, 0, elf->size);
	ptx_patch_t *phdr = ptx_type(&p->ptx, ELF_T_PHDR);
	ptx_patch_t *shdr = ptx_type(&p->ptx, ELF_T_SHDR);
	if (!!phdr) {
		elf_each_phdr64(elf, ph)
			pack_split_chunk(p, ph->p_offset);
	} else if (!!shdr) {
		elf_each_sec64(elf, sec)
			pack_split_chunk(p, sec->sh_offset);
	}
}

__u64 pack_patched_off(pack_t *pack, elf_t *elf, __u8 t, __u64 off) {
	ptx_each_any(pack, p)
		if (_contain_(p->src.off, p->src.size, off)) {
			__u64 v = p->off + (off - p->src.off);
			return (t == ELF_VIRT) ? pack_ftov(pack, v) : v;
		}

	return -1;
}

void pack_get_src(pack_t *p, ptx_src_t *ret, __u64 off) {
	ptx_each_any(p, f) {
		__u64 f_off = pack_patched_off(p, f->src.elf, ELF_OFF, f->src.off);
		if (_contain_(f_off, f->mm.size, off)) {
			memcpy(ret, &f->src, sizeof(ptx_src_t));
			return;
		}
	}
}

__u64 pack_base_off(pack_t *pack, elf_t *elf, __u8 from, __u8 to, __u64 v) {
	__u64 off = (from == ELF_OFF) ? v : elf_vtof(elf, v);
	return pack_patched_off(pack, elf, to, off);
}

/**
 * Rel handlers
**/

__s64 pack_rel_ftof(pack_t *pack, rel_t *rel, rel_patch_t *p, __u64 off) {
	return pack_base_ftof(pack, p->elf, off);
}

__s64 pack_rel_vtov(pack_t *pack, rel_t *rel, rel_patch_t *p, __u64 virt) {
	return pack_base_vtov(pack, p->elf, virt);
}

__u64 pack_rel_addr(pack_t *pack, rel_t *rel, elf_t *elf, __u8 t, __u64 v) {
	return pack_get_addr(pack, elf, t, v);
}

ptx_rel_t *ptx_get_rel(pack_t *pack, __u64 off, __u64 size) {
	llist_each_dat(&pack->ll_rel, ptx_rel_t, e) {
		ptx_patch_t *pr = e->patch.list_elem->dat;
		if (_contain_(off, size, pr->off))
			return pr;
	}
	return NULL;
}