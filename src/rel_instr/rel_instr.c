#include <time.h>
#ifndef UAPI_
#define UAPI_
#include "../../disass/include/uapi.h"
#endif
#include "../../include/rel_instr.h"
#include "../../include/xtc.h"
#include "../../include/packing.h"
#include <assert.h>

static __s8 rel_patch_imm_in(rel_patch_t *r, llist_t *patches, struct patched_in *pin);
operand *get_rip_imm_oper(instr_dat_t *in);
__s8 get_rip_imm_oper_ndx(instr_dat_t *in);

static __s8 do_reloc_patch_t(pack_t *pack, rel_patch_t *r, patches_t *p, __u8 *out);
static __u8 rel_stick_instr(instr_dat_t *in, __u8 *ptr, __u64 imm, __u64 virt, __u8 t);
__s64 rel_all_align(pack_t *pack, __u8 t, __u8 ll_t, __u64 base, __u64 size);

static __u64 r_rip_in_ptr(instr_dat_t *in, patches_t *p, __u64 off);
__s64 get_patch_align(llist_t *ll, __u8 t, __u64 src, __u64 dst);
static patches_t *get_dst_patch(llist_t *ll, __u64 off);
static patches_t *get_orig_patch(pack_t *pack, __u64 v);
void fix_rel_in(rel_patch_t *rel);

__s8 new_rel_t(pack_t *pack, rel_patch_t *r, __u64 d_off, elf_t *elf, __u64 s_off, __u64 sz) {
	__u64 t_sz = sz;
	for_each_rel(pack, NULL, rel) t_sz += rel->src.sz;
	if (pack->modif.mm.sz <= t_sz) {
		if (resz_mmsz(&pack->modif.mm, MEM_MMAP, t_sz - pack->modif.mm.sz) == -1)
			return -1;
	}

	*r = (rel_patch_t){
		.src = {
			.elf	= elf,
			.off	= s_off,
			.sz		= sz,
		},
		.out = {
			.off		= d_off,
			.shared_mm	= &pack->modif.mm,
		},
	};
	// new_mmsz(&r->out.shared_mm, sz);
	llist_new(&r->out.patches);
	llist_new(&r->ll_hijack);
}

lle *_rel_(llist_t *ll, __u8 t, __u64 src_off, __u32 src_sz, __u64 dst_off, __u64 dst_sz) {
	patches_t p = {
		.t		= t,
		.orig_off	= src_off,
		.dst_off	= dst_off,
		.orig_sz	= src_sz,
		.dst_sz		= dst_sz,
	};
	return llist_add(ll, F_LL_MALLOC, &p, sizeof(p));
}

lle *_rel_add_(llist_t *ll, __u8 t, struct mmsz_tup *mm, __u64 dst_off, __u64 dst_sz) {
	patches_t p = {
		.t	= t | PATCH_ADD,
		.mm	= mm,		// Someone 'll get raped :}
		.dst_off	= dst_off,
		.dst_sz		= dst_sz,
	};
	return llist_add(ll, F_LL_MALLOC, &p, sizeof(p));
}

rel_patch_t *pack_new_rel_t(pack_t *pack, __u64 d_off, elf_t *elf, __u64 s_off, __u64 sz) {
	rel_patch_t *ret = pack_get_rel(pack, elf, s_off);
	if (!!ret) return ret;

	rel_patch_t r = {0};
	new_rel_t(pack, &r, d_off, elf, s_off, sz);

	lle *e = llist_add(&pack->modif.rel, F_LL_MALLOC, &r, sizeof(rel_patch_t));
	return ((!e) ? NULL : (e->dat));
}

rel_patch_t *pack_off_to_rel(pack_t *p, elf_t *elf, __u64 off) {
	for_each_rel(p, elf, rel) {
		if (_contain_(rel->src.off, rel->src.sz, off)) return rel;
	}
	return NULL;
}

rel_patch_t *pack_get_rel(pack_t *p, elf_t *elf, __u64 off) {
	for_each_rel(p, elf, rel) {
		if (rel->src.off == off) return rel;
	}
	return NULL;
}

patches_t *_rel_cpy_(llist_t *ll, __u8 t, __u64 dst_off, __u32 src_sz, __u64 off, __u64 dst_sz) {
	lle *e = _rel_(ll, t, 0, src_sz, dst_off, dst_sz);
	if (!e) return NULL;
	patches_t *p = e->dat;

	p->off	= off;
	p->sz	= dst_sz;

	return p;
}

