#include <linux/types.h>
#include "../../include/packing.h"

#define foreach_hdr_sorted(pack, i)			\
		for (off_mmsz_t *i = NULL; !!(i = x_get_min((pack)->hdr.ptr, (pack)->hdr.num, i)); )

#define foreach_hdr_patches(pack, p)		\
		foreach_ll_T(&(pack)->modif.hdr, p, pack_patch)

static __s8 make_elf_main(pack_t *p, int fd);
static off_mmsz_t *x_get_min(off_mmsz_t *x, __u64 num, off_mmsz_t *min);

static __u64 pack_get_orig_off(pack_t *p, elf_t *elf, __u64 t, __u64 v, __u8 out_t);
__u64 pack_hdr_align(pack_t *p, __u64 virt);
static __u64 pack_get_offset_t(pack_t *pack, elf_t *elf, __u8 t, __u64 s_off, __u64 d_off);
static __u64 rel_get_offset_t(pack_t *pack, rel_patch_t *r, __u8 t, __u64 off);

static __u64 *pack_get_addr(pack_t *p, __u64 off);
static void patch_rela(pack_t *pack, rela_t *rtab);

__s8 split_patches(elf_t *elf, void *ptr, __u8 iter, __u64 off, __u64 sz, __u64 s_off, __u64 s_sz, __u8 t);
static __s8 init_hdr_arr(pack_t *pack);
static void elf_shift_off(elf_t *elf, __u64 off, __u64 sz);
void pack_split(pack_t *pack, __u64 off, __u64 sz);

__s8 import_elf(elf_t *elf, pack_t *p) {
	if (!p || !elf) return -1;

	p->orig_elf = elf;
	memcpy(&p->elf, elf, sizeof(elf_t));
	elf_alloc_all(&p->elf);

	llist_new(&p->modif.rel);
	llist_new(&p->modif.pack);
	llist_new(&p->modif.hdr);
	llist_new(&p->modif.fixes);

	init_hdr_arr(p);
	if (!!elf->phdr.tab) {
		foreach_phdr(elf, phdr)
			pack_split(p, phdr->p_offset, phdr->p_filesz);
	} else {
		foreach_shdr(elf, sec)
			pack_split(p, sec->sh_offset, sec->sh_size);
	}

	if (new_mmsz_t(&p->modif.mm, MEM_MMAP, 0x1000) == -1)
		return -1;

	return 0;
}

__s8 make_elf(pack_t *p, __u8 *output) {
	if (file_exists(output)) {
		prf(PR_ERR "output file exitsts - " color(BGRN, "%s\n"), output);
		return -1;
	}

	int fd = open(output, O_CREAT|O_RDWR, 0755);
	if (fd == -1) return -1;

	patch_elf(p);

	if (make_elf_main(p, fd) == -1) {
		close(fd);
		return -1;
	}
	
	close(fd);
	return 0;
}

/**
 * Pack into an ELF
 **/
static __s8 make_elf_main(pack_t *pack, int fd) {
	elf_t *elf = &pack->elf;

	foreach_ll_T((&pack->modif.pack), p, pack_fragment_t) {
		_wr(fd, p->off, p->mm.mem, p->mm.sz);
	}
	init_hdr_arr(pack);
	foreach_hdr_sorted(pack, i) {
		_wr(fd, i->off, i->mm->mem, i->mm->sz);
	}

	return 0;
}




lle *_hdr_(pack_t *pack, elf_t *elf, __u8 f, __u64 orig_off, __u32 orig_sz, __u64 dst_off, __u32 dst_sz) {
	pack_patch e = {
		.f			= f,
		.elf		= elf,
		.orig_off	= orig_off,
		.orig_sz	= orig_sz,
		.dst_off	= dst_off,
		.dst_sz		= dst_sz,
	};
	return llist_add(&pack->modif.hdr, F_LL_MALLOC, &e, sizeof(e));
}

