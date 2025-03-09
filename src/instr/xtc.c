#ifndef UAPI_
#define UAPI_
#include "../../disass/include/uapi.h"
#endif
#include "../../include/xtc.h"

#pragma pack(1)
typedef struct {
	struct {
		__u8 ext;
		__u8 t;		// 2bits each
		__u16 ops;	// 4bits each
	} x_info[4];
	__u16	t_ndx;
	__u8	c_pos;
} xtc_st;
#pragma pack()

static struct mmsz_tup mm = {0};

void _xtc_build_instr(__u8 sc[15], __u16 f) {
	_build_instr(&tabl[f & 0x3ff], sc + xtc_set_ext(sc, f >> 12));
}

__s8 xtc_make_in(instr_dat_t *dst, __u8 flags[4], void *ptr, const instr *in) {
	__s16 ret = xtc_chng_instr_sz(in, flags);
	if (ret == -1) return -1;
	
	_xtc_build_instr(ptr, ret);
	if (init_instr(ptr, dst) == -1) return -1;

	return 0;
}

__s16 xtc_chng_instr_sz(instr *in, __u8 oper[4]) {
	xtc_st *map = mm.mem, *e = NULL;
	if (!map) return -1;

	__s16 ndx = __get_tabl_ndx(in);
	for (xtc_st *i = map; i <= &map[mm.sz/sizeof(xtc_st)]; i++)
		if (i->t_ndx == ndx) { e = i; break; }

	if (!e) return -1;

	if (e->c_pos) while ((--e)->c_pos);

	for (__u8 i=0; !i || e->c_pos; e++, i=1) {
		for (__u8 l = 0; l < 4; l++) {
			for (__u8 j = 0; j < 4; j++) {

				__u8 f = ((X_TYPE(e->x_info[l].t, j) << 4) | X_SZ(e->x_info[l].ops, j));
				if (oper[j] && oper[j] != f)
					goto cont;
			}

			return (e->x_info[l].ext << 12) | e->t_ndx;	// l
			cont:
		}
	}
	return -1;
}

__u8 xtc_set_ext(__u8 sc[15], __u8 f) {
	__u8 i = 0;
	if (f&X_EXT_REXW)		sc[i++] = 0x48;
	if (f&X_EXT_ADDR_OVRD)	sc[i++] = 0x67;
	if (f&X_EXT_OPER_OVRD)	sc[i++] = 0x66;
	return i;
}


static __s8 x_t_c_insert(xtc_st *st, __u16 sub_ndx, instr *in) {
	if (!st) return -1;

	st->t_ndx = __get_tabl_ndx(in);
	st->c_pos = sub_ndx;

	__u8 ops_i = 0;
	__u8 x=0;
	for (__u8 l = 0; l < 0b111; l++) {
		__u8 pfx_i = 0, ext = 0;
		
		__u8 sc[15] = {0};
		if (l&1) {	sc[pfx_i++] = 0x48; ext |= X_EXT_REXW;		}
		if (l&2) {	sc[pfx_i++] = 0x67; ext |= X_EXT_ADDR_OVRD;	}
		if (l&4) {	sc[pfx_i++] = 0x66; ext |= X_EXT_OPER_OVRD;	}
		_build_instr(in, &sc[pfx_i]);

		instr_dat_t ins = {0};
		if (init_instr(sc, &ins) == -1) continue;
		if (ins.instr != in) continue;	// not the same instruction

		__u8 type = 0, i = 0;
		__u16 ops = 0;
		foreach_operand(p, (&ins)) {
			__u8 sz = 0;
			switch (p->sz) {
				case _BYTE_: 	sz = X_B; break;
				case _WORD_: 	sz = X_W; break;
				case _DWORD_: 	sz = X_DW; break;
				case _QWORD_: 	sz = X_QW; break;
				case _XMMWORD_: sz = X_XW; break;
				case _TBYTE_: 	sz = X_TB; break;
				case _FWORD_: 	sz = X_FW; break;
				case _YMMWORD_:	sz = X_YW; break;
			}
			ops |= ((sz&0xf) << (12 - i*4));

			__u8 t = 0;
			if (p->is_ptr)		t = XTC_PTR;
			else if (p->is_imm)	t = XTC_IMM;
			else if (p->reg)	t = XTC_REG;
			type |= ((t&0b11) << 6- i*2);
			i++;
		}

		__u8 is_unique = 1;
		for (__u8 j = 0; j < ops_i; j++) {
			if (st->x_info[j].t == type && st->x_info[j].ops == ops) {
				is_unique = 0; break;
			}
		}
		if (!is_unique) continue;
		// assert(ops_i < 4);
		st->x_info[ops_i++] = (typeof(st->x_info[ops_i])){
			.ext	= ext,
			.t		= type,
			.ops	= ops,
		};
	}

	return 0;
}

static __s8 _strcmp(__u8 *a, __u8 *b) {
	while (*a && *b) if (*a++ != *b++) return 0;
	return (*a == *b);
}

struct mmsz_tup *x_t_c_init() {
	if (mm.mem) return &mm;

	__u64 map_sz = MAX_TABLE_NDX * sizeof(xtc_st);
	xtc_st *map = map_anon(map_sz);
	__u64 map_ndx = 0;

	const instr *in = NULL, *_in = NULL;
	__u64 ndx = 0, i = 0;
	__u8 b_map[MAX_TABLE_NDX] = {0};
	for_each_instr(in) {
		if (!!b_map[i++]) continue;
		b_map[i-1] = 1;

		if (!in->mnemonic || in->opcode1==0x0F || (in->prefix && !in->opcode1))
			continue;

		__u64 j = 0, sub_ndx = 0;

		for_each_instr(_in) {
			if (!!b_map[j++]) continue;
			if (!_in->mnemonic || in->opcode1==0x0F || (!in->opcode1 && in->prefix)) continue;

			if (!_in->ops_count) {
				if (!in->ops_count) {
					if (!_strcmp(_in->mnemonic, in->mnemonic)) continue;
				} else {
					for (__u8 l = 0; l < in->ops_count; l++) {
						if (_strcmp(_in->mnemonic, in->ops[l].mnemonic)) goto insert;
					}
				}
			} else {
				for (__u8 l = 0; l < _in->ops_count; l++) {
					__u8 *str_a = _in->ops[l].mnemonic;

					if (!in->ops_count) {
						if (_strcmp(str_a, in->mnemonic)) goto insert;
					} else {
						for (__u8 e = 0; e < in->ops_count; e++) {
							if (_strcmp(str_a, in->ops[e].mnemonic)) goto insert;
						}
					}
				}

				continue;
			}

			insert:
			if (!sub_ndx) {
				_assert((x_t_c_insert(&map[map_ndx++], sub_ndx++, in) != -1), "FUCK");
			}

			b_map[j-1]=1;
			_assert((x_t_c_insert(&map[map_ndx++], sub_ndx++, _in) != -1), "FU@Ck");
		}
	}
	mm.mem	= (void*)map;
	mm.sz	= sizeof(xtc_st) * map_ndx;
	return &mm;
}