__s8 new_mm_t(mm_t *mm, __u8 t, __u64 sz) {
	if (!mm) return -1;
	*mm = (mm_t){ .t=t, .sz=sz, };

	switch (t) {
		case MEM_HEAP:	mm->mem = xmalloc(sz);	break;
		case MEM_MMAP:	mm->mem = map_anon(sz);	break;
		case MEM_NONE: break;
		default:
			prf_x(PR_WARN, "Unknown type %lx", t);
			return -1;
	}
	return 0;
}

static __u64 r_rip_in_ptr(instr_dat_t *in, patches_t *p, __u64 off) {
	__u64 imm = 0, in_off = p->orig_off;
	if (p->t == PATCH_ADD) in_off = p->dst_off;
	get_rip_ptr_addr(in, in_off + off, &imm);
	return imm;
}

struct rel_hijack *_rel_hijack_(rel_patch_t *r, __u64 orig_vaddr, __u64 dst_off) {
	struct rel_hijack h = {
		.orig_vaddr = orig_vaddr,
		.dst_off	= dst_off,
	};
	lle *ret = llist_add(&r->ll_hijack, F_LL_MALLOC, &h, sizeof(h));
	return (!ret) ? NULL : ret->dat;
}

struct rel_hook *_rel_hook_(patches_t *p, __u8 t, __u64 src, __u64 v) {
	struct rel_hook h = { .t=t, .src=src, .v=v };

	if (!p->ll_hook.head) llist_new(&p->ll_hook);
	lle *ret = llist_add(&p->ll_hook, F_LL_MALLOC, &h, sizeof(h));

	return (!ret) ? NULL : ret->dat;
}

__s64 pin_align(pack_t *pack, __u64 base, __u64 size) {
	return rel_all_align(pack, P_F_MAIN | P_F_MAIN, 0, base, size);
}
__s64 patches_align(pack_t *pack, __u64 base, __u64 size) {
	return rel_all_align(pack, P_F_MAIN | P_F_MAIN, 1, base, size);
}

__s64 rel_all_align(pack_t *pack, __u8 t, __u8 ll_t, __u64 base, __u64 size) {
	__s64 sz = 0;
	for_each_rel(pack, NULL, rel) {
		sz += get_patch_align(((!ll_t) ? &rel->pin->ll : &rel->out.patches), t, base, size);
	}
	return sz;
}

__u64 rel_get_all_inner_off(pack_t *pack, __u64 src, __u64 sz) {
	__u64 pin = rel_all_align(pack, P_F_INNER, 0, src, sz);
	__u64 ptx = rel_all_align(pack, P_F_INNER, 1, src, sz);
	return pin + ptx;
}

__u64 rel_get_all_off(pack_t *pack, __u64 src, __u64 sz) {
	__u64 pin = rel_all_align(pack, P_F_INNER | P_F_MAIN, 0, src, sz);
	__u64 ptx = rel_all_align(pack, P_F_INNER | P_F_MAIN, 1, src, sz);
	return ptx + pin;
}

ok_t rel_get_hijack(pack_t *pack, rel_patch_t *r, __u64 imm) {
	foreach_ll(&r->ll_hijack, e) {
		struct rel_hijack *h = e->dat;

		if (h->orig_vaddr == imm) {
			__u64 ret = rel_get_all_inner_off(pack, 0, h->dst_off) + pin_align(pack, 0, h->dst_off) + h->dst_off;
			return _OK(1, ret);
		}
	}

	return _OK(0, -1);

}

ok_t rel_get_hook(pack_t *p, patches_t *px, __u64 off) {
	if (!px->ll_hook.head) return _OK(0, -1);
	
	foreach_ll(&px->ll_hook, e) {
		struct rel_hook *h = e->dat;

		if (h->src == off) {
			__u64 r = 0;
			switch (h->t) {
				case HOOK_T_ORIG:	r = h->v; break;
				case HOOK_T_DST:
				case HOOK_T_TOKEN:
			}

			return _OK(1, r);
		}
	}

	return _OK(0, -1);
}


pack_fragment_t *get_ll_patch(pack_t *pack, llist_t *ll, __u64 off) {
	__u64 ret = 0;
	for_each_rel(pack, NULL, r) {
		for_each_patches(&r->out.patches, p) {
			if (p->dst_off + p->dst_sz > ret) {
				ret = p->dst_off + p->dst_sz;
			}
		}
	}

	for_each_orig_patch(pack, patch) {
		if (patch->off == off) {
			pack_fragment_t *e = NULL;
			ll_each(ll, e) {
				if (e->off == patch->off) return e;
			}

			__u64 sz = ret + rel_get_all_off(pack, 0, ret);
			return p_add_patch_ll(ll, map_anon(sz), patch->off, sz);
		}
	}
	return NULL;
}