__s64 pack_ext_hdr(pack_t *pack, __u64 off, __u64 sz) {
	foreach_hdr_sorted(pack, i) {
		if (_contain_(i->off, i->mm->sz, off)) {
			// prf("$$$$ %lx %lx\n", off, pack_hdr_align(pack, off));
			_hdr_(pack, NULL, PATCH_EXT, i->off - pack_hdr_align(pack, off), i->mm->sz, 0, sz);
			resz_mmsz(i->mm, 0, sz);
			
			elf_shift_off(&pack->elf, off, sz);
			for_each_orig_patch(pack, e) if (e->off > off) e->off += sz;
			init_hdr_arr(pack);
			return i->mm->sz;
		}
	}
	return -1;
}

static void pack_clean(pack_t *pack) {
	L1: foreach_ll((&pack->modif.pack), e_i) {
		foreach_ll((&pack->modif.pack), e_l) if (e_l != e_i) {
			pack_fragment_t *i = e_i->dat, *l = e_l->dat;

			if (_crossed_(l->off, l->mm.sz, i->off, i->mm.sz)) {
				lle *to_free = NULL;
				if (i->off == l->off) to_free = (i->mm.sz > l->mm.sz) ? e_l : e_i;
				else {
					pack_fragment_t *a = ((i->off > l->off) ? l : i),
									*b = ((i->off > l->off) ? i : l);

					if (a->off + a->mm.sz < b->off + b->mm.sz) {
						a->mm.sz = (b->off + b->mm.sz - a->off);
					}
					to_free = ((b == i) ? e_i : e_l);
				}
				lle_free(&pack->modif.pack, to_free);
				goto L1;
			}
		}
	}
}


pack_fragment_t *p_add_patch_ll(llist_t *ll, void *ptr, __u64 off, __u64 sz) {
	if (!ptr) return NULL;
	
	pack_fragment_t st = {
		.orig_off	= off,
		.orig_sz	= sz,
		.off		= off,
		.mm			= { .mem=ptr, .sz=sz },
	};

	lle *ret = llist_add(ll, F_LL_MALLOC, &st, sizeof(st));
	return (!ret) ? NULL : ret->dat;

}
pack_fragment_t *p_add_patch(pack_t *pack, void *ptr, __u64 off, __u64 sz) {
	return p_add_patch_ll(&pack->modif.pack, ptr, off, sz);
}

static void elf_shift_off(elf_t *elf, __u64 off, __u64 sz) {
	Elf_Ehdr *ehdr = elf->ehdr;
	__u64 virt = elf_ftov(elf, off);

	// if (ehdr->e_entry >= virt) ehdr->e_entry += sz;
	if (ehdr->e_phoff >= off) ehdr->e_phoff += sz;
	if (ehdr->e_shoff >= off) ehdr->e_shoff += sz;


	foreach_shdr(elf, sec) {
		if (_contain_(sec->sh_offset, sec->sh_size, off)) {
			sec->sh_size	+= sz;
		} else if (sec->sh_offset > off) {
			sec->sh_offset	+= sz;
			sec->sh_addr	+= sz;//_align(sec->sh_addralign, sz);
		}
	}

	foreach_ll_symtab(elf, stab) if (stab->off > off) stab->off += sz;
	foreach_sym(elf, stab, sym) {
		if (sym->st_value >= virt) sym->st_value += sz;
	}

	foreach_ll_rela(&elf->ll_rela, rtab)	if (rtab->off > off) rtab->off += sz;
	foreach_ll_rela(&elf->ll_rel, rtab)		if (rtab->off > off) rtab->off += sz;

	// foreach_rela(elf, rtab, r)	if (r->r_offset >= virt) r->r_offset += sz;
	// foreach_rel(elf, rtab, r)	if (r->r_offset >= virt) r->r_offset += sz;
	if (!!elf->gnu_ver.sym && elf->gnu_ver.sym_off > off) elf->gnu_ver.sym_off += sz;

	foreach_phdr(elf, p) {
		__u64 align_sz = _align(p->p_align, sz);
		if (_contain_(p->p_offset, p->p_filesz, off)) {
			p->p_memsz	+= sz;//align_sz;
			p->p_filesz	+= sz;//align_sz;
		} else if (p->p_offset > off) {
			p->p_offset += sz;
			p->p_vaddr	+= sz;
			p->p_paddr	+= sz;
		}
	}

	if (elf->dynamic.off > off) elf->dynamic.off += sz;
	foreach_dynamic_ptr(elf, dyn)
		if (dyn->d_un.d_ptr > virt) {
			// prf("%lx\n", dyn->d_un.d_ptr);//elf_ftov(elf, elf_vtof(elf, dyn->d_un.d_ptr) + sz);
			// dyn->d_un.d_ptr += sz;
		}
}


