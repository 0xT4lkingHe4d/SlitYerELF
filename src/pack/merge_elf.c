#include <string.h>
#ifndef UAPI_
#define UAPI_
#include "../../disass/include/uapi.h"
#endif
#include "../../include/packing.h"
#include "../../include/rel_instr.h"

typedef struct {
	__u8	t;
	__u8	*str;
	sym_obj	*orig_fn;
	sym_obj *modif_fn;
} me_target_t;

static __s8 import_plt(pack_t *p, merge_elf_t *m, __u8 *name, Elf_Rela *m_rela);
static __s8 m_instr_imm_R(pack_t *p, merge_elf_t *m, __u64 imm, me_target_t *trg, __u64 off);
static __s8 m_instr_imm_X(pack_t *p, merge_elf_t *m, __u64 imm, me_target_t *trg, __u64 off);
static __s64 m_stick_modif(pack_t *pack, merge_elf_t *m, me_target_t *trg, __u64 off);
static me_target_t *mrg_get_first_target(merge_elf_t *m, me_target_t *trg);
static merge_cpy_t *merge_cpy_get(merge_elf_t *m, __u64 s_off);

__s8 merge_elf_get_type(me_target_t *r, __u8 *attr) {
	if (MRG_CMP_ATTR(SYM, attr)) {
		*r = (me_target_t){ .t=MRG_SYM, .str=&attr[strlen(MRG_SYM_ATTR)] };
		return 0;
	}

	return -1;
}

__s8 merge_elf_init(merge_elf_t *m) {
	llist_new(&m->ll_target);
	new_mmsz_t(&m->mm_cpy, MEM_HEAP, 0x10 * sizeof(merge_cpy_t));

	foreach_shdr(m->modif_elf, sec) {
		const __u8 *sec_name = elf_sec_name(m->modif_elf, sec);

		me_target_t v = {0};
		if (merge_elf_get_type(&v, sec_name) == -1) continue;

		foreach_symtab(m->modif_elf, stab, sym) {
			if (sym->st_value == sec->sh_addr) {
				v.modif_fn = make_sym_obj(m->modif_elf, sym);
				if (!v.modif_fn) return -1;
			}
		}

		switch (v.t) {
			case MRG_SYM:
				v.orig_fn = get_sym(m->orig_elf, v.str);
				if (!v.orig_fn) {
					prf(PR_ERR "Failed to find symbol - [ %s ]\n", v.str);
					return -1;
				}
			break;
		}

		llist_add(&m->ll_target, F_LL_MALLOC, &v, sizeof(me_target_t));
	}

	return 0;
}

#define for_each_target(m, trg)		\
		for (me_target_t *trg = NULL; !!(trg = mrg_get_first_target((m), trg)); )

static __s8 merge_elf_check(pack_t *pack, merge_elf_t *m) {
	elf_t *s_elf = m->orig_elf, *m_elf = m->modif_elf;

	for_each_target(m, trg) {
		switch (trg->t) {
			case MRG_SYM:
			{
				Elf_Phdr *s_phdr = elf_off_to_phdr(s_elf, trg->orig_fn->off);
				Elf_Phdr *m_phdr = elf_off_to_phdr(m_elf, trg->modif_fn->off);
				__u64 off = s_phdr->p_offset;

				m->m_rel = pack_new_rel_t(pack, off, m_elf, m_phdr->p_offset, m_phdr->p_filesz);
				m->s_rel = pack_new_rel_t(pack, off, s_elf, s_phdr->p_offset, s_phdr->p_filesz);
				if (!m->m_rel || !m->s_rel) return -1;
			}
		}
	}
	return 0;
}

