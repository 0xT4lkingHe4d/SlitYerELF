#include "../../include/rel_instr.h"
#include "../../include/pack.h"
#include "../../include/llist.h"
#include "../../include/xtc.h"
#include "../../lib-x86-binary/x86.h"

__s8 get_rip_imm_oper_ndx(instr_dat_t *in);
static void rel_patch_imm_in(rel_t *r);
static rel_patch_t *get_orig_patch(rel_t *rel, __u64 v);
static __u64 rel_rip_ptr(instr_dat_t *in, rel_patch_t *p, __u64 off);
static rel_patch_t *pin_dst_patch(rel_t *rel, __u64 off);
static __s64 get_patch_align(llist_t *ll, __u64 src, __u64 dst);
__s64 pin_align(rel_t *rel, __u64 base, __u64 size);
__s64 patches_align(rel_t *rel, __u64 base, __u64 size);


void rel_init(rel_t *rel) {
	llist_new(&rel->patches, sizeof(rel_patch_t));
	// llist_new(&rel->ll_hijack, sizeof(rel_hijack_t));
}


rel_patch_t *_rel_ll_(llist_t *ll, __u16 patch_type, __u8 rel_type, elf_t *elf, void *ptr, __u64 src, __u64 dst, __u64 orig_size, __u64 dst_size) {
	Elf64_Phdr *p = NULL;
	if (!!elf) p = elf_off_to_phdr(elf, src);

	rel_patch_t ptx = {
		.type		= (patch_type << 4) | rel_type,
		.elf	= elf,
		.mm		= {
			.mem	= (!elf) ? ptr : elf->map + src,
			.size	= orig_size,
		},
		.orig_off	= src,
		.orig_size	= orig_size,
		.dst_off	= dst,
		.dst_size	= dst_size,
		.base_virt	= (!!elf) ? p->p_vaddr	: 0,
		.base_off	= (!!elf) ? p->p_offset	: 0,
	};


	lle *e = llist_add(ll, &ptx);
	return (!e) ? NULL : e->dat;
}

rel_patch_t *_rel_(rel_t *rel, __u8 t, elf_t *elf, void *ptr, __u64 src, __u64 dst, __u64 sz) {
	return _rel_ll_(&rel->patches, PATCH_REL, t, elf, ptr, src, dst, sz, sz);
}

rel_patch_t *rel_insn(rel_t *rel, elf_t *elf, void *ptr, __u64 src, __u64 dst, __u64 sz) {
	return _rel_(rel, REL_T_INSN, elf, ptr, src, dst, sz);
}

rel_patch_t *rel_buff(rel_t *rel, elf_t *elf, void *ptr, __u64 src, __u64 dst, __u64 sz) {
	return _rel_(rel, REL_T_DAT, elf, ptr, src, dst, sz);
}

mmsz_t *do_reloc(rel_t *rel) {
	rel_patch_imm_in(rel);
	
	__u64 max = 0;
	rel_each_patch(rel, p) {
		if (!max || p->dst_off + p->dst_size > max)
			max = p->dst_off + p->dst_size;
	}
	__u64 size = max + pin_align(rel, 0, max) + patches_align(rel, 0, max);
	mmsz_t *mm = new_mmsz(MEM_MMAP, size);

	rel_each_patch(rel, p) {
		switch (REL_TYPE_DAT(p->type)) {
			case REL_T_DAT:		rel_buf(rel, mm, p);	break;
			case REL_T_INSN:	rel_instr(rel, mm, p);	break;
		}
	}
	return mm;
}

void rel_buf(rel_t *rel, mmsz_t *mm, rel_patch_t *p) {
	__u64 off = p->dst_off - p->base_off;
	off += pin_align(rel, 0, off) + patches_align(rel, 0, off);
	memcpy(mm->mem + off, p->ptr, p->dst_size);
}

void rel_instr(rel_t *rel, mmsz_t *mm, rel_patch_t *p) {
	__u64 i = 0;
	foreach_instr_off(X86_64, in, i, p->ptr, p->dst_size) {
		// prf(PR_DBG "%lx %lx\n", rel->off_fn(rel->plugin, p, p->base_off), p->base_off);
		__u64 off = (p->dst_off + i);
		off += pin_align(rel, 0, off) + patches_align(rel, 0, off);
		__u8 *ptr = mm->mem + off;

		const operand *rip_oper = get_rip_imm_oper(&in);
		if (!rip_oper) {		// not RIP & IMM
			memcpy(ptr, p->ptr + i, in.in_sz);
			continue;
		}

		__u64 orig_imm	= rel_rip_ptr(&in, p, i);
		__u64 imm		= orig_imm + patches_align(rel, p->dst_off + i, in.in_sz);// - align; 
		
		rel_patch_t *patch = get_orig_patch(rel, imm); // + align
		switch (REL_TYPE_PATCH(p->type)) {
			case PATCH_REL:
			{
				if (!patch) {
					// Where is the pointing IMM phdr now
					imm = rel->hook_fn(rel->plugin, rel, p, orig_imm);
					ptr += stick_in_instr(&in, ptr, (imm - rel->off_fn(rel->plugin, p, p->base_off)), off, CHNG_REL);
					break;
				}

				// Jumps in the Patched area
				imm = rel_get_off(rel, orig_imm);
				rel_patch_t *p_sc = pin_dst_patch(rel, p->dst_off + i);
				if (!p_sc) {
					ptr += stick_in_instr(&in, ptr, imm, off, CHNG_REL);
					break;
				}

				instr_dat_t sc_in = {0};
				init_instr(X86_64, &sc_in, rel->pin.sc.mem + p_sc->off);
				ptr += stick_in_instr(&sc_in, ptr, imm, off, CHNG_REL);
			}
			break;
			case PATCH_ADD:
			{
				__s64 align = pin_align(rel, p->dst_off + i, orig_imm);
				ptr += stick_in_instr(&in, ptr, orig_imm, align, CHNG_FXD);
			}
			break;
		}
	}
	pr(PR_INFO "DONE");
}

