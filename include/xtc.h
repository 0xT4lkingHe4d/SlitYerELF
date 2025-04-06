#include <linux/types.h>
#include "./utils.h"
#include "./pack.h"


#define XTC_NULL	0
#define XTC_PTR		1
#define XTC_IMM		2
#define XTC_REG		3

#define X_EXT_REXW		1
#define X_EXT_ADDR_OVRD	2
#define X_EXT_OPER_OVRD	4


#define X_B		1
#define X_W		2
#define X_DW	3
#define X_QW	4
#define X_XW	5
#define X_TB	6
#define X_FW	7
#define X_YW	8

#define X_TYPE(x, n)	(x & (3 << (6 - (n%4)*2))) >> 6
#define X_SZ(x, n)		(x & (0xf << (12 - ((n%4)*4)))) >> 12

#define X_FLAG(type, sz) ((type << 4) | sz)

// __u64 *x_t_c_contains(__u64 *map, __u64 limit, instr *in);
__u8 xtc_set_ext(__u8 sc[15], __u8 f);
void _xtc_build_instr(__u8 sc[15], __u16 f);
__s8 xtc_make_in(instr_dat_t *dst, __u8 flags[4], void *ptr, const instr *in);
__s16 xtc_chng_instr_sz(instr *in, __u8 oper[4]);
struct mmsz_tup *x_t_c_init();