static off_mmsz_t *x_get_min(off_mmsz_t *x, __u64 num, off_mmsz_t *min) {
	off_mmsz_t *ret = NULL;
	for (__u64 i = 0; i < num; i++) {
		if ((!ret || ret->off > x[i].off) && (!min || x[i].off > min->off))
			ret = &x[i];
	}
	return ret;
}

static __s8 init_hdr_arr(pack_t *pack) {
	elf_t *elf = &pack->elf;
	if (!!pack->hdr.ptr) free(pack->hdr.ptr);

	pack->hdr.num = 7;
	foreach_ll_rela(&elf->ll_rela, tab)		pack->hdr.num++;
	foreach_ll_rela(&elf->ll_rel, tab)		pack->hdr.num++;
	foreach_ll_symtab(elf, tab)				pack->hdr.num+=2;

	typedef off_mmsz_t x_t;

	x_t *ptr = pack->hdr.ptr = xmalloc(sizeof(x_t) * pack->hdr.num);
	__u64 i = 0;

	ptr[i++] = (x_t){ .off = 0, .mm = &elf->mm_ehdr };
	ptr[i++] = (x_t){ .off = elf->ehdr->e_phoff,	.mm = &elf->phdr.mm		};
	ptr[i++] = (x_t){ .off = elf->ehdr->e_shoff,	.mm = &elf->sec.mm_tab	};
	ptr[i++] = (x_t){ .off = elf->dynamic.off,		.mm = &elf->dynamic.mm	};
	ptr[i++] = (x_t){ .off = elf->sec.tab[elf->ehdr->e_shstrndx].sh_offset, .mm = &elf->sec.mm_str };
	ptr[i++] = (x_t){ .off = elf->gnu_ver.sym_off,	.mm = &elf->gnu_ver.mm_sym };
	ptr[i++] = (x_t){ .off = elf->gnu_ver.need_off,	.mm = &elf->gnu_ver.mm_need };

	foreach_ll_rela(&elf->ll_rela, rtab)	ptr[i++] = (x_t){ .off = rtab->off, .mm = &rtab->mm };
	foreach_ll_rela(&elf->ll_rel, rtab)		ptr[i++] = (x_t){ .off = rtab->off, .mm = &rtab->mm };

	foreach_ll_symtab(elf, stab) {
		ptr[i++] = (x_t){ .off = stab->off, .mm = &stab->mm_tab };
		ptr[i++] = (x_t){ .off = elf->sec.tab[stab->sec->sh_link].sh_offset, .mm = &stab->mm_str };
	}

	return (i == pack->hdr.num) ? 0 : -1;
}

void pack_split(pack_t *pack, __u64 off, __u64 sz) {
	elf_t *elf = &pack->elf;
	if (!pack->hdr.ptr || !pack->hdr.num) return -1;
	if (!sz) return 0;

	__u64 prev_off = off;

	foreach_hdr_sorted(pack, i)
		if (i->off == off && i->mm->sz == sz) return 0;

	foreach_hdr_sorted(pack, i) {
		__u64 curr_sz = off + sz - prev_off;

		if (_crossed_(i->off, i->mm->sz, prev_off, curr_sz)) {
			if (prev_off < i->off) {
				p_add_patch(pack, elf->map + prev_off, prev_off, (i->off - prev_off));
				prev_off = i->off;
			}
			if (i->off == prev_off && i->mm->sz < curr_sz) {
				prev_off = i->off + i->mm->sz;
			}

			if ((i->off < prev_off)					&&
				(i->off + i->mm->sz > prev_off)		&&
				(i->off + i->mm->sz < prev_off + curr_sz))
			{
				prev_off = i->off + i->mm->sz;
			}
		}
	}

	p_add_patch(pack, elf->map + prev_off, prev_off, (off + sz - prev_off));
	pack_clean(pack);

	return 0;
}

