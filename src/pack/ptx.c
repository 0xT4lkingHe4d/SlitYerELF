#include <linux/types.h>
#include <fcntl.h>
#include "../../include/pack.h"
#include "../../include/llist.h"

void ptx_add_fill(pack_t *p, elf_t *elf, __u64 off, __u64 size);
__u64 ptx_align(pack_t *p, __u64 off, __u64 sz, __u8 v);
void elf_align(pack_t *p, __u64 off, __s64 sz);
void pack_get_patch(pack_t *p, ptx_patch_tup *ret, __u64 off);

void ptx_init(ptx_engine_t *ptx) {
	llist_new(&ptx->headers, sizeof(ptx_header_t));
	llist_new(&ptx->fills, sizeof(ptx_fill_t));
	llist_new(&ptx->patches, sizeof(ptx_patch_t));
}

void ptx_add_fill(pack_t *p, elf_t *elf, __u64 off, __u64 size) {
	ptx_fill_t f = {
		.src = {
			.elf=elf, .off=off, .size=size
		},
		.mm = {
			.t		= MEM_HEAP,
			.mem	= xmalloc(size),
			.size	= size,
		},
		.off	= off,
	};
	memcpy(f.mm.mem, elf->map + f.off, f.mm.size);
	llist_add(&p->ptx.fills, &f);
}

/**
 * @ptx_fill
 * ~ Stick in fill patches between headers
**/
void ptx_fill(pack_t *p, elf_t *elf, __u64 s_off, __u64 s_sz) {
	__u64 i = 0;
	ptx_each_header(&p->ptx, hdr)
		if (_contains_(s_off, s_sz, hdr->off, hdr->mm.size)) {
			// Before first header
			if (!i++ && hdr->off > s_off && hdr->off - s_off > 0)
				ptx_add_fill(p, elf, s_off, hdr->off - s_off);

			ptx_header_t *next = ptx_header_next(&p->ptx, hdr);
			__u64 off = hdr->off + hdr->mm.size;

			if (!!next) {
				// Between this header and the next one
				if (!!(next->off - off))
					ptx_add_fill(p, elf, off, (next->off - off));
			} else if (hdr->off + hdr->mm.size < s_sz) {
				if (!!(s_sz - off))
					ptx_add_fill(p, elf, off, (s_sz - off));
			}
		}
}

/**
 * @pack_split_chunk
 * ~ split a header or fill at off
**/
void pack_split_chunk(pack_t *pack, __u64 off) {
	llist_t *ll = NULL;
	lle *e = NULL;
	ptx_each_any_ll(pack, ll, t, e) {
		ptx_fill_t *f = e->dat;
		if (_contain_(f->off, f->mm.size, off)) {
			if (f->src.size == off || off - f->off <= 0) break;
			ptx_header_t a = {
				.src	= { .off=f->src.off, .size=off - f->off },
				.off	= f->off,
			},
			b = {
				.src	= { .off=f->src.off + (off - f->off), .size=f->src.size - (off - f->off) },
				.off	= off,
			};
			if (!!f->mm.t) {	// If patch has allocated memory - 
				make_mmsz(&a.mm, MEM_ANY, a.src.size);
				make_mmsz(&b.mm, MEM_ANY, b.src.size);
				memcpy(a.mm.mem, f->mm.mem, a.src.size);
				memcpy(b.mm.mem, f->mm.mem + (off - f->off), b.src.size);
				mmsz_free(&f->mm);
			}

			lle *prev = e->prev, *next = e->next;
			llist_free_elem(ll, e);

			lle *a_elem = llist_twine(ll, prev, next, &a);
			lle *b_elem = llist_twine(ll, a_elem, next, &b);
			return;
		}
	}
}

ptx_header_t *ptx_add_header(ptx_engine_t *ptx, __u8 t, elf_t *elf, void *ptr, __u64 count, __u64 hdr_sz) {
	void *mem = xmalloc(count * hdr_sz);
	memcpy(mem, ptr, count * hdr_sz);
	lle *e = llist_add(&ptx->headers, &(ptx_header_t){
		.type	= t,
		.src = {
			.elf 	= elf,
			.off	= ptr - elf->map,
			.size	= count * hdr_sz,
		},
		.mm	= {
			.t		= MEM_HEAP,
			.mem	= mem,
			.size	= count * hdr_sz,
		},
		.off	= ptr - elf->map,

		.count	= count,
		.entry_size = hdr_sz,
	});

	return (!!e) ? e->dat : NULL;
}

ptx_header_t *ptx_header_next(ptx_engine_t *ptx, ptx_header_t *min) {
	ptx_header_t *ret = NULL;
	llist_each_dat(&ptx->headers, ptx_header_t, e) {
		if ((!ret || ret->off > e->off) && (!min || e->off > min->off))
			ret = e;
	}
	return ret;
}

void ptx_shift(pack_t *pack, __u64 off, __s64 size) {
	llist_add(&pack->ptx.patches, &(ptx_patch_t){ .off=off, .mm={.size=size} });

	ptx_each_any(pack, f) {
		if (f->off > off) f->off += size;
		else if (_contain_(f->off, f->src.size, off)) {
			pack_split_chunk(pack, off); // next iter shall be the other half of this patch
		}
	}

	elf_align(pack, off, size);
}

