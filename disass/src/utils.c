#include <endian.h>
#include "../include/disass.h"

const __u8 *get_instr_name(instr_dat_t *in) {
	return (!in->op_ndx) ? in->instr->mnemonic : in->instr->ops[in->op_ndx].mnemonic;
}

void print_instr(instr *e) {
	if (e == NULL) {
		DIE("NULL arg");
		return;
	}
	printf("Pf[%02x]\t0f[%s]\topcode1[%02x]\topcode2[%02x]",
			e->prefix, (e->two_byte) ? "~+~" : "---",
			e->opcode1, e->opcode2);

	if (e->ops_count != 0) {
		for (int i=0; i<e->ops_count; i++) {
			printf("\t[%i] '%s';%s", i, e->ops[i].mnemonic, (i == e->ops_count-1) ? "\n" : "\t");
		}
	} else {
		printf("\t'%s'", e->mnemonic);
	}
	if (e->reg_op) printf("\tregop[%02x]", e->reg_op);
	puts("");
}

char *word_sz_to_str(__u8 sz) {
	switch (sz) {
		case _BYTE_: 	return "BYTE";
		case _WORD_: 	return "WORD";
		case _DWORD_: 	return "DWORD";
		case _QWORD_: 	return "QWORD";
		case _XMMWORD_: return "XMM";
		case _TBYTE_: 	return "TBYTE";
		case _FWORD_: 	return "FWORD";
		default: 		return "N/A";
	}
}

char *seg_reg_str(__u8 v) {
	switch (v) {
		case SEG_CS: return "cs";
		case SEG_SS: return "ss";
		case SEG_DS: return "ds";
		case SEG_ES: return "es";
		case SEG_FS: return "fs";
		case SEG_GS: return "gs";
	}
	return "[no segreg]";
}

__u64 _pow(__u8 a, __u8 b) {
	__u64 x=1;
	for (__u64 i=0;i<b;i++) x*=a;
	return x-1;
}


// #define _signed_limit(n)	 	(_pow(2, n)/2)
// #define _signed(v, len) 	( ((__u64)v > (__u64)_pow(2, len)/2) ? (~v)+1 : v )


void pr_hex(__u8 *addr, __u8 len, long e) {
	__u8 i = 0;
	while(i < len) {
		DBGF("%02x ", (e==BIG_ENDIAN) ? addr[i++] : addr[(len-1)-(i++)]);
	}
}

static void pr_hex_v(__u64 v, __u8 len) {
	DBGF(" %c", (v > _signed_limit(len))?'-':'+');
	switch (len) {
		case 8:  DBGF(" 0x%x ", (__u8) _signed(v, len)); break;
		case 16: DBGF(" 0x%x ", (__u16)_signed(v, len)); break;
		case 32: DBGF(" 0x%x ", (__u32)_signed(v, len)); break;
		case 64: DBGF(" 0x%x ", (__u64)_signed(v, len)); break;
	}
}

void pr_hex_le(__u8 *addr, __u8 len) {
	__u64 v=0;
	switch (len) {
	case 8:		v = (__u64)addr[0]; 		break;
	case 16:	v = le16toh(*(__u16*)addr);	break;
	case 32:	v = le32toh(*(__u32*)addr);	break;
	case 64:	v = le64toh(*(__u64*)addr);	break;
	default:
		DBGF("%i--\n", len);
		DIE("FIUCK ");
	}
	pr_hex_v(v, len);
}


static __u8 get_hex_len(size_t x) {
	__u8 i=0;
	while (!!x) {x>>=4; i++;}
	return i;
}



void hexdump(void *src, size_t len) {
	__u8 *addr = src;
	printf(" \e[1m%p\e[m", addr);
	for (size_t i=0;i < len; addr++,i++) {
		if ((i)%4==0)	printf("| ");
		printf("%02x ", *addr);

		if (((i+1)%16==0 && !!i) || !(i+1<len)) {
			printf("\t | ");
			__u8 limit = ((!(i+1<len))?(i)%15:15);
			for (int l=0; l<=limit;l++) {
				__u8 ch = *(addr-limit+l);
				if (isprint(ch)) printf("\e[1m%c\e[m", ch);
				else printf(".");
			}
			if ((i+1<len))
				printf("\n \e[1m%p\e[m", addr+1);
		}
	}
	puts("");
}



__u8 *get_rip_str(__u8 sz) {
	return (sz==64) ? "RIP" : (sz==32) ? "EIP" : "FUCK !";
}

void pr_in_str(instr_dat_t *ret) {
	__u8 addr_sz=get_addr_size(ret);
	foreach(i, 4) {
		operand *p = &ret->oper[i];
		DBGF("[%i] %c \t ", i, (!p->is_empty) ? 'Y' : '-');

		if (!!p->seg_reg) DBGF("%s:", seg_reg_str(p->seg_reg));
		if (!!p->is_imm) {
			if (!!p->rip) {
				DBGF("[ %s ", get_rip_str(p->rip));
				pr_hex_le(p->imm, p->sz);
				DBG("]");
			} else {
				DBGF("IS imm  -\t [%i-bit]\tval - [", p->sz);
				pr_hex(p->imm, p->sz/8, LITTLE_ENDIAN);
				DBG("]");
			}
		} else if (!!p->reg && !p->disp_sz) {
			__u32 reg = p->reg;
			if (IS_ANY_REGS(reg)) {
				// elsewhere
				DBG("REG any -\t %s", (__u8*)gen_reg_scale_by_val(reg, get_oper_size(ret)));
			} else {
				__u8 *nm = (__u8*)get_reg_name(reg);
				if (p->is_ptr) {
					DBGF("REG     -\t %s ptr ", word_sz_to_str(p->sz));
					DBGF("[%s]\n", nm);
				} else {
					DBG("REG     -\t %s", nm);
				}
			}
		} else if (!!p->is_ptr) {
			printf("IS ptr  -\t ");
			if (!!p->sz) {
				DBGF("%s ptr ", word_sz_to_str(p->sz));
			}
			if (p->sib.on) {
				DBGF("[ %s + %s*%i ",
					reg_4bits_name(p->sib.b_reg, addr_sz),
					(!p->sib.i_reg) ? "[NO]" : (char*)reg_4bits_name(p->sib.i_reg, addr_sz),
					p->sib.s);
				if (p->disp_sz) pr_hex_le(p->disp, p->disp_sz);
				DBG(" ]");
			} else if (ret->modrm_on && !!p->disp_sz) {
				if (!!p->rip) {
					DBGF("[ %s ", get_rip_str(p->rip));
				} else {
					DBGF("[ %s ", (__u8*)get_reg_name(p->reg));
				}
				pr_hex_le(p->disp, p->disp_sz);
				DBG(" ]");
			}
		} else {
			puts("____________________");
		}

	}
	DBGF("op_ndx     %u\n", ret->op_ndx);
	DBGF("instr size %i\n", ret->in_sz);
	DBGF("++ REX.[%c%c%c%c]\n",
		(ret->rex.w)? 'W' : '.',
		(ret->rex.r)? 'R' : '.',
		(ret->rex.x)? 'X' : '.',
		(ret->rex.b)? 'B' : '.');
}