void patch_elf(pack_t *p) {
	__u64 *entry = &p->elf.ehdr->e_entry;
	*entry = pack_vtov(p, p->orig_elf, *entry);
	prf("\t new entry 0x%lx\n", *entry);

	pack_fix_st *fix = NULL;
	ll_each(&p->modif.fixes, fix) {
		__u64 v = fix->rel->out.off + pack_hdr_align(p, fix->rel->out.off)
				+ fix->off + pin_align(p, 0, fix->off);
		*(__u64*)fix->dst = v;
	}

	foreach_dynamic_ptr(&p->elf, dyn) {
		dyn->d_un.d_val = pack_vtov(p, p->orig_elf, dyn->d_un.d_val);
	}

	foreach_dynamic_ptr(&p->elf, dyn) {
		foreach_ll_rela((&p->elf.ll_rela), rtab) {
			if (dyn->d_un.d_val == rtab->off) {
				switch (dyn->d_tag) {
					case DT_JMPREL:
					case DT_RELA:
						patch_rela(p, rtab); break;
				}
			}
		}

// 		next:
	}
			// if (!rtab->sec) continue;
			// const __u8 *sec_name = elf_sec_name(&p->elf, rtab->sec);
			// if (!strncmp(sec_name, ".rela.dyn", 10)) {
			// } else if (!strncmp(sec_name, ".rela.plt", 10)) {
				// pr("++"); // patch_rela_plt(p, r, st);
			// }	

		// p_each_dyn_addr(p, dyn) {
		// 	__u64 v = dyn->d_un.d_ptr;
		// 	if (_contain_(r->src.off, r->src.sz, v))
		// 		dyn->d_un.d_ptr = r->src.off + rel_get_off(r, v);
		// }
	// }
}

pack_fragment_t *pack_orig_off_patch(pack_t *pack, __u64 off) {
	for_each_orig_patch(pack, e) {
		if (_contain_(e->off, e->mm.sz, off)) return e;
	}
	return NULL;
}

__u64 rel_phdr_align(pack_t *pack, __u64 off) {
	__u64 ret = 0;
	foreach_hdr_patches(pack, e) {
		if (e->orig_off <= off)
			ret += e->dst_sz;
	}
	return off + ret;
}


static __u64 *pack_get_addr(pack_t *p, __u64 off) {
	__s64 align = pack_hdr_align(p, off);

	pack_fragment_t *patch = pack_orig_off_patch(p, off + align);
	if (!patch) return NULL;
	if (!patch->mm.t) mmsz_alloc(&patch->mm, patch->mm.sz);

	return (patch->mm.mem + (off - patch->off) + align);
}

static void patch_rela(pack_t *p, rela_t *rtab) {
	elf_t *elf = p->orig_elf;

	foreach_rela_t(rtab, r, Elf_Rela) {
		__u64 r_off = elf_vtof(elf, r->r_offset);
		__u64 A = pack_vtov(p, elf, r->r_addend);
		__u64 S = pack_vtov(p, elf, *(__u64*)(elf->map + r_off));

		__u64 *dst = pack_get_addr(p, r_off);
		r->r_offset += pack_hdr_align(p, r_off);

		__u64 v = 0;
		switch (ELF64_R_TYPE(r->r_info)) {
			case R_X86_64_RELATIVE:
				r->r_addend = A;
				break;
			case R_X86_64_GLOB_DAT:
			case R_X86_64_JUMP_SLOT: _assert(!!dst, "FUCK");
				*(__u64*)dst = S;
				break;
			case R_X86_64_64:		_assert(!!dst, "FUCK");
				*(__u64*)dst = S + A;
				break;
		}
	}
}