void elf_align(pack_t *pack, __u64 off, __s64 sz) {
	patch_each(pack, EHDR, Elf64_Ehdr, ehdr) {
		if (ehdr->e_shoff >= off) ehdr->e_shoff += sz;
		if (ehdr->e_phoff >= off) ehdr->e_phoff += sz;
	}

	patch_each(pack, PHDR, Elf64_Phdr, p)
		if (_contain_(p->p_offset, p->p_filesz, off)) {
			p->p_memsz	+= sz;
			p->p_filesz += sz;
		} else if (p->p_offset >= off) {
			p->p_offset	+= sz;
			p->p_paddr	+= sz;
			p->p_vaddr	+= sz;
		}

	patch_each(pack, SHDR, Elf64_Shdr, sec)
		if (_contain_(sec->sh_offset, sec->sh_size, off)) {
			sec->sh_size	+= sz;
		} else if (sec->sh_offset >= off) {
			sec->sh_addr	+= sz;
			sec->sh_offset	+= sz;
		}

	patch_each(pack, SYM, Elf64_Sym, sym)
		if (sym->st_value >= pack_ftov(pack, off))
			sym->st_value += ptx_align(pack, off, sz, sym->st_value);
}

void pack_get_patch(pack_t *p, ptx_patch_tup *ret, __u64 off) {
	llist_t *ll	= NULL;
	lle *e		= NULL;
	ptx_each_any_ll(p, ll, t, e) {
		ptx_patch_t *px = e->dat;
		if (_contain_(px->off, px->mm.size, off)) {
			ret->type = t;
			ret->list_elem = e;
			return;
		}
	}
}

ptx_header_t *ptx_type(ptx_engine_t *ptx, __u16 t) {	
	ptx_each_header(ptx, e)
		if (e->type == t) return e;
	return NULL;
}

__u64 ptx_align(pack_t *pack, __u64 off, __u64 sz, __u8 v) {
	patch_each(pack, PHDR, Elf64_Phdr, p) {
		__u64 align = ALIGN(sz, p->p_align);
		__u64 r = 0, size = 0;

		if (_contain_(p->p_offset-align, p->p_filesz, off)) {
			size += align;
		} else if (p->p_offset-align > off) {
			r += align;
		}

		if (_contain_(p->p_offset + off, p->p_filesz + size, v+align))
			return r;
	}
	return 0;
}

__u64 pack_get_addr(pack_t *pack, elf_t *elf, __u8 st, __u64 v) {
	__u64 off = (st == ELF_VIRT) ? elf_vtof(elf, v) : v;
	__u64 virt = (st == ELF_OFF) ? elf_ftov(elf, v) : v;

	llist_each_dat(&pack->ll_rel, ptx_rel_t, e) {
		rel_each_patch(&e->rel, p)
			if (_contain_(p->orig_off, p->orig_size, off)) {
				__u64 ret = p->dst_off + (off - p->orig_off);

				ret += pin_align(&e->rel, 0, ret) + patches_align(&e->rel, 0, ret);
				return ret + pack_base_ftov(pack, elf, p->base_off);
			}
	}
	return pack_base_ftov(pack, elf, off);
}

void patch_elf(pack_t *p) {
	Elf64_Ehdr *ehdr = (ptx_type(&p->ptx, ELF_T_EHDR))->mm.mem;
	ehdr->e_entry = pack_get_addr(p, p->out_elf, ELF_VIRT, ehdr->e_entry);
	prf("The fucking entry 0x%lx\n", ehdr->e_entry);

	/* Patch Dynamic Headers */
	patch_each_x(p, DYN, Elf64_Dyn, dyn, hdr)
		if (elf_dtag_is_addr(dyn->d_tag))
			dyn->d_un.d_ptr = pack_get_addr(p, hdr->src.elf, ELF_VIRT, dyn->d_un.d_ptr);
		
	/* Patch Rela */
	patch_each_x(p, RELA, Elf64_Rela, r, hdr) {
		elf_t *elf = hdr->src.elf;
		__u64 orig_off	= elf_vtof(elf, r->r_offset);
		__u64 r_virt	= pack_base_ftov(p, elf, orig_off);
		__u64 r_off		= pack_base_ftof(p, elf, orig_off);

		__u64 rA = pack_get_addr(p, elf, ELF_VIRT, r->r_addend);
		__u64 rS = pack_get_addr(p, elf, ELF_VIRT, *(__u64*)(elf->map + orig_off));
		void *dst = NULL;

		r->r_offset = r_virt;

		ptx_patch_tup ptup = {0};
		pack_get_patch(p, &ptup, r_off);
		ptx_patch_t *px = ptup.list_elem->dat;
		if (!!px) {
			if (r_off - px->off > px->mm.size) goto fail;
			dst = px->mm.mem + (r_off - px->off);
		}

		switch (ELF64_R_TYPE(r->r_info)) {
			case R_X86_64_RELATIVE:
				r->r_addend = rA;
				break;
			case R_X86_64_GLOB_DAT:
			case R_X86_64_JUMP_SLOT: if(!dst) goto fail;
				*(__u64*)dst = rS;
				break;
			case R_X86_64_64:		if (!dst) goto fail;
				*(__u64*)dst = rS + rA;
				break;
			case R_X86_64_COPY:
				r->r_offset = r_off;
		}
	}
	return;
	fail:
		xprf(ERR, "%s - fuck!\n", __FUNCTION__);
}

/**
 * Rebuild the ELF */
__s8 make_elf(pack_t *p, __u8 *output) {
	if (file_exists(output)) {
		xprf(ERR, "output file exitsts - " BGRN"%s\n"CRST, output);
		return -1;
	}
	int fd = open(output, O_CREAT|O_RDWR, 0755);
	if (fd == -1) return -1;
	patch_elf(p);

	ptx_each_any(p, e) {
		_wr(fd, e->off, e->mm.mem, e->mm.size);
	}

	close(fd);
	return 0;
}