__s8 merge_elf(pack_t *pack, merge_elf_t *m) {
	elf_t *s_elf = m->orig_elf, *m_elf = m->modif_elf;
	if (merge_elf_check(pack, m) == -1) return -1;

	__u8 *ptr = pack->modif.mm.mem;
	rel_patch_t *rel = m->s_rel;
	__u64 min=0, off=0, src_off=0;

	for_each_target(m, trg) {
		sym_obj *fn = trg->orig_fn;

		__u64 fn_off = fn->off - rel->src.off;
		__u64 sz	 = fn_off - src_off;

		memcpy(ptr + off, s_elf->map + rel->src.off + src_off, sz);
		_rel_(&rel->out.patches, PATCH_REL, elf_ftov(s_elf, rel->src.off + src_off), sz, off, sz);

		off		= fn_off + (off - src_off);
		src_off	= fn_off;

		_rel_hijack_(rel, elf_ftov(s_elf, fn->off), off);
		__u64 ret = m_stick_modif(pack, m, trg, off);
		if (ret == -1) return -1;

		off += ret;
	}

	__u64 sz = rel->src.sz - src_off;
	memcpy(ptr + off, s_elf->map + rel->src.off + src_off, sz);
	_rel_(&rel->out.patches, PATCH_REL, elf_ftov(s_elf, rel->src.off + src_off), sz, off, sz);

	// __u8 *sname = "printf@GLIBC_2.2.5";
	// pack_t *p = pack;
	// symtab_t *sym	= elf_get_symtab(&p->elf);
	// _assert(!!sym, "FU!K!K!");
	// __u64 symstr_sz = sym->mm_str.sz;
	// pack_ext_hdr(p, _elf_off(&p->elf, sym->str), strlen(sname) + 1);
	// memcpy(sym->str + symstr_sz, sname, strlen(sname));
	// __u64 si = _elf_symtab_sz(sym) / sizeof(Elf_Sym);
	// pack_ext_hdr(p, sym->off, sizeof(Elf_Sym));
	// sym->tab[si] = (Elf_Sym){
	// 	.st_info	= ELF64_ST_INFO(STB_GLOBAL, STT_FUNC),
	// 	.st_name	= symstr_sz,
	// };

	return 0;
}

static __s64 m_stick_modif(pack_t *pack, merge_elf_t *m, me_target_t *trg, __u64 off) {
	__u8 *ptr = pack->modif.mm.mem + off;
	elf_t	*m_elf	= m->modif_elf,		*s_elf 	= m->orig_elf;
	sym_obj *m_fn	= trg->modif_fn,	*s_fn	= trg->orig_fn;

	*ptr = 0xcc;
	memcpy(ptr + 1, m_elf->map + m_fn->off, m_fn->size);

	__u64 i = 0;
	foreach_instr_off(in, i, ptr + 1, m_fn->size) {
		__u64 imm = 0;
		if (get_rip_ptr_addr(&in, elf_ftov(m_elf, m_fn->off + i), &imm) == -1)
			continue;

		Elf_Phdr *p = elf_off_to_phdr(m_elf, imm);
		if (!p) return -1;

		switch (p->p_flags) {
			case PF_R | PF_X:	// R-X
				m_instr_imm_X(pack, m, imm, trg, off + i);
				break;
			case PF_R | PF_W:	// RW-
				break;
			case PF_R:			// R--
				m_instr_imm_R(pack, m, imm, trg, off + i);
				break;
			default:
				return -1;
		}
	}

	// prf("%lx\n", elf_ftov(m_elf, m_fn->off-1));
	_rel_(&m->m_rel->out.patches, PATCH_REL, elf_ftov(m_elf, m_fn->off-1), m_fn->size + 1, off, m_fn->size + 1);
	return m_fn->size +1;
}
patches_t *rel_patch_by_orig_off(llist_t *ll, __u64 off) {
	for_each_patches(ll, p)
		if (_contain_(p->orig_off, p->orig_sz, off)) return p;
	return NULL;
}

static __s8 m_instr_imm_R(pack_t *p, merge_elf_t *m, __u64 imm, me_target_t *trg, __u64 off) {
	elf_t *m_elf = m->modif_elf, *s_elf = m->orig_elf;
	Elf_Shdr *sec = elf_off_to_shdr(m_elf, imm);
	if (!sec) return -1;
	
	Elf_Shdr *s_sec = elf_sec_by_name(s_elf, elf_sec_name(m_elf, sec));

	__u64 v = pack_ftof(p, s_elf, s_sec->sh_offset);
	p_add_patch(p, m_elf->map + sec->sh_offset, v + s_sec->sh_size, sec->sh_size);

	prf(PR_WARN "%lx %lx %lx\n", 0x1fd7, imm, v + s_sec->sh_size);//(imm - elf_ftov(&p->elf, v)));
	_rel_hijack_(m->m_rel, imm, 0x1fd7);
	return 0;

}

#define ELF_PLT_ENTRY_SZ	0x10