__u64 pack_hdr_align(pack_t *p, __u64 v) {
	__u64 ret = 0;
	foreach_hdr_patches(p, e) {
		if (e->orig_off < v) ret += e->dst_sz;
	}
	return ret;
}

__u64 rel_get_off(pack_t *pack, rel_patch_t *rel, __u64 off) {
	return rel_get_offset_t(pack, rel, 0, off);
}
__u64 pack_get_virt(pack_t *pack, elf_t *elf, __u64 s_virt, __u64 d_virt) {
	return pack_get_offset_t(pack, elf, 1, s_virt, d_virt);
}
__u64 pack_get_off(pack_t *pack, elf_t *elf, __u64 s_off, __u64 d_off) {
	return pack_get_offset_t(pack, elf, 2, s_off, d_off);
}

#define M_OFF	1
#define M_VIRT	2

static __u64 pack_get_offset_t(pack_t *pack, elf_t *elf, __u8 t, __u64 s_off, __u64 d_off) {
	// prf("%lx %lx %lx\n", d_off, (!!s ? d - s : d), s_off, d - s);
	// u64 s = pack_hdr_align(pack, (t==M_VIRT) ? elf_ftov(&pack->elf, s_off) : s_off);
	// u64 d = pack_hdr_align(pack, (t==M_VIRT) ? elf_ftov(&pack->elf, off) : off);
	for_each_rel(pack, elf, rel) {
		__u64 ret = rel_get_offset_t(pack, rel, t, d_off);
		if (ret != -1) {
			return ret;
		}
	}
	return -1;
}

__u64 pack_vtof(pack_t *p, elf_t *elf, __u64 v) { return pack_get_orig_off(p, elf, M_VIRT, v, M_OFF); }
__u64 pack_ftov(pack_t *p, elf_t *elf, __u64 v) { return pack_get_orig_off(p, elf, M_OFF, v, M_VIRT); }
__u64 pack_vtov(pack_t *p, elf_t *elf, __u64 v) { return pack_get_orig_off(p, elf, M_VIRT, v, M_VIRT); }
__u64 pack_ftof(pack_t *p, elf_t *elf, __u64 v) { return pack_get_orig_off(p, elf, M_OFF, v, M_OFF); }

static __u64 pack_get_orig_off(pack_t *p, elf_t *elf, __u64 t, __u64 v, __u8 out_t) {
	__u64 off = (t == M_VIRT) ? elf_vtof(elf, v) : v;
	__u64 pv = pack_get_off(p, p->orig_elf, 0, off);

	v = ((pv != -1) ? pv : off) + pack_hdr_align(p, off);
	return (out_t == M_VIRT) ? elf_ftov(&p->elf, v) : v;
}

static __u64 rel_get_offset_t(pack_t *pack, rel_patch_t *r, __u8 t, __u64 off) {
	for_each_patches(&r->out.patches, p) {
		if (_contain_(p->orig_off, p->orig_sz, off)) {
			__u64 ret = p->dst_off + (off - p->orig_off);
			ret += pin_align(pack, 0, ret);
			ret += rel_get_all_inner_off(pack, 0, ret);

			if (t == M_OFF)		return elf_ftov(&pack->elf, r->out.off + ret);
			if (t == M_VIRT)	return r->out.off + ret;
			return ret;
		}
	}
	return -1;
}


lle *pack_fix_u64(pack_t *p, rel_patch_t *rel, void *dst, __u64 off) {
	pack_fix_st st = {
		.rel = rel, .dst = dst, .off = off
	};
	lle *e = llist_add(&p->modif.fixes, F_LL_MALLOC, &st, sizeof(pack_fix_st));
	return (!e) ? NULL : e->dat;
}