__u64 rel_get_off(rel_t *rel, __u64 imm) {
	rel_each_patch(rel, p) {
		if (_contain_(p->orig_off, p->orig_size, imm)) {
			__u64 v = p->dst_off + (imm - p->orig_off);
			v += pin_align(rel, 0, v) + patches_align(rel, 0, v);
			return v;
		}
	}
	return -1;
}

static rel_patch_t *get_orig_patch(rel_t *rel, __u64 v) {
	rel_each_patch(rel, p)
		if (p->orig_off != -1)
			if (_contain_(p->orig_off, p->orig_size+1, v))
				return p;

	return NULL;
}


rel_patch_t *_rel_cpy_(llist_t *ll, __u8 t, __u32 dst, __u64 dst_size, __u64 orig_size, __u64 off) {
	rel_patch_t *p = _rel_ll_(ll, t, REL_T_INSN, NULL, NULL, 0, dst, orig_size, dst_size);
	p->off	= off;
	p->size	= dst_size;
	return p;
}

static void rel_patch_imm_in(rel_t *r) {
	r->pin.sc.t		= MEM_MMAP;
	r->pin.sc.mem	= map_anon(0x1000);
	r->pin.sc.size	= 0x1000;
	llist_new(&r->pin.ll, sizeof(rel_patch_t));
	mmsz_t *const sc = &r->pin.sc;

	rel_each_patch(r, p) {
		__u64 i = 0;
		foreach_instr_off(X86_64, in, i, p->ptr, p->dst_size) {
			instr_dat_t lin = {0};
			__u8 *ptr = sc->mem + sc->off;

			__s8 ndx = get_rip_imm_oper_ndx(&in);
			if (ndx == -1) continue;
			const operand *op = &in.oper[ndx];
			
			if (get_oper_sz(&in, op) < _DWORD_) {
				__u8 flags[4] = {0};
				flags[ndx] = X_FLAG(XTC_IMM, X_DW);

				if (xtc_make_in(&lin, flags, ptr, in.instr) == -1) DIE("FU3CK!");
				if (sc->off + MAX_INSTR_SZ > sc->size) DIE("FU8CK!");

				_rel_cpy_(&r->pin.ll, PATCH_REPLACE, p->dst_off + i, lin.in_sz, in.in_sz, sc->off);
				sc->off += lin.in_sz;

				if (sc->off + 0x100 > sc->size) {
					mmsz_resz(sc, 0x1000);
				}
			}
		}
	}
}


static __u64 rel_rip_ptr(instr_dat_t *in, rel_patch_t *p, __u64 off) {
	__u64 imm = 0, in_off = p->orig_off;
	if (p->type == PATCH_ADD) in_off = p->dst_off;
	get_rip_ptr_addr(in, in_off + off, &imm);
	return imm;
}

static rel_patch_t *pin_dst_patch(rel_t *rel, __u64 off) {
	llist_each_dat(&rel->pin.ll, rel_patch_t, p)
		if (off == p->dst_off) return p;
	return NULL;
}

__s64 pin_align(rel_t *rel, __u64 base, __u64 size) {
	__u64 x =  get_patch_align(&rel->pin.ll, base, size);
	// prf("(%lx, %lx) - %lx\n", base, size, x);
	return x;
}

__s64 patches_align(rel_t *rel, __u64 base, __u64 size) {
	return get_patch_align(&rel->patches, base, size);
}

// Multiple elfs
static __s64 get_patch_align(llist_t *ll, __u64 src, __u64 dst) {
	__u64 base = ((src > dst) ? dst : src);
	__u64 size = ((src > dst) ? src : dst) - base;

	__s64 align = 0;
	llist_each_dat(ll, rel_patch_t, p) {
		// prf("%lx;%lx ; %lx\n", base, size, p->dst_off);
		if (_contain_(base, size, p->dst_off))
			switch (REL_TYPE_PATCH(p->type)) {
				case PATCH_REPLACE:
					align += (p->dst_size - p->orig_size);
					break;
				case PATCH_ADD:
					align += p->dst_size;
					break;
			}
	}

	return ((src > dst) ? -1 : 1) * align;
}