__s8 do_reloc(pack_t *pack) {
	for_each_rel(pack, NULL, rel) {
		__u64 align = pack_hdr_align(pack, elf_vtof(rel->src.elf, rel->out.off));

		rel->pin = xmalloc(sizeof(struct patched_in));
		llist_new(&rel->pin->ll);
		new_mm_t(&rel->pin->sc, MEM_MMAP, 0x1000);

		rel->out.off += align;
		__s8 ret = rel_patch_imm_in(rel, &rel->out.patches, rel->pin);
		rel->out.off -= align;

		if (ret == -1) return -1;
	}

	llist_t new_patches = {0};
	llist_new(&new_patches);

	for_each_rel(pack, NULL, r) {
		__s64 align = pack_hdr_align(pack, elf_vtof(r->src.elf, r->out.off));
		pack_fragment_t *out = get_ll_patch(pack, &new_patches, r->out.off + align);

		for_each_patches(&r->out.patches, p) {
			if (do_reloc_patch_t(pack, r, p, out->mm.mem) == -1)
				return -1;
		}
	}

	for_each_patches_ll(&new_patches, new) {
		for_each_orig_patch(pack, patch) {
			if (new->off != patch->off) continue;

			foreach_phdr(&pack->elf, p)	 if (p->p_flags & PF_X) {
				p->p_filesz	= new->mm.sz;
				p->p_memsz	= new->mm.sz;
				patch->mm	= new->mm;
				_hexdump(new->mm.mem, new->mm.sz);

				goto next_new;
			}
		}

		next_new:
	}

	return 0;
}

static __u8 *rel_patch_src(rel_patch_t *r, patches_t *p) {
	if (p->t & P_F_INNER) return (!p->mm || !p->mm->mem) ? NULL : p->mm->mem;
	return r->out.shared_mm->mem + p->dst_off;
}

static __s8 do_reloc_patch_t(pack_t *pack, rel_patch_t *r, patches_t *p, __u8 *out) {
	__u8 *ptr	= out;		// output
	__s64 align	= pack_hdr_align(pack, elf_vtof(r->src.elf, r->out.off));
	void *s_ptr = rel_patch_src(r, p);


	volatile __u64 i = 0;
	foreach_instr_off(in, i, s_ptr, p->dst_sz) {
		__u64 off = (p->dst_off + i);

		if (*(__u8*)&p->patches) {
			for_each_patches(&p->patches, ptx) {
				if (ptx->dst_off == off) {
					if (do_reloc_patch_t(pack, r, ptx, out) == -1) return -1;
				}
			}
		}


		off += pin_align(pack, 0, (p->dst_off + i));
		if (!(p->t & P_F_INNER)) {
			off += rel_get_all_inner_off(pack, 0, off);
		}
		ptr = out + off;

		// if (off != (ptr - ret_map)) TRAP();
		__u64 base = (off + r->out.align);
		const operand *rip_oper = get_rip_imm_oper(&in);
		if (!rip_oper) {		// not RIP & IMM
			memcpy(ptr, s_ptr + i, in.in_sz);
			ptr += in.in_sz;
			continue;
		}

		__u64 orig_imm	= r_rip_in_ptr(&in, p, i);
		__u64 imm		= orig_imm + patches_align(pack, p->dst_off + i, in.in_sz) - align; 
		ok_t hook	= rel_get_hook(pack, p, i);

		patches_t *patch = get_orig_patch(pack, imm + align);
		switch (p->t & 0xf) {
			case PATCH_REL:
			{
				ok_t hijack = rel_get_hijack(pack, r, orig_imm);
				// pr_in_str(&in);
				
				if (!patch) {
					if (hijack.ok)	imm = hijack.v;
					// Where is the pointing IMM phdr now
					imm += pack_hdr_align(pack, orig_imm);
					ptr += rel_stick_instr(&in, ptr, (imm - r->src.off), base, CHNG_REL);
					break;
				}

				// Jumps in the Patched area
				imm = (hijack.ok) ? hijack.v : rel_get_off(pack, r, orig_imm);
				
				// Is it patched
				patches_t *p_sc = get_dst_patch(&r->pin->ll, p->dst_off + i);
				if (!p_sc) {
					ptr += rel_stick_instr(&in, ptr, imm, base, CHNG_REL);
					break;
				}

				instr_dat_t sc_in = {0};
				init_instr(r->pin->sc.mem + p_sc->off, &sc_in);
				ptr += rel_stick_instr(&sc_in, ptr, imm, base, CHNG_REL);
			}
			break;
			case PATCH_ADD:
			{
				__u64 v = (hook.ok) ? hook.v - r->src.off : orig_imm;
				if (hook.ok) {
					ptr += rel_stick_instr(&in, ptr, v, base, CHNG_REL);
					break;
				}
				__s64 align = pin_align(pack, p->dst_off + i, v);
				ptr += rel_stick_instr(&in, ptr, v, align, CHNG_FXD);
			}
			break;
			default:
				return -1;
		}
	}
}

