#include <assert.h>
#include "../include/uapi.h"


#define GET_REX_BYTE(rex) ({										\
		0x40 | (!!rex.w<<3 | !!rex.r<<2 | !!rex.x<<1 | !!rex.b);	\
	})


int _strncmp(__u8 *a, __u8 *b, size_t sz) {
	if (!a||!b) return -0xbadf;
	foreach(i, sz) if (a[i]!=b[i]) return -1;
	return 0;
}

__u8 assemble(instr_dat_t *ret, __u8 ops[15]) {
	const instr *in = ret->instr;
	__u8 i=0;

	// Prefixes
	for_range(i, INST_MAX_PFX) {
		if (!ret->pfx[i]) break;
		ops[i]=ret->pfx[i];
	}
	// REX
	if (!!ret->rex_on) ops[i++]=GET_REX_BYTE(ret->rex);
	// Add mandatory prefix if not already there
	if (in->prefix && !list_contains(ret->pfx, INST_MAX_PFX, in->prefix)) {
		ops[i++]=in->prefix;
	}
	// instr opcodes
	if (in->two_byte) ops[i++] = 0x0f;
	ops[i++] = in->opcode1 +
			( !_strncmp(in->flds, "+r", 3) ? ret->reg_op : 0 );
	if (in->opcode2) ops[i++]=in->opcode2;
	
	// Modrm + SIB
	if (ret->modrm_on) {
		ops[i++] = ret->modrm;
		if (ret->sib_on) ops[i++]=ret->sib;
	}

	foreach(l, 4) {
		operand *p = &ret->oper[l];
		if (!!p->is_empty) continue;

		if (!!p->disp_sz) {
			__u8 disp_sz = p->disp_sz/8;
			assert(i+disp_sz <= 15);
			memcpy(&ops[i], p->disp, disp_sz);
			i += disp_sz;
		}
		if (!!p->is_imm) {
			__u8 sz = p->sz/8;
			assert(i+sz <= 15);
			memcpy(&ops[i], p->imm, sz);
			i += sz;
		}
	}
	assert(ret->in_sz == i);
	return i;
}


__u8 change_imm(instr_dat_t *ret, operand *p, __u64 imm) {
	__u64 t = p->x_origin.t;
	__u8 sz = p->sz/8;

	if (p->x_origin.t!=X_IMM) {
		DBGF("NOT IMMEDIATE [0x%lx %1$lu]\n", t);
		return -1;
	}
	if (sz > sizeof(__u64)) DIE("fuck");
	memmove(p->imm, (__u8*)&imm, sz);
	return sz;
}

__s8 change_disp(instr_dat_t *ret, operand *p, __u32 v) {
	if (!p->disp_sz) return -1;
	switch (p->disp_sz) {
	case 8:
		p->disp[0] = (__u8)v; break;
	case 32:
		*(__u32*)p->disp = v; break;
	default: return -1;
	}	
	return 0;
}

#define CHANGE_MODRM_REG(x, v)	(((__u8)x &~0x38) | ((v&7) << 3))
#define CHANGE_MODRM_RM(x, v) 	(((__u8)x&~7) | (v&7))

#define CHANGE_SIB_S(x, v) 	(((__u8)x&~0xc0) | ((v&3)<<6))
#define CHANGE_SIB_I(x, v)	CHANGE_MODRM_REG(x, v);
#define CHANGE_SIB_B(x, v)	CHANGE_MODRM_RM(x, v);

void change_regop(instr_dat_t *ret, operand *p, __u8 reg) {
	if (p->x_origin.t!=X_REG_OP) DIE("not regop");
	const instr *in = ret->instr;
	ret->reg_op = reg&7;
}

__s8 chng_sib(instr_dat_t *ret, __u8 v, __u16 x) {
	if (!ret->sib_on) return -1;
	switch (x) {
		case S:	ret->sib = CHANGE_SIB_S(ret->sib, v); break;
		case I:	ret->sib = CHANGE_SIB_I(ret->sib, v); break;
		case B:	ret->sib = CHANGE_SIB_B(ret->sib, v); break;
		default: return -1;
	}
	return 0;
}

__s8 change_modrm(instr_dat_t *ret, operand *p, __u8 reg) {
	const regs_tuple_t *tup = &p->x_origin;
	switch (tup->t) {
	case X_MODRM:
		{
			if (ret->sib_on || !!p->rip) return -1;
			ret->modrm = CHANGE_MODRM_RM(ret->modrm, reg);
		}
		break;
	case X_MODRM_FXD:
	case X_REG:
		{
			if (!ret->modrm_on) DIE("fuck");
			if (tup->f != reg_f && tup->f != rm_f) DIE(";....");

			ret->modrm =
				(tup->f==reg_f) ? CHANGE_MODRM_REG(ret->modrm, reg)
								: CHANGE_MODRM_RM(ret->modrm, reg);
		}
		break;
		default: return -1;
	}
	return 0;
}