static __s8 m_instr_imm_X(pack_t *p, merge_elf_t *m, __u64 imm, me_target_t *trg, __u64 off) {
	elf_t *m_elf = m->modif_elf, *s_elf = m->orig_elf;
	rela_t *plt_rel = elf_get_plt_rela(m_elf);
	if (!plt_rel) return -1;

	symtab_t *s_tab = elf_get_dyntab(s_elf), *m_tab = elf_get_dyntab(m_elf);
	if (plt_rel->t == DT_RELA) {
		__u64 mv = 0;
		Elf_Rela *m_rela = NULL;
		foreach_rela_t(plt_rel, rela, Elf_Rela) {
			if (ELF64_R_TYPE(rela->r_info) == R_X86_64_JUMP_SLOT) {
				__u64 v = *(__u64*)(m_elf->map + elf_vtof(m_elf, rela->r_offset));

				if (!mv || ((imm-mv) < (imm-v) && v >= imm)) {
					mv		= v;
					m_rela	= rela;
				}
			}
		}

		if (imm > mv || (mv - imm) > ELF_PLT_ENTRY_SZ)
			goto import_fn;

		__u8 *m_name = elf_rela_name(m_tab, m_rela);
		foreach_rela(s_elf, rtab, rela) {
			__u8 *s_name = elf_rela_name(s_tab, rela);
			if (!strncmp(s_name, m_name, 0x100)) {
				__u64 sv	= *(__u64*)(s_elf->map + elf_vtof(s_elf, rela->r_offset));
				__u64 off	= (sv - m->s_rel->out.off) - (mv - imm);
				_rel_hijack_(m->m_rel, imm, off);
				return 0;
			}
		}

		__u64 off = import_plt(p, m, m_name, m_rela);
		if (off == -1) return -1;

		_rel_hijack_(m->m_rel, imm, off);
	}

	import_fn:

	return 0;
}


static __s8 import_plt(pack_t *p, merge_elf_t *m, __u8 *name, Elf_Rela *m_rela) {
	elf_t *m_elf = m->modif_elf, *s_elf = m->orig_elf;
	got_entry_t got = {0};
	 if (p_add_got_entry(p, &got) == -1)
	 	return -1;

	rela_t	 *plt = elf_get_plt_rela(&p->elf);
	symtab_t *dyn = elf_get_dyntab(&p->elf);
	if (!dyn || !plt) return -1;

	__u16 di = p_add_sym(p, dyn, name, strlen(name), &(Elf_Sym){
		.st_info = ELF64_ST_INFO(STB_GLOBAL, STT_FUNC),
	});

	__u16 ri = p_add_rela(p, plt, &(Elf_Rela){
		.r_info		= ELF64_R_INFO(di, R_X86_64_JUMP_SLOT),
		.r_offset	= got.addr,
	});

	__u8 *ver_str = elf_ver_str(m_elf, ELF64_R_SYM(m_rela->r_info));
	if (ver_str == -1) return -1;

	// symtab_t *m_dyn = elf_get_dyntab(m_elf);//, *r_dyn = elf_get_dyntab(&p->elf);

	__u16 vna_other = 0;
	if (!!ver_str) {
		Elf_Vernaux *vna = elf_vernaux_by_name(&p->elf, ver_str);
		if (!!vna) {
			p_add_gnu_versym(p, vna->vna_other);
		} else {
			prf(PR_INFO "%lx, %s\n", vna->vna_other, &dyn->str[vna->vna_name]);
			// pack_ext_hdr(p, p->elf.gnu_ver.need_off, sizeof(Elf_Verneed));
		}
	}

	struct mmsz_tup *mm = new_mmsz_tup(0x10);
	memcpy(	mm->mem,
			"\xff\x25\x00\x00\x00\x00"		// jmp	[rip+0]
			"\x68\x00\x00\x00\x00"			// push	0
			"\xe9\x00\x00\x00\x00",			// jmp	0
			0x10);

	Elf_Shdr *sec_plt	= elf_sec_by_name(s_elf, ".plt");
	if (!sec_plt) return -1;

	__u64 off = sec_plt->sh_offset - m->s_rel->src.off + sec_plt->sh_size;

	patches_t *px = rel_patch_by_orig_off(&m->s_rel->out.patches, sec_plt->sh_offset);
	if (!px) return -1;
	if (!px->patches.head) llist_new(&px->patches);
	lle *e = _rel_add_(&px->patches, P_F_INNER, mm, off, 0x10);
	if (!e) return -1;

	pack_fix_u64(p, m->s_rel, got.ptr, off + 6);

	*(__u32*)(mm->mem + 7)	= ri;
	*(__u32*)(mm->mem + 12)	= px->orig_off - sec_plt->sh_addr - 12;
	_rel_hook_(e->dat, HOOK_T_ORIG, 0, got.addr);

	return off;
}

static me_target_t *mrg_get_first_target(merge_elf_t *m, me_target_t *trg) {
	me_target_t *i=NULL, *ret=NULL;
	ll_each((&m->ll_target), i) {
		if (!trg || i->orig_fn->off > trg->orig_fn->off)
			if (!ret || (i->orig_fn->off < ret->orig_fn->off))
				ret = i;
	}
	return ret;
}