static __u8 rel_stick_instr(instr_dat_t *in, __u8 *ptr, __u64 imm, __u64 virt, __u8 t) {
	__u64 v = 0;
	switch (t) {
		case CHNG_REL:	v = (imm - virt) - in->in_sz;	break;
		case CHNG_FXD:	v = (imm + virt);				break;
		default: TRAP();
	}
	if (change_ptr(in, v, t) == -1) DIE("FUCK!");
	return assemble(in, ptr);
}

static __s8 rel_patch_imm_in(rel_patch_t *r, llist_t *patches, struct patched_in *pin) {
	mm_t *const sc = &pin->sc;

	for_each_patches(patches, p) {
		// if (p->t != PATCH_REL) continue;
		if (*(__u8*)(&p->patches)) {
			if (rel_patch_imm_in(r, &p->patches, pin) == -1)
				return -1;
		}

		__u64 i = 0;
		foreach_instr_off(in, i, rel_patch_src(r, p) + p->dst_off, p->dst_sz) {
			instr_dat_t lin = {0};
			__u8 *ptr = sc->mem + sc->off;

			__s8 ndx = get_rip_imm_oper_ndx(&in);
			if (ndx == -1) continue;
			const operand *op = &in.oper[ndx];
			
			if (get_oper_sz(&in, op) < _DWORD_) {
				__u8 flags[4] = {0};
				flags[ndx] = X_FLAG(XTC_IMM, X_DW);

				if (xtc_make_in(&lin, flags, ptr, in.instr) == -1) DIE("FU3CK!");
				if (sc->off + MAX_INSTR_SZ > sc->sz) DIE("FU8CK!");

				_rel_cpy_(&pin->ll, PATCH_REPLACE, p->dst_off + i, in.in_sz, sc->off, lin.in_sz);
				sc->off += lin.in_sz;

				if (sc->off + 0x100 > sc->sz) {
					resz_mm(sc, 0x1000);
				}
			}
		}
	}

	return 0;
}

operand *get_rip_imm_oper(instr_dat_t *in) {
	foreach_operand(oper, in) {
		if (oper->rip && (oper->imm || oper->disp))
			return in;
	}
	return NULL;
}

__s8 get_rip_imm_oper_ndx(instr_dat_t *in) {
	__u8 i = 0;
	foreach_operand(oper, in) {
		if (oper->rip && (oper->imm || oper->disp)) return i;
		i++;
	}
	return -1;
}

patches_t *get_first_patch(llist_t *ll, patches_t *min) {
	patches_t *patch = NULL;
	foreach_ll(ll, e) {
		patches_t *p = e->dat;
		if (	( !patch || p->dst_off < patch->dst_off)
			&&	( !min || p->dst_off > min->dst_off))
		{
			patch = p;
		}
	}
	return patch;
}



static patches_t *get_dst_patch(llist_t *ll, __u64 off) {
	patches_t *p = NULL;
	ll_each(ll, p) if (off == p->dst_off) return p;
	return NULL;
}

static patches_t *get_orig_patch(pack_t *pack, __u64 v) {
	for_each_rel(pack, NULL, rel) {
		for_each_patches(&rel->out.patches, p) {
			if (p->orig_off == -1) continue;
			if (_contains_(p->orig_off, p->orig_sz, v, 1))
				return p;
		}
	}
	return NULL;
}

__s64 get_patch_align(llist_t *ll, __u8 t, __u64 src, __u64 dst) {
	__u64 base = ((src > dst) ? dst : src);
	__u64 size = ((src > dst) ? src : dst) - base;
	__s64 align = 0;
	for_each_patches(ll, p) {
		if ((t & P_F_INNER) && *(__u8*)(&p->patches))
			align += get_patch_align(&p->patches, t, src, dst);

		if ((t & p->t & P_F_INNER) || t & P_F_MAIN) {
			if (	((t & p->t & P_F_INNER) && !size && !p->dst_off)
				||	_contain_(base, size, p->dst_off)) {
				switch (p->t & 0xf) {
					case PATCH_REPLACE:
						align += (p->dst_sz - p->orig_sz);
						break;
					case PATCH_REMOVE:
						align -= p->dst_sz;
						break;
					case PATCH_ADD:
						align += p->dst_sz;
						break;
				}
			}
		}
	}

	return ((src > dst) ? -1 : 1) * align;
}