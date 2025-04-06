#define INSTR_TABLE_H
#include "../include/def.h"
#undef INSTR_TABLE_H

__attribute__((section(".tabl_sec"), aligned(0x1000))) const instr tabl[941] = (const instr[941]){
	{ .op1=0x00, .reg_op=0xf, .x=X_LOCK, .mnemo="ADD", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_G | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add */
	{ .op1=0x01, .reg_op=0xf, .x=X_LOCK, .mnemo="ADD", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add */
	{ .op1=0x02, .reg_op=0xf, .mnemo="ADD", .ops={ { F_ADDR_G | F_OPERAND_B, F_ADDR_E | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add */
	{ .op1=0x03, .reg_op=0xf, .mnemo="ADD", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add */
	{ .op1=0x04, .mnemo="ADD", .ops={ { REG_8_AL, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add */
	{ .op1=0x05, .mnemo="ADD", .ops={ { REG_ANY_RAX, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add */
	{ .op1=0x06, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x07, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x08, .reg_op=0xf, .x=X_LOCK, .mnemo="OR", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_G | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Inclusive OR */
	{ .op1=0x09, .reg_op=0xf, .x=X_LOCK, .mnemo="OR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Inclusive OR */
	{ .op1=0x0A, .reg_op=0xf, .mnemo="OR", .ops={ { F_ADDR_G | F_OPERAND_B, F_ADDR_E | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Inclusive OR */
	{ .op1=0x0B, .reg_op=0xf, .mnemo="OR", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Inclusive OR */
	{ .op1=0x0C, .mnemo="OR", .ops={ { REG_8_AL, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Inclusive OR */
	{ .op1=0x0D, .mnemo="OR", .ops={ { REG_ANY_RAX, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Inclusive OR */
	{ .op1=0x0E, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x0F, },		/* DESCRIPTION=0f prefix */
	{ .op1=0x10, .reg_op=0xf, .x=X_LOCK, .mnemo="ADC", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_G | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add with Carry */
	{ .op1=0x11, .reg_op=0xf, .x=X_LOCK, .mnemo="ADC", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add with Carry */
	{ .op1=0x12, .reg_op=0xf, .mnemo="ADC", .ops={ { F_ADDR_G | F_OPERAND_B, F_ADDR_E | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add with Carry */
	{ .op1=0x13, .reg_op=0xf, .mnemo="ADC", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add with Carry */
	{ .op1=0x14, .mnemo="ADC", .ops={ { REG_8_AL, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add with Carry */
	{ .op1=0x15, .mnemo="ADC", .ops={ { REG_ANY_RAX, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add with Carry */
	{ .op1=0x16, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x17, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x18, .reg_op=0xf, .x=X_LOCK, .mnemo="SBB", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_G | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Integer Subtraction with Borrow */
	{ .op1=0x19, .reg_op=0xf, .x=X_LOCK, .mnemo="SBB", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Integer Subtraction with Borrow */
	{ .op1=0x1A, .reg_op=0xf, .mnemo="SBB", .ops={ { F_ADDR_G | F_OPERAND_B, F_ADDR_E | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Integer Subtraction with Borrow */
	{ .op1=0x1B, .reg_op=0xf, .mnemo="SBB", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Integer Subtraction with Borrow */
	{ .op1=0x1C, .mnemo="SBB", .ops={ { REG_8_AL, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Integer Subtraction with Borrow */
	{ .op1=0x1D, .mnemo="SBB", .ops={ { REG_ANY_RAX, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Integer Subtraction with Borrow */
	{ .op1=0x1E, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x1F, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x20, .reg_op=0xf, .x=X_LOCK, .mnemo="AND", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_G | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical AND */
	{ .op1=0x21, .reg_op=0xf, .x=X_LOCK, .mnemo="AND", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical AND */
	{ .op1=0x22, .reg_op=0xf, .mnemo="AND", .ops={ { F_ADDR_G | F_OPERAND_B, F_ADDR_E | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical AND */
	{ .op1=0x23, .reg_op=0xf, .mnemo="AND", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical AND */
	{ .op1=0x24, .mnemo="AND", .ops={ { REG_8_AL, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical AND */
	{ .op1=0x25, .mnemo="AND", .ops={ { REG_ANY_RAX, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical AND */
	{ .pfx=0x26, },		/* DESCRIPTION=Null Prefix in 64-bit Mode */
	{ .op1=0x27, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x28, .reg_op=0xf, .x=X_LOCK, .mnemo="SUB", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_G | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Subtract */
	{ .op1=0x29, .reg_op=0xf, .x=X_LOCK, .mnemo="SUB", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Subtract */
	{ .op1=0x2A, .reg_op=0xf, .mnemo="SUB", .ops={ { F_ADDR_G | F_OPERAND_B, F_ADDR_E | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Subtract */
	{ .op1=0x2B, .reg_op=0xf, .mnemo="SUB", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Subtract */
	{ .op1=0x2C, .mnemo="SUB", .ops={ { REG_8_AL, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Subtract */
	{ .op1=0x2D, .mnemo="SUB", .ops={ { REG_ANY_RAX, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Subtract */
	{ .pfx=0x2E, },		/* DESCRIPTION=Null Prefix in 64-bit Mode */
	{ .op1=0x2F, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x30, .reg_op=0xf, .x=X_LOCK, .mnemo="XOR", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_G | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Exclusive OR */
	{ .op1=0x31, .reg_op=0xf, .x=X_LOCK, .mnemo="XOR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Exclusive OR */
	{ .op1=0x32, .reg_op=0xf, .mnemo="XOR", .ops={ { F_ADDR_G | F_OPERAND_B, F_ADDR_E | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Exclusive OR */
	{ .op1=0x33, .reg_op=0xf, .mnemo="XOR", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Exclusive OR */
	{ .op1=0x34, .mnemo="XOR", .ops={ { REG_8_AL, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Exclusive OR */
	{ .op1=0x35, .mnemo="XOR", .ops={ { REG_ANY_RAX, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Exclusive OR */
	{ .pfx=0x36, },		/* DESCRIPTION=Null Prefix in 64-bit Mode */
	{ .op1=0x37, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x38, .reg_op=0xf, .mnemo="CMP", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_G | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Compare Two Operands */
	{ .op1=0x39, .reg_op=0xf, .mnemo="CMP", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Compare Two Operands */
	{ .op1=0x3A, .reg_op=0xf, .mnemo="CMP", .ops={ { F_ADDR_G | F_OPERAND_B, F_ADDR_E | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Compare Two Operands */
	{ .op1=0x3B, .reg_op=0xf, .mnemo="CMP", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Compare Two Operands */
	{ .op1=0x3C, .mnemo="CMP", .ops={ { REG_8_AL, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Compare Two Operands */
	{ .op1=0x3D, .mnemo="CMP", .ops={ { REG_ANY_RAX, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Compare Two Operands */
	{ .pfx=0x3E, },		/* DESCRIPTION=Null Prefix in 64-bit Mode */
	{ .op1=0x3F, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .pfx=0x40, .mnemo="REX", },		/* DESCRIPTION=Access to new 8-bit registers */
	{ .pfx=0x41, .mnemo="REX.B", },		/* DESCRIPTION=Extension of r/m field, base field, or opcode reg field */
	{ .pfx=0x42, .mnemo="REX.X", },		/* DESCRIPTION=Extension of SIB index field */
	{ .pfx=0x43, .mnemo="REX.XB", },	/* DESCRIPTION=REX.X and REX.B combination */
	{ .pfx=0x44, .mnemo="REX.R", },		/* DESCRIPTION=Extension of ModR/M reg field */
	{ .pfx=0x45, .mnemo="REX.RB", },	/* DESCRIPTION=REX.R and REX.B combination */
	{ .pfx=0x46, .mnemo="REX.RX", },	/* DESCRIPTION=REX.R and REX.X combination */
	{ .pfx=0x47, .mnemo="REX.RXB", },	/* DESCRIPTION=REX.R, REX.X and REX.B combination */
	{ .pfx=0x48, .mnemo="REX.W", },		/* DESCRIPTION=64 Bit Operand Size */
	{ .pfx=0x49, .mnemo="REX.WB", },	/* DESCRIPTION=REX.W and REX.B combination */
	{ .pfx=0x4A, .mnemo="REX.WX", },	/* DESCRIPTION=REX.W and REX.X combination */
	{ .pfx=0x4B, .mnemo="REX.WXB", },	/* DESCRIPTION=REX.W, REX.X and REX.B combination */
	{ .pfx=0x4C, .mnemo="REX.WR", },	/* DESCRIPTION=REX.W and REX.R combination */
	{ .pfx=0x4D, .mnemo="REX.WRB", },	/* DESCRIPTION=REX.W, REX.R and REX.B combination */
	{ .pfx=0x4E, .mnemo="REX.WRX", },	/* DESCRIPTION=REX.W, REX.R and REX.X combination */
	{ .pfx=0x4F, .mnemo="REX.WRXB", },	/* DESCRIPTION=REX.W, REX.R, REX.X and REX.B combination */
	{ .op1=0x50, .flds=1, .mnemo="PUSH", .ops={ { F_ADDR_Z | F_OPERAND_VQ, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Push Word, Doubleword or Quadword Onto the Stack */
	{ .op1=0x58, .flds=1, .mnemo="POP", .ops={ { F_ADDR_Z | F_OPERAND_VQ, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Pop a Value from the Stack */
	{ .op1=0x60, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x61, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x62, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x63, .reg_op=0xf, .mnemo="MOVSXD", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_E | F_OPERAND_D, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, CONVER, 0), },		/* DESCRIPTION=Move with Sign-Extension */
	{ .pfx=0x64, .mnemo="FS", },		/* DESCRIPTION=FS segment override prefix */
	{ .pfx=0x65, .mnemo="GS", },		/* DESCRIPTION=GS segment override prefix */
	{ .pfx=0x66, },		/* DESCRIPTION=Operand-size override prefix */
	{ .pfx=0x66, },		/* DESCRIPTION=Precision-size override prefix */
	{ .pfx=0x67, },		/* DESCRIPTION=Address-size override prefix */
	{ .op1=0x68, .mnemo="PUSH", .ops={ { F_ADDR_I | F_OPERAND_VS, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Push Word, Doubleword or Quadword Onto the Stack */
	{ .op1=0x69, .reg_op=0xf, .mnemo="IMUL", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Signed Multiply */
	{ .op1=0x6A, .mnemo="PUSH", .ops={ { F_ADDR_I | F_OPERAND_BSS, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Push Word, Doubleword or Quadword Onto the Stack */
	{ .op1=0x6B, .reg_op=0xf, .mnemo="IMUL", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_BS, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Signed Multiply */
	{ .op1=0x6C, .rlvl=RLVL1, .ops=(instr_fop[2]){.mnemo="INS", { F_ADDR_Y | F_OPERAND_B, REG_16_DX, 0, 0 }, .mnemo="INSB", { F_ADDR_Y | F_OPERAND_B, REG_16_DX, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Input from Port to String */
	{ .op1=0x6D, .rlvl=RLVL1, .ops=(instr_fop[2]){.mnemo="INS", { F_ADDR_Y | F_OPERAND_WO, REG_16_DX, 0, 0 }, .mnemo="INSW", { F_ADDR_Y | F_OPERAND_WO, REG_16_DX, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Input from Port to String */
	{ .op1=0x6D, .rlvl=RLVL1, .ops=(instr_fop[2]){.mnemo="INS", { F_ADDR_Y | F_OPERAND_V, REG_16_DX, 0, 0 }, .mnemo="INSD", { F_ADDR_Y | F_OPERAND_DO, REG_16_DX, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Input from Port to String */
	{ .op1=0x6E, .rlvl=RLVL1, .ops=(instr_fop[2]){.mnemo="OUTS", { REG_16_DX, F_ADDR_X | F_OPERAND_B, 0, 0 }, .mnemo="OUTSB", { REG_16_DX, F_ADDR_X | F_OPERAND_B, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Output String to Port */
	{ .op1=0x6F, .rlvl=RLVL1, .ops=(instr_fop[2]){.mnemo="OUTS", { REG_16_DX, F_ADDR_X | F_OPERAND_WO, 0, 0 }, .mnemo="OUTSW", { REG_16_DX, F_ADDR_X | F_OPERAND_WO, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Output String to Port */
	{ .op1=0x6F, .rlvl=RLVL1, .ops=(instr_fop[2]){.mnemo="OUTS", { REG_16_DX, F_ADDR_X | F_OPERAND_V, 0, 0 }, .mnemo="OUTSD", { REG_16_DX, F_ADDR_X | F_OPERAND_DO, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Output String to Port */
	{ .op1=0x70, .mnemo="JO", .ops={ { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if overflow (OF=1) */
	{ .op1=0x71, .mnemo="JNO", .ops={ { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if not overflow (OF=0) */
	{ .op1=0x72, .ops=(instr_fop[3]){.mnemo="JB", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JNAE", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JC", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=3, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if below/not above or equal/carry (CF=1) */
	{ .op1=0x73, .ops=(instr_fop[3]){.mnemo="JNB", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JAE", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JNC", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=3, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if not below/above or equal/not carry (CF=0) */
	{ .op1=0x74, .ops=(instr_fop[2]){.mnemo="JZ", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JE", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if zero/equal (ZF=1) */
	{ .op1=0x75, .ops=(instr_fop[2]){.mnemo="JNZ", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JNE", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if not zero/not equal (ZF=0) */
	{ .op1=0x76, .ops=(instr_fop[2]){.mnemo="JBE", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JNA", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if below or equal/not above (CF=1 OR ZF=1) */
	{ .op1=0x77, .ops=(instr_fop[2]){.mnemo="JNBE", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JA", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if not below or equal/above (CF=0 AND ZF=0) */
	{ .op1=0x78, .mnemo="JS", .ops={ { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if sign (SF=1) */
	{ .op1=0x79, .mnemo="JNS", .ops={ { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if not sign (SF=0) */
	{ .op1=0x7A, .ops=(instr_fop[2]){.mnemo="JP", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JPE", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if parity/parity even (PF=1) */
	{ .op1=0x7B, .ops=(instr_fop[2]){.mnemo="JNP", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JPO", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if not parity/parity odd (PF=0) */
	{ .op1=0x7C, .ops=(instr_fop[2]){.mnemo="JL", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JNGE", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if less/not greater (SF!=OF) */
	{ .op1=0x7D, .ops=(instr_fop[2]){.mnemo="JNL", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JGE", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if not less/greater or equal (SF=OF) */
	{ .op1=0x7E, .ops=(instr_fop[2]){.mnemo="JLE", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JNG", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if less or equal/not greater ((ZF=1) OR (SF!=OF)) */
	{ .op1=0x7F, .ops=(instr_fop[2]){.mnemo="JNLE", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, .mnemo="JG", { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if not less nor equal/greater ((ZF=0) AND (SF=OF)) */
	{ .op1=0x80, .reg_op=0xb, .x=X_LOCK, .mnemo="ADD", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add */
	{ .op1=0x80, .reg_op=1, .x=X_LOCK, .mnemo="OR", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Inclusive OR */
	{ .op1=0x80, .reg_op=2, .x=X_LOCK, .mnemo="ADC", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add with Carry */
	{ .op1=0x80, .reg_op=3, .x=X_LOCK, .mnemo="SBB", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Integer Subtraction with Borrow */
	{ .op1=0x80, .reg_op=4, .x=X_LOCK, .mnemo="AND", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical AND */
	{ .op1=0x80, .reg_op=5, .x=X_LOCK, .mnemo="SUB", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Subtract */
	{ .op1=0x80, .reg_op=6, .x=X_LOCK, .mnemo="XOR", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Exclusive OR */
	{ .op1=0x80, .reg_op=7, .mnemo="CMP", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Compare Two Operands */
	{ .op1=0x81, .reg_op=0xb, .x=X_LOCK, .mnemo="ADD", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add */
	{ .op1=0x81, .reg_op=1, .x=X_LOCK, .mnemo="OR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Inclusive OR */
	{ .op1=0x81, .reg_op=2, .x=X_LOCK, .mnemo="ADC", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add with Carry */
	{ .op1=0x81, .reg_op=3, .x=X_LOCK, .mnemo="SBB", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Integer Subtraction with Borrow */
	{ .op1=0x81, .reg_op=4, .x=X_LOCK, .mnemo="AND", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical AND */
	{ .op1=0x81, .reg_op=5, .x=X_LOCK, .mnemo="SUB", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Subtract */
	{ .op1=0x81, .reg_op=6, .x=X_LOCK, .mnemo="XOR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Exclusive OR */
	{ .op1=0x81, .reg_op=7, .mnemo="CMP", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Compare Two Operands */
	{ .op1=0x82, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x83, .reg_op=0xb, .x=X_LOCK, .mnemo="ADD", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_BS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add */
	{ .op1=0x83, .reg_op=1, .x=X_LOCK, .mnemo="OR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_BS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Inclusive OR */
	{ .op1=0x83, .reg_op=2, .x=X_LOCK, .mnemo="ADC", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_BS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Add with Carry */
	{ .op1=0x83, .reg_op=3, .x=X_LOCK, .mnemo="SBB", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_BS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Integer Subtraction with Borrow */
	{ .op1=0x83, .reg_op=4, .x=X_LOCK, .mnemo="AND", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_BS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical AND */
	{ .op1=0x83, .reg_op=5, .x=X_LOCK, .mnemo="SUB", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_BS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Subtract */
	{ .op1=0x83, .reg_op=6, .x=X_LOCK, .mnemo="XOR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_BS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Exclusive OR */
	{ .op1=0x83, .reg_op=7, .mnemo="CMP", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_BS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Compare Two Operands */
	{ .op1=0x84, .reg_op=0xf, .mnemo="TEST", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_G | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Compare */
	{ .op1=0x85, .reg_op=0xf, .mnemo="TEST", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Compare */
	{ .op1=0x86, .reg_op=0xf, .x=X_LOCK, .mnemo="XCHG", .ops={ { F_ADDR_G | F_OPERAND_B, F_ADDR_E | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Exchange Register/Memory with Register */
	{ .op1=0x87, .reg_op=0xf, .x=X_LOCK, .mnemo="XCHG", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Exchange Register/Memory with Register */
	{ .op1=0x88, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_G | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0x89, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0x8A, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_G | F_OPERAND_B, F_ADDR_E | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0x8B, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0x8C, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="MOV", { F_ADDR_M | F_OPERAND_W, F_ADDR_S | F_OPERAND_W, 0, 0 }, .mnemo="MOV", { F_ADDR_R | F_OPERAND_VQP, F_ADDR_S | F_OPERAND_W, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0x8D, .reg_op=0xf, .mnemo="LEA", .ops={ { F_ADDR_G | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Load Effective Address */
	{ .op1=0x8E, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_S | F_OPERAND_W, F_ADDR_E | F_OPERAND_W, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0x8F, .reg_op=0xb, .mnemo="POP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Pop a Value from the Stack */
	{ .op1=0x8F, .reg_op=0xb, .mnemo="POP", .ops={ { F_ADDR_E | F_OPERAND_VQ, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Pop a Value from the Stack */
	{ .op1=0x90, .flds=1, .mnemo="XCHG", .ops={ { F_ADDR_Z | F_OPERAND_VQP, REG_ANY_RAX, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Exchange Register/Memory with Register */
	{ .op1=0x90, .mnemo="NOP", .grp=GRP(GEN, CONTROL, 0), },		/* DESCRIPTION=No Operation */
	{ .pfx=0xF3, .op1=0x90, .mnemo="PAUSE", .grp=GRP(CACHECT, 0, 0), },		/* DESCRIPTION=Spin Loop Hint */
	{ .op1=0x98, .ops=(instr_fop[3]){.mnemo="CBW", { REG_16_AX, REG_8_AL, 0, 0 }, .mnemo="CWDE", { REG_16_EAX, REG_16_AX, 0, 0 }, .mnemo="CDQE", { REG_16_RAX, REG_16_EAX, 0, 0 }, }, .opnum=3, .grp=GRP(GEN, CONVER, 0), },		/* DESCRIPTION=Convert */
	{ .op1=0x99, .ops=(instr_fop[3]){.mnemo="CWD", { REG_16_DX, REG_16_AX, 0, 0 }, .mnemo="CDQ", { REG_16_EDX, REG_16_EAX, 0, 0 }, .mnemo="CQO", { REG_16_RDX, REG_16_RAX, 0, 0 }, }, .opnum=3, .grp=GRP(GEN, CONVER, 0), },		/* DESCRIPTION=Convert */
	{ .op1=0x9A, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0x9B, .ops=(instr_fop[2]){.mnemo="FWAIT", { 0, 0, 0, 0 }, .mnemo="WAIT", { 0, 0, 0, 0 }, }, .opnum=2, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Check pending unmasked floating-point exceptions */
	{ .pfx=0x9B, },		/* DESCRIPTION=Wait Prefix */
	{ .op1=0x9C, .ops=(instr_fop[2]){.mnemo="PUSHF", { F_ADDR_F | F_OPERAND_WS, 0, 0, 0 }, .mnemo="PUSHFQ", { F_ADDR_F | F_OPERAND_QS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Push rFLAGS Register onto the Stack */
	{ .op1=0x9D, .ops=(instr_fop[2]){.mnemo="POPF", { F_ADDR_F | F_OPERAND_WS, 0, 0, 0 }, .mnemo="POPFQ", { F_ADDR_F | F_OPERAND_QS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Pop Stack into rFLAGS Register */
	{ .op1=0x9E, .mnemo="SAHF", .ops={ { REG_8_AH, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Store AH into Flags */
	{ .op1=0x9F, .mnemo="LAHF", .ops={ { REG_8_AH, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Load Status Flags into AH Register */
	{ .op1=0xA0, .mnemo="MOV", .ops={ { REG_8_AL, F_ADDR_O | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0xA1, .mnemo="MOV", .ops={ { REG_ANY_RAX, F_ADDR_O | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0xA2, .mnemo="MOV", .ops={ { F_ADDR_O | F_OPERAND_B, REG_8_AL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0xA3, .mnemo="MOV", .ops={ { F_ADDR_O | F_OPERAND_VQP, REG_ANY_RAX, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0xA4, .ops=(instr_fop[2]){.mnemo="MOVS", { F_ADDR_Y | F_OPERAND_B, F_ADDR_X | F_OPERAND_B, 0, 0 }, .mnemo="MOVSB", { F_ADDR_Y | F_OPERAND_B, F_ADDR_X | F_OPERAND_B, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Move Data from String to String */
	{ .op1=0xA5, .ops=(instr_fop[4]){.mnemo="MOVS", { F_ADDR_Y | F_OPERAND_VQP, F_ADDR_X | F_OPERAND_VQP, 0, 0 }, .mnemo="MOVSW", { F_ADDR_Y | F_OPERAND_WO, F_ADDR_X | F_OPERAND_WO, 0, 0 }, .mnemo="MOVSD", { F_ADDR_Y | F_OPERAND_DO, F_ADDR_X | F_OPERAND_DO, 0, 0 }, .mnemo="MOVSQ", { F_ADDR_Y | F_OPERAND_QP, F_ADDR_X | F_OPERAND_QP, 0, 0 }, }, .opnum=4, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Move Data from String to String */
	{ .op1=0xA6, .ops=(instr_fop[2]){.mnemo="CMPS", { F_ADDR_Y | F_OPERAND_B, F_ADDR_X | F_OPERAND_B, 0, 0 }, .mnemo="CMPSB", { F_ADDR_Y | F_OPERAND_B, F_ADDR_X | F_OPERAND_B, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, BINARY), },		/* DESCRIPTION=Compare String Operands */
	{ .op1=0xA7, .ops=(instr_fop[4]){.mnemo="CMPS", { F_ADDR_Y | F_OPERAND_VQP, F_ADDR_X | F_OPERAND_VQP, 0, 0 }, .mnemo="CMPSW", { F_ADDR_Y | F_OPERAND_WO, F_ADDR_X | F_OPERAND_WO, 0, 0 }, .mnemo="CMPSD", { F_ADDR_Y | F_OPERAND_DO, F_ADDR_X | F_OPERAND_DO, 0, 0 }, .mnemo="CMPSQ", { F_ADDR_Y | F_OPERAND_QP, F_ADDR_X | F_OPERAND_QP, 0, 0 }, }, .opnum=4, .grp=GRP(GEN, 0, BINARY), },		/* DESCRIPTION=Compare String Operands */
	{ .op1=0xA8, .mnemo="TEST", .ops={ { REG_8_AL, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Compare */
	{ .op1=0xA9, .mnemo="TEST", .ops={ { REG_ANY_RAX, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Compare */
	{ .op1=0xAA, .ops=(instr_fop[2]){.mnemo="STOS", { F_ADDR_Y | F_OPERAND_B, REG_8_AL, 0, 0 }, .mnemo="STOSB", { F_ADDR_Y | F_OPERAND_B, REG_8_AL, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Store String */
	{ .op1=0xAB, .ops=(instr_fop[4]){.mnemo="STOS", { F_ADDR_Y | F_OPERAND_VQP, REG_ANY_RAX, 0, 0 }, .mnemo="STOSW", { F_ADDR_Y | F_OPERAND_WO, REG_16_AX, 0, 0 }, .mnemo="STOSD", { F_ADDR_Y | F_OPERAND_DO, REG_16_EAX, 0, 0 }, .mnemo="STOSQ", { F_ADDR_Y | F_OPERAND_QP, REG_16_RAX, 0, 0 }, }, .opnum=4, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Store String */
	{ .op1=0xAC, .ops=(instr_fop[2]){.mnemo="LODS", { REG_8_AL, F_ADDR_X | F_OPERAND_B, 0, 0 }, .mnemo="LODSB", { REG_8_AL, F_ADDR_X | F_OPERAND_B, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Load String */
	{ .op1=0xAD, .ops=(instr_fop[4]){.mnemo="LODS", { REG_ANY_RAX, F_ADDR_X | F_OPERAND_VQP, 0, 0 }, .mnemo="LODSW", { REG_16_AX, F_ADDR_X | F_OPERAND_WO, 0, 0 }, .mnemo="LODSD", { REG_16_EAX, F_ADDR_X | F_OPERAND_DO, 0, 0 }, .mnemo="LODSQ", { REG_16_RAX, F_ADDR_X | F_OPERAND_QP, 0, 0 }, }, .opnum=4, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Load String */
	{ .op1=0xAE, .ops=(instr_fop[2]){.mnemo="SCAS", { F_ADDR_Y | F_OPERAND_B, REG_8_AL, 0, 0 }, .mnemo="SCASB", { F_ADDR_Y | F_OPERAND_B, REG_8_AL, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, BINARY), },		/* DESCRIPTION=Scan String */
	{ .op1=0xAF, .ops=(instr_fop[4]){.mnemo="SCAS", { F_ADDR_Y | F_OPERAND_VQP, REG_ANY_RAX, 0, 0 }, .mnemo="SCASW", { F_ADDR_Y | F_OPERAND_WO, REG_16_AX, 0, 0 }, .mnemo="SCASD", { F_ADDR_Y | F_OPERAND_DO, REG_16_EAX, 0, 0 }, .mnemo="SCASQ", { F_ADDR_Y | F_OPERAND_QP, REG_16_RAX, 0, 0 }, }, .opnum=4, .grp=GRP(GEN, 0, BINARY), },		/* DESCRIPTION=Scan String */
	{ .op1=0xB0, .flds=1, .mnemo="MOV", .ops={ { F_ADDR_Z | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0xB8, .flds=1, .mnemo="MOV", .ops={ { F_ADDR_Z | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VQP, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0xC0, .reg_op=0xb, .mnemo="ROL", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xC0, .reg_op=1, .mnemo="ROR", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xC0, .reg_op=2, .mnemo="RCL", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xC0, .reg_op=3, .mnemo="RCR", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xC0, .reg_op=4, .ops=(instr_fop[2]){.mnemo="SHL", { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, .mnemo="SAL", { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xC0, .reg_op=5, .mnemo="SHR", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xC0, .reg_op=6, .ops=(instr_fop[2]){.mnemo="SAL alias", { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, .mnemo="SHL alias", { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xC0, .reg_op=7, .mnemo="SAR", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xC1, .reg_op=0xb, .mnemo="ROL", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xC1, .reg_op=1, .mnemo="ROR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xC1, .reg_op=2, .mnemo="RCL", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xC1, .reg_op=3, .mnemo="RCR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xC1, .reg_op=4, .ops=(instr_fop[2]){.mnemo="SHL", { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 }, .mnemo="SAL", { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xC1, .reg_op=5, .mnemo="SHR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xC1, .reg_op=6, .ops=(instr_fop[2]){.mnemo="SAL alias", { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 }, .mnemo="SHL alias", { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xC1, .reg_op=7, .mnemo="SAR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xC2, .mnemo="RETN", .ops={ { F_ADDR_I | F_OPERAND_W, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Return from procedure */
	{ .op1=0xC3, .mnemo="RETN", .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Return from procedure */
	{ .op1=0xC4, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0xC5, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0xC6, .reg_op=0xb, .mnemo="MOV", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0xC7, .reg_op=0xb, .mnemo="MOV", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Move */
	{ .op1=0xC8, .mnemo="ENTER", .ops={ { REG_ANY_RBP, F_ADDR_I | F_OPERAND_W, F_ADDR_I | F_OPERAND_B, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Make Stack Frame for Procedure Parameters */
	{ .op1=0xC9, .mnemo="LEAVE", .ops={ { REG_ANY_RBP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=High Level Procedure Exit */
	{ .op1=0xCA, .rlvl=RLVL3, .mnemo="RETF", .ops={ { F_ADDR_I | F_OPERAND_W, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Return from procedure */
	{ .op1=0xCB, .rlvl=RLVL3, .mnemo="RETF", .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Return from procedure */
	{ .op1=0xCC, .rlvl=RLVL3, .mnemo="INT alias", .ops={ { 0, F_ADDR_F | F_OPERAND_V, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Call to Interrupt Procedure */
	{ .op1=0xCD, .rlvl=RLVL3, .mnemo="INT", .ops={ { F_ADDR_I | F_OPERAND_B, F_ADDR_F | F_OPERAND_V, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Call to Interrupt Procedure */
	{ .op1=0xCE, .rlvl=RLVL3, .mnemo="INTO", .ops={ { F_ADDR_F | F_OPERAND_V, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Call to Interrupt Procedure */
	{ .op1=0xCF, .rlvl=RLVL3, .ops=(instr_fop[3]){.mnemo="IRET", { F_ADDR_F | F_OPERAND_WO, 0, 0, 0 }, .mnemo="IRETD", { F_ADDR_F | F_OPERAND_DO, 0, 0, 0 }, .mnemo="IRETQ", { F_ADDR_F | F_OPERAND_QP, 0, 0, 0 }, }, .opnum=3, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Interrupt Return */
	{ .op1=0xD0, .reg_op=0xb, .mnemo="ROL", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD0, .reg_op=1, .mnemo="ROR", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD0, .reg_op=2, .mnemo="RCL", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD0, .reg_op=3, .mnemo="RCR", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD0, .reg_op=4, .ops=(instr_fop[2]){.mnemo="SHL", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SAL", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD0, .reg_op=5, .mnemo="SHR", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD0, .reg_op=6, .ops=(instr_fop[2]){.mnemo="SAL alias", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SHL alias", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD0, .reg_op=7, .mnemo="SAR", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD1, .reg_op=0xb, .mnemo="ROL", .ops={ { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD1, .reg_op=1, .mnemo="ROR", .ops={ { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD1, .reg_op=2, .mnemo="RCL", .ops={ { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD1, .reg_op=3, .mnemo="RCR", .ops={ { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD1, .reg_op=4, .ops=(instr_fop[2]){.mnemo="SHL", { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, .mnemo="SAL", { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD1, .reg_op=5, .mnemo="SHR", .ops={ { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD1, .reg_op=6, .ops=(instr_fop[2]){.mnemo="SAL alias", { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, .mnemo="SHL alias", { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD1, .reg_op=7, .mnemo="SAR", .ops={ { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD2, .reg_op=0xb, .mnemo="ROL", .ops={ { F_ADDR_E | F_OPERAND_B, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD2, .reg_op=1, .mnemo="ROR", .ops={ { F_ADDR_E | F_OPERAND_B, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD2, .reg_op=2, .mnemo="RCL", .ops={ { F_ADDR_E | F_OPERAND_B, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD2, .reg_op=3, .mnemo="RCR", .ops={ { F_ADDR_E | F_OPERAND_B, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD2, .reg_op=4, .ops=(instr_fop[2]){.mnemo="SHL", { F_ADDR_E | F_OPERAND_B, REG_8_CL, 0, 0 }, .mnemo="SAL", { F_ADDR_E | F_OPERAND_B, REG_8_CL, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD2, .reg_op=5, .mnemo="SHR", .ops={ { F_ADDR_E | F_OPERAND_B, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD2, .reg_op=6, .ops=(instr_fop[2]){.mnemo="SAL alias", { F_ADDR_E | F_OPERAND_B, REG_8_CL, 0, 0 }, .mnemo="SHL alias", { F_ADDR_E | F_OPERAND_B, REG_8_CL, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD2, .reg_op=7, .mnemo="SAR", .ops={ { F_ADDR_E | F_OPERAND_B, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD3, .reg_op=0xb, .mnemo="ROL", .ops={ { F_ADDR_E | F_OPERAND_VQP, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD3, .reg_op=1, .mnemo="ROR", .ops={ { F_ADDR_E | F_OPERAND_VQP, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD3, .reg_op=2, .mnemo="RCL", .ops={ { F_ADDR_E | F_OPERAND_VQP, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD3, .reg_op=3, .mnemo="RCR", .ops={ { F_ADDR_E | F_OPERAND_VQP, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Rotate */
	{ .op1=0xD3, .reg_op=4, .ops=(instr_fop[2]){.mnemo="SHL", { F_ADDR_E | F_OPERAND_VQP, REG_8_CL, 0, 0 }, .mnemo="SAL", { F_ADDR_E | F_OPERAND_VQP, REG_8_CL, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD3, .reg_op=5, .mnemo="SHR", .ops={ { F_ADDR_E | F_OPERAND_VQP, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD3, .reg_op=6, .ops=(instr_fop[2]){.mnemo="SAL alias", { F_ADDR_E | F_OPERAND_VQP, REG_8_CL, 0, 0 }, .mnemo="SHL alias", { F_ADDR_E | F_OPERAND_VQP, REG_8_CL, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD3, .reg_op=7, .mnemo="SAR", .ops={ { F_ADDR_E | F_OPERAND_VQP, REG_8_CL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0), },		/* DESCRIPTION=Shift */
	{ .op1=0xD4, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0xD5, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0xD6, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0xD7, .ops=(instr_fop[2]){.mnemo="XLAT", { REG_8_AL, F_ADDR_BB | F_OPERAND_B, 0, 0 }, .mnemo="XLATB", { REG_8_AL, F_ADDR_BB | F_OPERAND_B, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0), },		/* DESCRIPTION=Table Look-up Translation */
	{ .op1=0xD8, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="FADD", { 0, F_ADDR_M | F_OPERAND_SR, 0, 0 }, .mnemo="FADD", { 0, 0, 0, 0 }, }, .opnum=2, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Add */
	{ .op1=0xD8, .reg_op=1, .ops=(instr_fop[2]){.mnemo="FMUL", { 0, F_ADDR_M | F_OPERAND_SR, 0, 0 }, .mnemo="FMUL", { 0, 0, 0, 0 }, }, .opnum=2, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Multiply */
	{ .op1=0xD8, .reg_op=2, .mnemo="FCOM", .ops={ { 0, F_ADDR_ES | F_OPERAND_SR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Real */
	{ .op1=0xD8, .op2=0xD1, .reg_op=2, .mnemo="FCOM", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Real */
	{ .op1=0xD8, .reg_op=3, .x=X_FPU_POP, .mnemo="FCOMP", .ops={ { 0, F_ADDR_ES | F_OPERAND_SR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Real and Pop */
	{ .op1=0xD8, .op2=0xD9, .reg_op=3, .x=X_FPU_POP, .mnemo="FCOMP", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Real and Pop */
	{ .op1=0xD8, .reg_op=4, .ops=(instr_fop[2]){.mnemo="FSUB", { 0, F_ADDR_M | F_OPERAND_SR, 0, 0 }, .mnemo="FSUB", { 0, 0, 0, 0 }, }, .opnum=2, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Subtract */
	{ .op1=0xD8, .reg_op=5, .ops=(instr_fop[2]){.mnemo="FSUBR", { 0, F_ADDR_M | F_OPERAND_SR, 0, 0 }, .mnemo="FSUBR", { 0, 0, 0, 0 }, }, .opnum=2, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Subtract */
	{ .op1=0xD8, .reg_op=6, .ops=(instr_fop[2]){.mnemo="FDIV", { 0, F_ADDR_M | F_OPERAND_SR, 0, 0 }, .mnemo="FDIV", { 0, 0, 0, 0 }, }, .opnum=2, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Divide */
	{ .op1=0xD8, .reg_op=7, .ops=(instr_fop[2]){.mnemo="FDIVR", { 0, F_ADDR_M | F_OPERAND_SR, 0, 0 }, .mnemo="FDIVR", { 0, 0, 0, 0 }, }, .opnum=2, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Divide */
	{ .op1=0xD9, .reg_op=0xb, .x=X_FPU_PUSH, .mnemo="FLD", .ops={ { 0, F_ADDR_ES | F_OPERAND_SR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Load Floating Point Value */
	{ .op1=0xD9, .reg_op=1, .mnemo="FXCH", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Exchange Register Contents */
	{ .op1=0xD9, .op2=0xC9, .reg_op=1, .mnemo="FXCH", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Exchange Register Contents */
	{ .op1=0xD9, .reg_op=2, .mnemo="FST", .ops={ { F_ADDR_M | F_OPERAND_SR, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Floating Point Value */
	{ .op1=0xD9, .op2=0xD0, .reg_op=2, .mnemo="FNOP", .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=No Operation */
	{ .op1=0xD9, .reg_op=3, .x=X_FPU_POP, .mnemo="FSTP", .ops={ { F_ADDR_M | F_OPERAND_SR, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Floating Point Value and Pop */
	{ .op1=0xD9, .reg_op=3, .x=X_FPU_POP, .mnemo="FSTP1 part alias5", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Floating Point Value and Pop */
	{ .op1=0xD9, .reg_op=4, .mnemo="FLDENV", .ops={ { F_ADDR_M | F_OPERAND_E, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Load x87 FPU Environment */
	{ .op1=0xD9, .op2=0xE0, .reg_op=4, .mnemo="FCHS", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Change Sign */
	{ .op1=0xD9, .op2=0xE1, .reg_op=4, .mnemo="FABS", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Absolute Value */
	{ .op1=0xD9, .op2=0xE4, .reg_op=4, .mnemo="FTST", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Test */
	{ .op1=0xD9, .op2=0xE5, .reg_op=4, .mnemo="FXAM", .grp=GRP(X87FPU, 0, 0), },		/* DESCRIPTION=Examine */
	{ .op1=0xD9, .reg_op=5, .mnemo="FLDCW", .ops={ { F_ADDR_M | F_OPERAND_W, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Load x87 FPU Control Word */
	{ .op1=0xD9, .op2=0xE8, .reg_op=5, .x=X_FPU_PUSH, .mnemo="FLD1", .grp=GRP(X87FPU, 0, 0), },		/* DESCRIPTION=Load Constant +1.0 */
	{ .op1=0xD9, .op2=0xE9, .reg_op=5, .x=X_FPU_PUSH, .mnemo="FLDL2T", .grp=GRP(X87FPU, 0, 0), },		/* DESCRIPTION=Load Constant log210 */
	{ .op1=0xD9, .op2=0xEA, .reg_op=5, .x=X_FPU_PUSH, .mnemo="FLDL2E", .grp=GRP(X87FPU, 0, 0), },		/* DESCRIPTION=Load Constant log2e */
	{ .op1=0xD9, .op2=0xEB, .reg_op=5, .x=X_FPU_PUSH, .mnemo="FLDPI", .grp=GRP(X87FPU, 0, 0), },		/* DESCRIPTION=Load Constant π */
	{ .op1=0xD9, .op2=0xEC, .reg_op=5, .x=X_FPU_PUSH, .mnemo="FLDLG2", .grp=GRP(X87FPU, 0, 0), },		/* DESCRIPTION=Load Constant log102 */
	{ .op1=0xD9, .op2=0xED, .reg_op=5, .x=X_FPU_PUSH, .mnemo="FLDLN2", .grp=GRP(X87FPU, 0, 0), },		/* DESCRIPTION=Load Constant loge2 */
	{ .op1=0xD9, .op2=0xEE, .reg_op=5, .x=X_FPU_PUSH, .mnemo="FLDZ", .grp=GRP(X87FPU, 0, 0), },		/* DESCRIPTION=Load Constant +0.0 */
	{ .op1=0xD9, .reg_op=6, .mnemo="FNSTENV", .ops={ { F_ADDR_M | F_OPERAND_E, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Store x87 FPU Environment */
	{ .pfx=0x9B, .op1=0xD9, .reg_op=6, .mnemo="FSTENV", .ops={ { F_ADDR_M | F_OPERAND_E, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Store x87 FPU Environment */
	{ .op1=0xD9, .op2=0xF0, .reg_op=6, .mnemo="F2XM1", .grp=GRP(X87FPU, TRANS, 0), },		/* DESCRIPTION=Compute 2x-1 */
	{ .op1=0xD9, .op2=0xF1, .reg_op=6, .x=X_FPU_POP, .mnemo="FYL2X", .grp=GRP(X87FPU, TRANS, 0), },		/* DESCRIPTION=Compute y × log2x and Pop */
	{ .op1=0xD9, .op2=0xF2, .reg_op=6, .x=X_FPU_PUSH, .mnemo="FPTAN", .grp=GRP(X87FPU, TRANS, 0), },		/* DESCRIPTION=Partial Tangent */
	{ .op1=0xD9, .op2=0xF3, .reg_op=6, .x=X_FPU_POP, .mnemo="FPATAN", .grp=GRP(X87FPU, TRANS, 0), },		/* DESCRIPTION=Partial Arctangent and Pop */
	{ .op1=0xD9, .op2=0xF4, .reg_op=6, .x=X_FPU_PUSH, .mnemo="FXTRACT", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Extract Exponent and Significand */
	{ .op1=0xD9, .op2=0xF5, .reg_op=6, .mnemo="FPREM1", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=IEEE Partial Remainder */
	{ .op1=0xD9, .op2=0xF6, .reg_op=6, .mnemo="FDECSTP", .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Decrement Stack-Top Pointer */
	{ .op1=0xD9, .op2=0xF7, .reg_op=6, .mnemo="FINCSTP", .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Increment Stack-Top Pointer */
	{ .op1=0xD9, .reg_op=7, .mnemo="FNSTCW", .ops={ { F_ADDR_M | F_OPERAND_W, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Store x87 FPU Control Word */
	{ .pfx=0x9B, .op1=0xD9, .reg_op=7, .mnemo="FSTCW", .ops={ { F_ADDR_M | F_OPERAND_W, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Store x87 FPU Control Word */
	{ .op1=0xD9, .op2=0xF8, .reg_op=7, .mnemo="FPREM", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Partial Remainder (for compatibility with i8087 and i287) */
	{ .op1=0xD9, .op2=0xF9, .reg_op=7, .x=X_FPU_POP, .mnemo="FYL2XP1", .grp=GRP(X87FPU, TRANS, 0), },		/* DESCRIPTION=Compute y × log2(x+1) and Pop */
	{ .op1=0xD9, .op2=0xFA, .reg_op=7, .mnemo="FSQRT", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Square Root */
	{ .op1=0xD9, .op2=0xFB, .reg_op=7, .x=X_FPU_PUSH, .mnemo="FSINCOS", .grp=GRP(X87FPU, TRANS, 0), },		/* DESCRIPTION=Sine and Cosine */
	{ .op1=0xD9, .op2=0xFC, .reg_op=7, .mnemo="FRNDINT", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Round to Integer */
	{ .op1=0xD9, .op2=0xFD, .reg_op=7, .mnemo="FSCALE", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Scale */
	{ .op1=0xD9, .op2=0xFE, .reg_op=7, .mnemo="FSIN", .grp=GRP(X87FPU, TRANS, 0), },		/* DESCRIPTION=Sine */
	{ .op1=0xD9, .op2=0xFF, .reg_op=7, .mnemo="FCOS", .grp=GRP(X87FPU, TRANS, 0), },		/* DESCRIPTION=Cosine */
	{ .op1=0xDA, .reg_op=0xb, .mnemo="FIADD", .ops={ { 0, F_ADDR_M | F_OPERAND_DI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Add */
	{ .op1=0xDA, .reg_op=0xb, .mnemo="FCMOVB", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=FP Conditional Move - below (CF=1) */
	{ .op1=0xDA, .reg_op=1, .mnemo="FIMUL", .ops={ { 0, F_ADDR_M | F_OPERAND_DI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Multiply */
	{ .op1=0xDA, .reg_op=1, .mnemo="FCMOVE", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=FP Conditional Move - equal (ZF=1) */
	{ .op1=0xDA, .reg_op=2, .mnemo="FICOM", .ops={ { 0, F_ADDR_M | F_OPERAND_DI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Integer */
	{ .op1=0xDA, .reg_op=2, .mnemo="FCMOVBE", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=FP Conditional Move - below or equal (CF=1 or ZF=1) */
	{ .op1=0xDA, .reg_op=3, .x=X_FPU_POP, .mnemo="FICOMP", .ops={ { 0, F_ADDR_M | F_OPERAND_DI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Integer and Pop */
	{ .op1=0xDA, .reg_op=3, .mnemo="FCMOVU", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=FP Conditional Move - unordered (PF=1) */
	{ .op1=0xDA, .reg_op=4, .mnemo="FISUB", .ops={ { 0, F_ADDR_M | F_OPERAND_DI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Subtract */
	{ .op1=0xDA, .reg_op=5, .mnemo="FISUBR", .ops={ { 0, F_ADDR_M | F_OPERAND_DI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Subtract */
	{ .op1=0xDA, .op2=0xE9, .reg_op=5, .x=X_FPU_POPOP, .mnemo="FUCOMPP", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Unordered Compare Floating Point Values and Pop Twice */
	{ .op1=0xDA, .reg_op=6, .mnemo="FIDIV", .ops={ { 0, F_ADDR_M | F_OPERAND_DI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Divide */
	{ .op1=0xDA, .reg_op=7, .mnemo="FIDIVR", .ops={ { 0, F_ADDR_M | F_OPERAND_DI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Divide */
	{ .op1=0xDB, .reg_op=0xb, .x=X_FPU_PUSH, .mnemo="FILD", .ops={ { 0, F_ADDR_M | F_OPERAND_DI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Load Integer */
	{ .op1=0xDB, .reg_op=0xb, .mnemo="FCMOVNB", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=FP Conditional Move - not below (CF=0) */
	{ .op1=0xDB, .reg_op=1, .x=X_FPU_POP, .mnemo="FISTTP", .ops={ { F_ADDR_M | F_OPERAND_DI, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONVER, 0), },		/* DESCRIPTION=Store Integer with Truncation and Pop */
	{ .op1=0xDB, .reg_op=1, .mnemo="FCMOVNE", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=FP Conditional Move - not equal (ZF=0) */
	{ .op1=0xDB, .reg_op=2, .mnemo="FIST", .ops={ { F_ADDR_M | F_OPERAND_DI, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Integer */
	{ .op1=0xDB, .reg_op=2, .mnemo="FCMOVNBE", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=FP Conditional Move - below or equal (CF=0 and ZF=0) */
	{ .op1=0xDB, .reg_op=3, .x=X_FPU_POP, .mnemo="FISTP", .ops={ { F_ADDR_M | F_OPERAND_DI, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Integer and Pop */
	{ .op1=0xDB, .reg_op=3, .mnemo="FCMOVNU", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=FP Conditional Move - not unordered (PF=0) */
	{ .op1=0xDB, .op2=0xE0, .reg_op=4, .mnemo="FNENI nop", .grp=GRP(0, CONTROL, 0), },		/* DESCRIPTION=Treated as Integer NOP */
	{ .op1=0xDB, .op2=0xE1, .reg_op=4, .mnemo="FNDISI nop", .grp=GRP(0, CONTROL, 0), },		/* DESCRIPTION=Treated as Integer NOP */
	{ .op1=0xDB, .op2=0xE2, .reg_op=4, .mnemo="FNCLEX", .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Clear Exceptions */
	{ .pfx=0x9B, .op1=0xDB, .op2=0xE2, .reg_op=4, .mnemo="FCLEX", .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Clear Exceptions */
	{ .op1=0xDB, .op2=0xE3, .reg_op=4, .mnemo="FNINIT", .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Initialize Floating-Point Unit */
	{ .pfx=0x9B, .op1=0xDB, .op2=0xE3, .reg_op=4, .mnemo="FINIT", .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Initialize Floating-Point Unit */
	{ .op1=0xDB, .op2=0xE4, .reg_op=4, .mnemo="FNSETPM nop", .grp=GRP(0, CONTROL, 0), },		/* DESCRIPTION=Treated as Integer NOP */
	{ .op1=0xDB, .reg_op=5, .x=X_FPU_PUSH, .mnemo="FLD", .ops={ { 0, F_ADDR_M | F_OPERAND_ER, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Load Floating Point Value */
	{ .op1=0xDB, .reg_op=5, .mnemo="FUCOMI", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Unordered Compare Floating Point Values and Set EFLAGS */
	{ .op1=0xDB, .reg_op=6, .mnemo="FCOMI", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Floating Point Values and Set EFLAGS */
	{ .op1=0xDB, .reg_op=7, .x=X_FPU_POP, .mnemo="FSTP", .ops={ { F_ADDR_M | F_OPERAND_ER, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Floating Point Value and Pop */
	{ .op1=0xDC, .reg_op=0xb, .mnemo="FADD", .ops={ { 0, F_ADDR_M | F_OPERAND_DR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Add */
	{ .op1=0xDC, .reg_op=0xb, .mnemo="FADD", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Add */
	{ .op1=0xDC, .reg_op=1, .mnemo="FMUL", .ops={ { 0, F_ADDR_M | F_OPERAND_DR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Multiply */
	{ .op1=0xDC, .reg_op=1, .mnemo="FMUL", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Multiply */
	{ .op1=0xDC, .reg_op=2, .mnemo="FCOM", .ops={ { 0, F_ADDR_M | F_OPERAND_DR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Real */
	{ .op1=0xDC, .reg_op=2, .mnemo="FCOM2 alias", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Real */
	{ .op1=0xDC, .reg_op=3, .x=X_FPU_POP, .mnemo="FCOMP", .ops={ { 0, F_ADDR_M | F_OPERAND_DR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Real and Pop */
	{ .op1=0xDC, .reg_op=3, .x=X_FPU_POP, .mnemo="FCOMP3 alias", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Real and Pop */
	{ .op1=0xDC, .reg_op=4, .mnemo="FSUB", .ops={ { 0, F_ADDR_M | F_OPERAND_DR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Subtract */
	{ .op1=0xDC, .reg_op=4, .mnemo="FSUBR", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Subtract */
	{ .op1=0xDC, .reg_op=5, .mnemo="FSUBR", .ops={ { 0, F_ADDR_M | F_OPERAND_DR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Subtract */
	{ .op1=0xDC, .reg_op=5, .mnemo="FSUB", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Subtract */
	{ .op1=0xDC, .reg_op=6, .mnemo="FDIV", .ops={ { 0, F_ADDR_M | F_OPERAND_DR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Divide */
	{ .op1=0xDC, .reg_op=6, .mnemo="FDIVR", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Divide */
	{ .op1=0xDC, .reg_op=7, .mnemo="FDIVR", .ops={ { 0, F_ADDR_M | F_OPERAND_DR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Divide */
	{ .op1=0xDC, .reg_op=7, .mnemo="FDIV", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Divide and Pop */
	{ .op1=0xDD, .reg_op=0xb, .x=X_FPU_PUSH, .mnemo="FLD", .ops={ { 0, F_ADDR_M | F_OPERAND_DR, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Load Floating Point Value */
	{ .op1=0xDD, .reg_op=0xb, .mnemo="FFREE", .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Free Floating-Point Register */
	{ .op1=0xDD, .reg_op=1, .x=X_FPU_POP, .mnemo="FISTTP", .ops={ { F_ADDR_M | F_OPERAND_QI, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONVER, 0), },		/* DESCRIPTION=Store Integer with Truncation and Pop */
	{ .op1=0xDD, .reg_op=1, .mnemo="FXCH4 alias", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Exchange Register Contents */
	{ .op1=0xDD, .reg_op=2, .mnemo="FST", .ops={ { F_ADDR_M | F_OPERAND_DR, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Floating Point Value */
	{ .op1=0xDD, .reg_op=2, .mnemo="FST", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Floating Point Value */
	{ .op1=0xDD, .reg_op=3, .x=X_FPU_POP, .mnemo="FSTP", .ops={ { F_ADDR_M | F_OPERAND_DR, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Floating Point Value and Pop */
	{ .op1=0xDD, .reg_op=3, .x=X_FPU_POP, .mnemo="FSTP", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Floating Point Value and Pop */
	{ .op1=0xDD, .reg_op=4, .mnemo="FRSTOR", .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Restore x87 FPU State */
	{ .op1=0xDD, .reg_op=4, .mnemo="FUCOM", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Unordered Compare Floating Point Values */
	{ .op1=0xDD, .op2=0xE1, .reg_op=4, .mnemo="FUCOM", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Unordered Compare Floating Point Values */
	{ .op1=0xDD, .reg_op=5, .x=X_FPU_POP, .mnemo="FUCOMP", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Unordered Compare Floating Point Values and Pop */
	{ .op1=0xDD, .op2=0xE9, .reg_op=5, .x=X_FPU_POP, .mnemo="FUCOMP", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Unordered Compare Floating Point Values and Pop */
	{ .op1=0xDD, .reg_op=6, .mnemo="FNSAVE", .ops={ { F_ADDR_M | F_OPERAND_ST, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Store x87 FPU State */
	{ .pfx=0x9B, .op1=0xDD, .reg_op=6, .mnemo="FSAVE", .ops={ { F_ADDR_M | F_OPERAND_ST, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Store x87 FPU State */
	{ .op1=0xDD, .reg_op=7, .mnemo="FNSTSW", .ops={ { F_ADDR_M | F_OPERAND_W, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Store x87 FPU Status Word */
	{ .pfx=0x9B, .op1=0xDD, .reg_op=7, .mnemo="FSTSW", .ops={ { F_ADDR_M | F_OPERAND_W, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Store x87 FPU Status Word */
	{ .op1=0xDE, .reg_op=0xb, .mnemo="FIADD", .ops={ { 0, F_ADDR_M | F_OPERAND_WI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Add */
	{ .op1=0xDE, .reg_op=0xb, .x=X_FPU_POP, .mnemo="FADDP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Add and Pop */
	{ .op1=0xDE, .op2=0xC1, .reg_op=0xb, .x=X_FPU_POP, .mnemo="FADDP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Add and Pop */
	{ .op1=0xDE, .reg_op=1, .mnemo="FIMUL", .ops={ { 0, F_ADDR_M | F_OPERAND_WI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Multiply */
	{ .op1=0xDE, .reg_op=1, .x=X_FPU_POP, .mnemo="FMULP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Multiply and Pop */
	{ .op1=0xDE, .op2=0xC9, .reg_op=1, .x=X_FPU_POP, .mnemo="FMULP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Multiply and Pop */
	{ .op1=0xDE, .reg_op=2, .mnemo="FICOM", .ops={ { 0, F_ADDR_M | F_OPERAND_WI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Integer */
	{ .op1=0xDE, .reg_op=2, .x=X_FPU_POP, .mnemo="FCOMP5 alias", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Real and Pop */
	{ .op1=0xDE, .reg_op=3, .x=X_FPU_POP, .mnemo="FICOMP", .ops={ { 0, F_ADDR_M | F_OPERAND_WI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Integer and Pop */
	{ .op1=0xDE, .op2=0xD9, .reg_op=3, .x=X_FPU_POPOP, .mnemo="FCOMPP", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Real and Pop Twice */
	{ .op1=0xDE, .reg_op=4, .mnemo="FISUB", .ops={ { 0, F_ADDR_M | F_OPERAND_WI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Subtract */
	{ .op1=0xDE, .reg_op=4, .x=X_FPU_POP, .mnemo="FSUBRP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Subtract and Pop */
	{ .op1=0xDE, .op2=0xE1, .reg_op=4, .x=X_FPU_POP, .mnemo="FSUBRP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Subtract and Pop */
	{ .op1=0xDE, .reg_op=5, .mnemo="FISUBR", .ops={ { 0, F_ADDR_M | F_OPERAND_WI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Subtract */
	{ .op1=0xDE, .reg_op=5, .x=X_FPU_POP, .mnemo="FSUBP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Subtract and Pop */
	{ .op1=0xDE, .op2=0xE9, .reg_op=5, .x=X_FPU_POP, .mnemo="FSUBP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Subtract and Pop */
	{ .op1=0xDE, .reg_op=6, .mnemo="FIDIV", .ops={ { 0, F_ADDR_M | F_OPERAND_WI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Divide */
	{ .op1=0xDE, .reg_op=6, .x=X_FPU_POP, .mnemo="FDIVRP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Divide and Pop */
	{ .op1=0xDE, .op2=0xF1, .reg_op=6, .x=X_FPU_POP, .mnemo="FDIVRP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Divide and Pop */
	{ .op1=0xDE, .reg_op=7, .mnemo="FIDIVR", .ops={ { 0, F_ADDR_M | F_OPERAND_WI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Reverse Divide */
	{ .op1=0xDE, .reg_op=7, .x=X_FPU_POP, .mnemo="FDIVP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Divide and Pop */
	{ .op1=0xDE, .op2=0xF9, .reg_op=7, .x=X_FPU_POP, .mnemo="FDIVP", .grp=GRP(X87FPU, ARITH, 0), },		/* DESCRIPTION=Divide and Pop */
	{ .op1=0xDF, .reg_op=0xb, .x=X_FPU_PUSH, .mnemo="FILD", .ops={ { 0, F_ADDR_M | F_OPERAND_WI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Load Integer */
	{ .op1=0xDF, .reg_op=0xb, .x=X_FPU_POP, .mnemo="FFREEP", .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Free Floating-Point Register and Pop */
	{ .op1=0xDF, .reg_op=1, .x=X_FPU_POP, .mnemo="FISTTP", .ops={ { F_ADDR_M | F_OPERAND_WI, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONVER, 0), },		/* DESCRIPTION=Store Integer with Truncation and Pop */
	{ .op1=0xDF, .reg_op=1, .mnemo="FXCH7 alias", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Exchange Register Contents */
	{ .op1=0xDF, .reg_op=2, .mnemo="FIST", .ops={ { F_ADDR_M | F_OPERAND_WI, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Integer */
	{ .op1=0xDF, .reg_op=2, .x=X_FPU_POP, .mnemo="FSTP8 alias", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Floating Point Value and Pop */
	{ .op1=0xDF, .reg_op=3, .x=X_FPU_POP, .mnemo="FISTP", .ops={ { F_ADDR_M | F_OPERAND_WI, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Integer and Pop */
	{ .op1=0xDF, .reg_op=3, .x=X_FPU_POP, .mnemo="FSTP9 alias", .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Floating Point Value and Pop */
	{ .op1=0xDF, .reg_op=4, .x=X_FPU_PUSH, .mnemo="FBLD", .ops={ { 0, F_ADDR_M | F_OPERAND_BCD, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Load Binary Coded Decimal */
	{ .op1=0xDF, .op2=0xE0, .reg_op=4, .mnemo="FNSTSW", .ops={ { REG_16_AX, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Store x87 FPU Status Word */
	{ .pfx=0x9B, .op1=0xDF, .op2=0xE0, .reg_op=4, .mnemo="FSTSW", .ops={ { REG_16_AX, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0), },		/* DESCRIPTION=Store x87 FPU Status Word */
	{ .op1=0xDF, .reg_op=5, .x=X_FPU_PUSH, .mnemo="FILD", .ops={ { 0, F_ADDR_M | F_OPERAND_QI, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Load Integer */
	{ .op1=0xDF, .reg_op=5, .x=X_FPU_POP, .mnemo="FUCOMIP", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Unordered Compare Floating Point Values and Set EFLAGS and Pop */
	{ .op1=0xDF, .reg_op=6, .x=X_FPU_POP, .mnemo="FBSTP", .ops={ { F_ADDR_M | F_OPERAND_BCD, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store BCD Integer and Pop */
	{ .op1=0xDF, .reg_op=6, .x=X_FPU_POP, .mnemo="FCOMIP", .grp=GRP(X87FPU, COMPAR, 0), },		/* DESCRIPTION=Compare Floating Point Values and Set EFLAGS and Pop */
	{ .op1=0xDF, .reg_op=7, .x=X_FPU_POP, .mnemo="FISTP", .ops={ { F_ADDR_M | F_OPERAND_QI, 0, 0, 0 }, }, .opnum=1, .grp=GRP(X87FPU, DATAMOV, 0), },		/* DESCRIPTION=Store Integer and Pop */
	{ .op1=0xE0, .ops=(instr_fop[2]){.mnemo="LOOPNZ", { REG_ANY_RCX, F_ADDR_J | F_OPERAND_BS, 0, 0 }, .mnemo="LOOPNE", { REG_ANY_RCX, F_ADDR_J | F_OPERAND_BS, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Decrement count; Jump short if count!=0 and ZF=0 */
	{ .op1=0xE1, .ops=(instr_fop[2]){.mnemo="LOOPZ", { REG_ANY_RCX, F_ADDR_J | F_OPERAND_BS, 0, 0 }, .mnemo="LOOPE", { REG_ANY_RCX, F_ADDR_J | F_OPERAND_BS, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Decrement count; Jump short if count!=0 and ZF=1 */
	{ .op1=0xE2, .mnemo="LOOP", .ops={ { REG_ANY_RCX, F_ADDR_J | F_OPERAND_BS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Decrement count; Jump short if count!=0 */
	{ .op1=0xE3, .ops=(instr_fop[2]){.mnemo="JECXZ", { F_ADDR_J | F_OPERAND_BS, REG_16_ECX, 0, 0 }, .mnemo="JRCXZ", { F_ADDR_J | F_OPERAND_BS, REG_16_RCX, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND), },		/* DESCRIPTION=Jump short if rCX register is 0 */
	{ .op1=0xE4, .rlvl=RLVL1, .mnemo="IN", .ops={ { REG_8_AL, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Input from Port */
	{ .op1=0xE5, .rlvl=RLVL1, .mnemo="IN", .ops={ { 0, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Input from Port */
	{ .op1=0xE6, .rlvl=RLVL1, .mnemo="OUT", .ops={ { F_ADDR_I | F_OPERAND_B, REG_8_AL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Output to Port */
	{ .op1=0xE7, .rlvl=RLVL1, .mnemo="OUT", .ops={ { F_ADDR_I | F_OPERAND_B, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Output to Port */
	{ .op1=0xE8, .mnemo="CALL", .ops={ { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Call Procedure */
	{ .op1=0xE9, .mnemo="JMP", .ops={ { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, BRANCH, 0), },		/* DESCRIPTION=Jump */
	{ .op1=0xEA, },		/* DESCRIPTION=Invalid Instruction in 64-Bit Mode */
	{ .op1=0xEB, .mnemo="JMP", .ops={ { F_ADDR_J | F_OPERAND_BS, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, BRANCH, 0), },		/* DESCRIPTION=Jump */
	{ .op1=0xEC, .rlvl=RLVL1, .mnemo="IN", .ops={ { REG_8_AL, REG_16_DX, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Input from Port */
	{ .op1=0xED, .rlvl=RLVL1, .mnemo="IN", .ops={ { 0, REG_16_DX, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Input from Port */
	{ .op1=0xEE, .rlvl=RLVL1, .mnemo="OUT", .ops={ { REG_16_DX, REG_8_AL, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Output to Port */
	{ .op1=0xEF, .rlvl=RLVL1, .mnemo="OUT", .ops={ { REG_16_DX, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Output to Port */
	{ .pfx=0xF0, .mnemo="LOCK", },		/* DESCRIPTION=Assert LOCK# Signal Prefix */
	{ .op1=0xF1, },		/* DESCRIPTION=Undefined and Reserved; Does not Generate #UD */
	{ .op1=0xF1, .ops=(instr_fop[2]){.mnemo="INT1 part alias10", { F_ADDR_F | F_OPERAND_V, 0, 0, 0 }, .mnemo="ICEBP part alias10", { F_ADDR_F | F_OPERAND_V, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Call to Interrupt Procedure */
	{ .pfx=0xF2, .ops=(instr_fop[2]){.mnemo="REPNZ", { REG_ANY_RCX, 0, 0, 0 }, .mnemo="REPNE", { REG_ANY_RCX, 0, 0, 0 }, }, .opnum=2, },		/* DESCRIPTION=Repeat String Operation Prefix */
	{ .pfx=0xF2, .mnemo="REP", .ops={ { REG_ANY_RCX, 0, 0, 0 }, }, .opnum=1, },		/* DESCRIPTION=Repeat String Operation Prefix */
	{ .pfx=0xF2, },		/* DESCRIPTION=Scalar Double-precision Prefix */
	{ .pfx=0xF3, .ops=(instr_fop[2]){.mnemo="REPZ", { REG_ANY_RCX, 0, 0, 0 }, .mnemo="REPE", { REG_ANY_RCX, 0, 0, 0 }, }, .opnum=2, },		/* DESCRIPTION=Repeat String Operation Prefix */
	{ .pfx=0xF3, .mnemo="REP", .ops={ { REG_ANY_RCX, 0, 0, 0 }, }, .opnum=1, },		/* DESCRIPTION=Repeat String Operation Prefix */
	{ .pfx=0xF3, },		/* DESCRIPTION=Scalar Single-precision Prefix */
	{ .op1=0xF4, .mnemo="HLT", .grp=GRP(SYSTEM, 0, 0), },		/* DESCRIPTION=Halt */
	{ .op1=0xF5, .mnemo="CMC", .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Complement Carry Flag */
	{ .op1=0xF6, .reg_op=0xb, .mnemo="TEST", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Compare */
	{ .op1=0xF6, .reg_op=1, .mnemo="TEST alias", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Compare */
	{ .op1=0xF6, .reg_op=2, .x=X_LOCK, .mnemo="NOT", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=One's Complement Negation */
	{ .op1=0xF6, .reg_op=3, .x=X_LOCK, .mnemo="NEG", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Two's Complement Negation */
	{ .op1=0xF6, .reg_op=4, .mnemo="MUL", .ops={ { REG_16_AX, REG_8_AL, F_ADDR_E | F_OPERAND_B, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Unsigned Multiply */
	{ .op1=0xF6, .reg_op=5, .mnemo="IMUL", .ops={ { REG_16_AX, REG_8_AL, F_ADDR_E | F_OPERAND_B, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Signed Multiply */
	{ .op1=0xF6, .reg_op=6, .mnemo="DIV", .ops={ { REG_8_AL, REG_8_AH, REG_16_AX, F_ADDR_E | F_OPERAND_B }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Unsigned Divide */
	{ .op1=0xF6, .reg_op=7, .mnemo="IDIV", .ops={ { REG_8_AL, REG_8_AH, REG_16_AX, F_ADDR_E | F_OPERAND_B }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Signed Divide */
	{ .op1=0xF7, .reg_op=0xb, .mnemo="TEST", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Compare */
	{ .op1=0xF7, .reg_op=1, .mnemo="TEST alias", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_VDS, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=Logical Compare */
	{ .op1=0xF7, .reg_op=2, .x=X_LOCK, .mnemo="NOT", .ops={ { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, LOGICAL, 0), },		/* DESCRIPTION=One's Complement Negation */
	{ .op1=0xF7, .reg_op=3, .x=X_LOCK, .mnemo="NEG", .ops={ { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Two's Complement Negation */
	{ .op1=0xF7, .reg_op=4, .mnemo="MUL", .ops={ { REG_ANY_RDX, REG_ANY_RAX, F_ADDR_E | F_OPERAND_VQP, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Unsigned Multiply */
	{ .op1=0xF7, .reg_op=5, .mnemo="IMUL", .ops={ { REG_ANY_RDX, REG_ANY_RAX, F_ADDR_E | F_OPERAND_VQP, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Signed Multiply */
	{ .op1=0xF7, .reg_op=6, .mnemo="DIV", .ops={ { REG_ANY_RDX, REG_ANY_RAX, F_ADDR_E | F_OPERAND_VQP, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Unsigned Divide */
	{ .op1=0xF7, .reg_op=7, .mnemo="IDIV", .ops={ { REG_ANY_RDX, REG_ANY_RAX, F_ADDR_E | F_OPERAND_VQP, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Signed Divide */
	{ .op1=0xF8, .mnemo="CLC", .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Clear Carry Flag */
	{ .op1=0xF9, .mnemo="STC", .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Set Carry Flag */
	{ .op1=0xFA, .rlvl=RLVL1, .mnemo="CLI", .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Clear Interrupt Flag */
	{ .op1=0xFB, .rlvl=RLVL1, .mnemo="STI", .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Set Interrupt Flag */
	{ .op1=0xFC, .mnemo="CLD", .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Clear Direction Flag */
	{ .op1=0xFD, .mnemo="STD", .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Set Direction Flag */
	{ .op1=0xFE, .reg_op=0xb, .x=X_LOCK, .mnemo="INC", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Increment by 1 */
	{ .op1=0xFE, .reg_op=1, .x=X_LOCK, .mnemo="DEC", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Decrement by 1 */
	{ .op1=0xFF, .reg_op=0xb, .x=X_LOCK, .mnemo="INC", .ops={ { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Increment by 1 */
	{ .op1=0xFF, .reg_op=1, .x=X_LOCK, .mnemo="DEC", .ops={ { F_ADDR_E | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY), },		/* DESCRIPTION=Decrement by 1 */
	{ .op1=0xFF, .reg_op=2, .mnemo="CALL", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Call Procedure */
	{ .op1=0xFF, .reg_op=2, .mnemo="CALL", .ops={ { F_ADDR_E | F_OPERAND_Q, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Call Procedure */
	{ .op1=0xFF, .reg_op=3, .mnemo="CALLF", .ops={ { F_ADDR_M | F_OPERAND_PTP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Call Procedure */
	{ .op1=0xFF, .reg_op=4, .mnemo="JMP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, BRANCH, 0), },		/* DESCRIPTION=Jump */
	{ .op1=0xFF, .reg_op=4, .mnemo="JMP", .ops={ { F_ADDR_E | F_OPERAND_Q, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, BRANCH, 0), },		/* DESCRIPTION=Jump */
	{ .op1=0xFF, .reg_op=5, .mnemo="JMPF", .ops={ { F_ADDR_M | F_OPERAND_PTP, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, BRANCH, 0), },		/* DESCRIPTION=Jump */
	{ .op1=0xFF, .reg_op=6, .mnemo="PUSH", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 }, }, .opnum=1, .grp=GRP(GEN, 0, 0), },		/* DESCRIPTION=Push Word, Doubleword or Quadword Onto the Stack */

	/**DESCRIPTION=
	 * Two byte instr
	**/

	{ .tbyte=0x0f, .op1=0x00, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="SLDT", { F_ADDR_M | F_OPERAND_W, 0, 0, 0 }, .mnemo="SLDT", { F_ADDR_R | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=2, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Store Local DESCRIPTIONriptor Table Register */
	{ .tbyte=0x0f, .op1=0x00, .reg_op=1, .ops=(instr_fop[2]){.mnemo="STR", { F_ADDR_M | F_OPERAND_W, 0, 0, 0 }, .mnemo="STR", { F_ADDR_R | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=2, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Store Task Register */
	{ .tbyte=0x0f, .op1=0x00, .reg_op=2, .mnemo="LLDT", .ops={ { 0, F_ADDR_E | F_OPERAND_W, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Load Local DESCRIPTIONriptor Table Register */
	{ .tbyte=0x0f, .op1=0x00, .reg_op=3, .mnemo="LTR", .ops={ { 0, F_ADDR_E | F_OPERAND_W, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Load Task Register */
	{ .tbyte=0x0f, .op1=0x00, .reg_op=4, .mnemo="VERR", .ops={ { F_ADDR_E | F_OPERAND_W, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Verify a Segment for Reading */
	{ .tbyte=0x0f, .op1=0x00, .reg_op=5, .mnemo="VERW", .ops={ { F_ADDR_E | F_OPERAND_W, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Verify a Segment for Writing */
	{ .tbyte=0x0f, .op1=0x00, .reg_op=6, .mnemo="JMPE", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, BRANCH, 0),  },		/* DESCRIPTION=Jump to IA-64 Instruction Set */
	{ .tbyte=0x0f, .op1=0x01, .reg_op=0xb, .mnemo="SGDT", .ops={ { F_ADDR_M | F_OPERAND_S, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Store Global DESCRIPTIONriptor Table Register */
	{ .tbyte=0x0f, .op1=0x01, .op2=0xC1, .reg_op=0xb, .mnemo="VMCALL", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Call to VM Monitor */
	{ .tbyte=0x0f, .op1=0x01, .op2=0xC2, .reg_op=0xb, .mnemo="VMLAUNCH", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Launch Virtual Machine */
	{ .tbyte=0x0f, .op1=0x01, .op2=0xC3, .reg_op=0xb, .mnemo="VMRESUME", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Resume Virtual Machine */
	{ .tbyte=0x0f, .op1=0x01, .op2=0xC4, .reg_op=0xb, .mnemo="VMXOFF", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Leave VMX Operation */
	{ .tbyte=0x0f, .op1=0x01, .reg_op=1, .mnemo="SIDT", .ops={ { F_ADDR_M | F_OPERAND_S, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Store Interrupt DESCRIPTIONriptor Table Register */
	{ .tbyte=0x0f, .op1=0x01, .op2=0xC8, .reg_op=1, .mnemo="MONITOR", .ops={ { F_ADDR_BA | F_OPERAND_B, REG_16_ECX, REG_16_EDX, 0 },  }, .opnum=1, .grp=GRP(SYNC, 0, 0),  },		/* DESCRIPTION=Set Up Monitor Address */
	{ .tbyte=0x0f, .op1=0x01, .op2=0xC9, .reg_op=1, .mnemo="MWAIT", .ops={ { REG_16_EAX, REG_32_ECX, 0, 0 },  }, .opnum=1, .grp=GRP(SYNC, 0, 0),  },		/* DESCRIPTION=Monitor Wait */
	{ .tbyte=0x0f, .op1=0x01, .reg_op=2, .mnemo="LGDT", .ops={ { 0, F_ADDR_M | F_OPERAND_S, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Load Global DESCRIPTIONriptor Table Register */
	{ .tbyte=0x0f, .op1=0x01, .op2=0xD0, .reg_op=2, .mnemo="XGETBV", .ops={ { REG_16_EDX, REG_16_EAX, REG_16_ECX, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Get Value of Extended Control Register */
	{ .tbyte=0x0f, .op1=0x01, .op2=0xD1, .reg_op=2, .mnemo="XSETBV", .ops={ { 0, REG_16_ECX, REG_16_EDX, REG_16_EAX },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Set Extended Control Register */
	{ .tbyte=0x0f, .op1=0x01, .reg_op=3, .mnemo="LIDT", .ops={ { 0, F_ADDR_M | F_OPERAND_S, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Load Interrupt DESCRIPTIONriptor Table Register */
	{ .tbyte=0x0f, .op1=0x01, .reg_op=4, .ops=(instr_fop[2]){.mnemo="SMSW", { F_ADDR_M | F_OPERAND_W, 0, 0, 0 }, .mnemo="SMSW", { F_ADDR_R | F_OPERAND_VQP, 0, 0, 0 }, }, .opnum=2, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Store Machine Status Word */
	{ .tbyte=0x0f, .op1=0x01, .reg_op=6, .mnemo="LMSW", .ops={ { 0, F_ADDR_E | F_OPERAND_W, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Load Machine Status Word */
	{ .tbyte=0x0f, .op1=0x01, .reg_op=7, .mnemo="INVLPG", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Invalidate TLB Entry */
	{ .tbyte=0x0f, .op1=0x01, .op2=0xF8, .reg_op=7, .mnemo="SWAPGS", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Swap GS Base Register */
	{ .tbyte=0x0f, .op1=0x01, .op2=0xF9, .reg_op=7, .rlvl=RLVL2, .mnemo="RDTSCP", .ops={ { REG_16_EAX, REG_16_EDX, REG_16_ECX, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Read Time-Stamp Counter and Processor ID */
	{ .tbyte=0x0f, .op1=0x02, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="LAR", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_M | F_OPERAND_W, 0, 0 }, .mnemo="LAR", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_R | F_OPERAND_V, 0, 0 }, }, .opnum=2, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Load Access Rights Byte */
	{ .tbyte=0x0f, .op1=0x03, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="LSL", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_M | F_OPERAND_W, 0, 0 }, .mnemo="LSL", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_R | F_OPERAND_V, 0, 0 }, }, .opnum=2, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Load Segment Limit */
	{ .tbyte=0x0f, .op1=0x05, .mnemo="SYSCALL", .ops={ { REG_16_RCX, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, BRANCH, 0),  },		/* DESCRIPTION=Fast System Call */
	{ .tbyte=0x0f, .op1=0x06, .mnemo="CLTS", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Clear Task-Switched Flag in CR0 */
	{ .tbyte=0x0f, .op1=0x07, .mnemo="SYSRET", .ops={ { 0, F_ADDR_F | F_OPERAND_D, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, BRANCH, TRANS),  },		/* DESCRIPTION=Return From Fast System Call */
	{ .tbyte=0x0f, .op1=0x08, .mnemo="INVD", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Invalidate Internal Caches */
	{ .tbyte=0x0f, .op1=0x09, .mnemo="WBINVD", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Write Back and Invalidate Cache */
	{ .tbyte=0x0f, .op1=0x0B, .mnemo="UD2", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Undefined Instruction */
	{ .tbyte=0x0f, .op1=0x0D, .mnemo="NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=No Operation */
	{ .tbyte=0x0f, .op1=0x10, .reg_op=0xf, .mnemo="MOVUPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Unaligned Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x10, .reg_op=0xf, .mnemo="MOVSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Scalar Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x10, .reg_op=0xf, .mnemo="MOVUPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, DATAMOV, 0),  },		/* DESCRIPTION=Move Unaligned Packed Double-FP Value */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x10, .reg_op=0xf, .mnemo="MOVSD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, DATAMOV, 0),  },		/* DESCRIPTION=Move Scalar Double-FP Value */
	{ .tbyte=0x0f, .op1=0x11, .reg_op=0xf, .mnemo="MOVUPS", .ops={ { F_ADDR_W | F_OPERAND_PS, F_ADDR_V | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Unaligned Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x11, .reg_op=0xf, .mnemo="MOVSS", .ops={ { F_ADDR_W | F_OPERAND_SS, F_ADDR_V | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Scalar Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x11, .reg_op=0xf, .mnemo="MOVUPD", .ops={ { F_ADDR_W | F_OPERAND_PD, F_ADDR_V | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, DATAMOV, 0),  },		/* DESCRIPTION=Move Unaligned Packed Double-FP Values */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x11, .reg_op=0xf, .mnemo="MOVSD", .ops={ { F_ADDR_W | F_OPERAND_SD, F_ADDR_V | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, DATAMOV, 0),  },		/* DESCRIPTION=Move Scalar Double-FP Value */
	{ .tbyte=0x0f, .op1=0x12, .reg_op=0xf, .mnemo="MOVHLPS", .ops={ { F_ADDR_V | F_OPERAND_Q, F_ADDR_U | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Packed Single-FP Values High to Low */
	{ .tbyte=0x0f, .op1=0x12, .reg_op=0xf, .mnemo="MOVLPS", .ops={ { F_ADDR_V | F_OPERAND_Q, F_ADDR_M | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Low Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x12, .reg_op=0xf, .mnemo="MOVLPD", .ops={ { F_ADDR_V | F_OPERAND_Q, F_ADDR_M | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, DATAMOV, 0),  },		/* DESCRIPTION=Move Low Packed Double-FP Value */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x12, .reg_op=0xf, .mnemo="MOVDDUP", .ops={ { F_ADDR_V | F_OPERAND_Q, F_ADDR_W | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move One Double-FP and Duplicate */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x12, .reg_op=0xf, .mnemo="MOVSLDUP", .ops={ { F_ADDR_V | F_OPERAND_Q, F_ADDR_W | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Packed Single-FP Low and Duplicate */
	{ .tbyte=0x0f, .op1=0x13, .reg_op=0xf, .mnemo="MOVLPS", .ops={ { F_ADDR_M | F_OPERAND_Q, F_ADDR_V | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Low Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x13, .reg_op=0xf, .mnemo="MOVLPD", .ops={ { F_ADDR_M | F_OPERAND_Q, F_ADDR_V | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, DATAMOV, 0),  },		/* DESCRIPTION=Move Low Packed Double-FP Value */
	{ .tbyte=0x0f, .op1=0x14, .reg_op=0xf, .mnemo="UNPCKLPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack and Interleave Low Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x14, .reg_op=0xf, .mnemo="UNPCKLPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack and Interleave Low Packed Double-FP Values */
	{ .tbyte=0x0f, .op1=0x15, .reg_op=0xf, .mnemo="UNPCKHPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack and Interleave High Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x15, .reg_op=0xf, .mnemo="UNPCKHPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack and Interleave High Packed Double-FP Values */
	{ .tbyte=0x0f, .op1=0x16, .reg_op=0xf, .mnemo="MOVLHPS", .ops={ { F_ADDR_V | F_OPERAND_Q, F_ADDR_U | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Packed Single-FP Values Low to High */
	{ .tbyte=0x0f, .op1=0x16, .reg_op=0xf, .mnemo="MOVHPS", .ops={ { F_ADDR_V | F_OPERAND_Q, F_ADDR_M | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move High Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x16, .reg_op=0xf, .mnemo="MOVHPD", .ops={ { F_ADDR_V | F_OPERAND_Q, F_ADDR_M | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, DATAMOV, 0),  },		/* DESCRIPTION=Move High Packed Double-FP Value */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x16, .reg_op=0xf, .mnemo="MOVSHDUP", .ops={ { F_ADDR_V | F_OPERAND_Q, F_ADDR_W | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Packed Single-FP High and Duplicate */
	{ .tbyte=0x0f, .op1=0x17, .reg_op=0xf, .mnemo="MOVHPS", .ops={ { F_ADDR_M | F_OPERAND_Q, F_ADDR_V | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move High Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x17, .reg_op=0xf, .mnemo="MOVHPD", .ops={ { F_ADDR_M | F_OPERAND_Q, F_ADDR_V | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, DATAMOV, 0),  },		/* DESCRIPTION=Move High Packed Double-FP Value */
	{ .tbyte=0x0f, .op1=0x18, .reg_op=0xb, .mnemo="PREFETCHNTA", .ops={ { F_ADDR_M | F_OPERAND_B, 0, 0, 0 },  }, .opnum=1, .grp=GRP(FETCH, 0, 0),  },		/* DESCRIPTION=Prefetch Data Into Caches */
	{ .tbyte=0x0f, .op1=0x18, .reg_op=1, .mnemo="PREFETCHT0", .ops={ { F_ADDR_M | F_OPERAND_B, 0, 0, 0 },  }, .opnum=1, .grp=GRP(FETCH, 0, 0),  },		/* DESCRIPTION=Prefetch Data Into Caches */
	{ .tbyte=0x0f, .op1=0x18, .reg_op=2, .mnemo="PREFETCHT1", .ops={ { F_ADDR_M | F_OPERAND_B, 0, 0, 0 },  }, .opnum=1, .grp=GRP(FETCH, 0, 0),  },		/* DESCRIPTION=Prefetch Data Into Caches */
	{ .tbyte=0x0f, .op1=0x18, .reg_op=3, .mnemo="PREFETCHT2", .ops={ { F_ADDR_M | F_OPERAND_B, 0, 0, 0 },  }, .opnum=1, .grp=GRP(FETCH, 0, 0),  },		/* DESCRIPTION=Prefetch Data Into Caches */
	{ .tbyte=0x0f, .op1=0x18, .reg_op=4, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x18, .reg_op=5, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x18, .reg_op=6, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x18, .reg_op=7, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x19, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1A, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1B, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1C, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1D, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1E, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1F, .reg_op=0xb, .mnemo="NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=No Operation */
	{ .tbyte=0x0f, .op1=0x1F, .reg_op=1, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1F, .reg_op=2, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1F, .reg_op=3, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1F, .reg_op=4, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1F, .reg_op=5, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1F, .reg_op=6, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x1F, .reg_op=7, .mnemo="HINT_NOP", .ops={ { F_ADDR_E | F_OPERAND_V, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Hintable NOP */
	{ .tbyte=0x0f, .op1=0x20, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_R | F_OPERAND_Q, F_ADDR_C | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Move to/from Control Registers */
	{ .tbyte=0x0f, .op1=0x20, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_H | F_OPERAND_Q, F_ADDR_C | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Move to/from Control Registers */
	{ .tbyte=0x0f, .op1=0x21, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_R | F_OPERAND_Q, F_ADDR_D | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Move to/from Debug Registers */
	{ .tbyte=0x0f, .op1=0x21, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_H | F_OPERAND_Q, F_ADDR_D | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Move to/from Debug Registers */
	{ .tbyte=0x0f, .op1=0x22, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_C | F_OPERAND_Q, F_ADDR_R | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Move to/from Control Registers */
	{ .tbyte=0x0f, .op1=0x22, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_C | F_OPERAND_Q, F_ADDR_H | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Move to/from Control Registers */
	{ .tbyte=0x0f, .op1=0x23, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_D | F_OPERAND_Q, F_ADDR_R | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Move to/from Debug Registers */
	{ .tbyte=0x0f, .op1=0x23, .reg_op=0xf, .mnemo="MOV", .ops={ { F_ADDR_D | F_OPERAND_Q, F_ADDR_H | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Move to/from Debug Registers */
	{ .tbyte=0x0f, .op1=0x28, .reg_op=0xf, .mnemo="MOVAPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Aligned Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x28, .reg_op=0xf, .mnemo="MOVAPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, DATAMOV, 0),  },		/* DESCRIPTION=Move Aligned Packed Double-FP Values */
	{ .tbyte=0x0f, .op1=0x29, .reg_op=0xf, .mnemo="MOVAPS", .ops={ { F_ADDR_W | F_OPERAND_PS, F_ADDR_V | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Move Aligned Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x29, .reg_op=0xf, .mnemo="MOVAPD", .ops={ { F_ADDR_W | F_OPERAND_PD, F_ADDR_V | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, DATAMOV, 0),  },		/* DESCRIPTION=Move Aligned Packed Double-FP Values */
	{ .tbyte=0x0f, .op1=0x2A, .reg_op=0xf, .mnemo="CVTPI2PS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_Q | F_OPERAND_PI, 0, 0 },  }, .opnum=1, .grp=GRP(CONVER, 0, 0),  },		/* DESCRIPTION=Convert Packed DW Integers to Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x2A, .reg_op=0xf, .mnemo="CVTSI2SS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_E | F_OPERAND_DQP, 0, 0 },  }, .opnum=1, .grp=GRP(CONVER, 0, 0),  },		/* DESCRIPTION=Convert DW Integer to Scalar Single-FP Value */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x2A, .reg_op=0xf, .mnemo="CVTPI2PD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_Q | F_OPERAND_PI, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert Packed DW Integers to Double-FP Values */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x2A, .reg_op=0xf, .mnemo="CVTSI2SD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_E | F_OPERAND_DQP, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert DW Integer to Scalar Double-FP Value */
	{ .tbyte=0x0f, .op1=0x2B, .reg_op=0xf, .mnemo="MOVNTPS", .ops={ { F_ADDR_M | F_OPERAND_PS, F_ADDR_V | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(CACHECT, 0, 0),  },		/* DESCRIPTION=Store Packed Single-FP Values Using Non-Temporal Hint */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x2B, .reg_op=0xf, .mnemo="MOVNTPD", .ops={ { F_ADDR_M | F_OPERAND_PD, F_ADDR_V | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(CACHECT, 0, 0),  },		/* DESCRIPTION=Store Packed Double-FP Values Using Non-Temporal Hint */
	{ .tbyte=0x0f, .op1=0x2C, .reg_op=0xf, .mnemo="CVTTPS2PI", .ops={ { F_ADDR_P | F_OPERAND_PI, F_ADDR_W | F_OPERAND_PSQ, 0, 0 },  }, .opnum=1, .grp=GRP(CONVER, 0, 0),  },		/* DESCRIPTION=Convert with Trunc. Packed Single-FP Values to DW Integers */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x2C, .reg_op=0xf, .mnemo="CVTTSS2SI", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(CONVER, 0, 0),  },		/* DESCRIPTION=Convert with Trunc. Scalar Single-FP Value to DW Integer */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x2C, .reg_op=0xf, .mnemo="CVTTPD2PI", .ops={ { F_ADDR_P | F_OPERAND_PI, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert with Trunc. Packed Double-FP Values to DW Integers */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x2C, .reg_op=0xf, .mnemo="CVTTSD2SI", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Conv. with Trunc. Scalar Double-FP Value to Signed DW Int */
	{ .tbyte=0x0f, .op1=0x2D, .reg_op=0xf, .mnemo="CVTPS2PI", .ops={ { F_ADDR_P | F_OPERAND_PI, F_ADDR_W | F_OPERAND_PSQ, 0, 0 },  }, .opnum=1, .grp=GRP(CONVER, 0, 0),  },		/* DESCRIPTION=Convert Packed Single-FP Values to DW Integers */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x2D, .reg_op=0xf, .mnemo="CVTSS2SI", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(CONVER, 0, 0),  },		/* DESCRIPTION=Convert Scalar Single-FP Value to DW Integer */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x2D, .reg_op=0xf, .mnemo="CVTPD2PI", .ops={ { F_ADDR_P | F_OPERAND_PI, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert Packed Double-FP Values to DW Integers */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x2D, .reg_op=0xf, .mnemo="CVTSD2SI", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert Scalar Double-FP Value to DW Integer */
	{ .tbyte=0x0f, .op1=0x2E, .reg_op=0xf, .mnemo="UCOMISS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, COMPAR, 0),  },		/* DESCRIPTION=Unordered Compare Scalar Single-FP Values and Set EFLAGS */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x2E, .reg_op=0xf, .mnemo="UCOMISD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, COMPAR, 0),  },		/* DESCRIPTION=Unordered Compare Scalar Double-FP Values and Set EFLAGS */
	{ .tbyte=0x0f, .op1=0x2F, .reg_op=0xf, .mnemo="COMISS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, COMPAR, 0),  },		/* DESCRIPTION=Compare Scalar Ordered Single-FP Values and Set EFLAGS */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x2F, .reg_op=0xf, .mnemo="COMISD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, COMPAR, 0),  },		/* DESCRIPTION=Compare Scalar Ordered Double-FP Values and Set EFLAGS */
	{ .tbyte=0x0f, .op1=0x30, .mnemo="WRMSR", .ops={ { 0, REG_ANY_RCX, REG_ANY_RAX, REG_ANY_RDX },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Write to Model Specific Register */
	{ .tbyte=0x0f, .op1=0x31, .rlvl=RLVL2, .mnemo="RDTSC", .ops={ { REG_32_EAX, REG_16_EDX, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Read Time-Stamp Counter */
	{ .tbyte=0x0f, .op1=0x32, .mnemo="RDMSR", .ops={ { REG_ANY_RAX, REG_ANY_RDX, REG_ANY_RCX, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Read from Model Specific Register */
	{ .tbyte=0x0f, .op1=0x33, .rlvl=RLVL3, .mnemo="RDPMC", .ops={ { REG_32_EAX, REG_16_EDX, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Read Performance-Monitoring Counters */
	{ .tbyte=0x0f, .op1=0x34, .mnemo="SYSENTER", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, BRANCH, 0),  },		/* DESCRIPTION=Fast System Call */
	{ .tbyte=0x0f, .op1=0x35, .mnemo="SYSEXIT", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, BRANCH, TRANS),  },		/* DESCRIPTION=Fast Return from Fast System Call */
	{ .tbyte=0x0f, .op1=0x37, .mnemo="GETSEC", .ops={ { REG_16_EAX, 0, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=GETSEC Leaf Functions */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x38, .op2=0x80, .reg_op=0xf, .mnemo="INVEPT", .ops={ { F_ADDR_G | F_OPERAND_Q, F_ADDR_M | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Invalidate Translations Derived from EPT */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x38, .op2=0x81, .reg_op=0xf, .mnemo="INVVPID", .ops={ { F_ADDR_G | F_OPERAND_Q, F_ADDR_M | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Invalidate Translations Based on VPID */
	{ .tbyte=0x0f, .op1=0x38, .op2=0xF0, .reg_op=0xf, .mnemo="MOVBE", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_M | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Move Data After Swapping Bytes */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x38, .op2=0xF0, .reg_op=0xf, .mnemo="CRC32", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_E | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Accumulate CRC32 Value */
	{ .tbyte=0x0f, .op1=0x38, .op2=0xF1, .reg_op=0xf, .mnemo="MOVBE", .ops={ { F_ADDR_M | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Move Data After Swapping Bytes */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x38, .op2=0xF1, .reg_op=0xf, .mnemo="CRC32", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Accumulate CRC32 Value */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x08, .reg_op=0xf, .mnemo="ROUNDPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, CONVER, 0),  },		/* DESCRIPTION=Round Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x09, .reg_op=0xf, .mnemo="ROUNDPD", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PD, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, CONVER, 0),  },		/* DESCRIPTION=Round Packed Double-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x0A, .reg_op=0xf, .mnemo="ROUNDSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, CONVER, 0),  },		/* DESCRIPTION=Round Scalar Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x0B, .reg_op=0xf, .mnemo="ROUNDSD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, CONVER, 0),  },		/* DESCRIPTION=Round Scalar Double-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x0C, .reg_op=0xf, .mnemo="BLENDPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Blend Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x0D, .reg_op=0xf, .mnemo="BLENDPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Blend Packed Double-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x0E, .reg_op=0xf, .mnemo="PBLENDW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Blend Packed Words */
	{ .tbyte=0x0f, .op1=0x3A, .op2=0x0F, .reg_op=0xf, .mnemo="PALIGNR", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Packed Align Right */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x0F, .reg_op=0xf, .mnemo="PALIGNR", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Packed Align Right */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x14, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="PEXTRB", { F_ADDR_M | F_OPERAND_B, F_ADDR_V | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 }, .mnemo="PEXTRB", { F_ADDR_R | F_OPERAND_DQP, F_ADDR_V | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 }, }, .opnum=2, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Extract Byte */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x15, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="PEXTRW", { F_ADDR_M | F_OPERAND_W, F_ADDR_V | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 }, .mnemo="PEXTRW", { F_ADDR_R | F_OPERAND_DQP, F_ADDR_V | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 }, }, .opnum=2, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Extract Word */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x16, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="PEXTRD", { F_ADDR_E | F_OPERAND_D, F_ADDR_V | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 }, .mnemo="PEXTRQ", { F_ADDR_E | F_OPERAND_QP, F_ADDR_V | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 }, }, .opnum=2, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Extract Dword/Qword */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x17, .reg_op=0xf, .mnemo="EXTRACTPS", .ops={ { F_ADDR_E | F_OPERAND_D, F_ADDR_V | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Extract Packed Single-FP Value */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x20, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="PINSRB", { F_ADDR_V | F_OPERAND_DQ, F_ADDR_M | F_OPERAND_B, F_ADDR_I | F_OPERAND_B, 0 }, .mnemo="PINSRB", { F_ADDR_V | F_OPERAND_DQ, F_ADDR_R | F_OPERAND_DQP, F_ADDR_I | F_OPERAND_B, 0 }, }, .opnum=2, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Insert Byte */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x21, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="INSERTPS", { F_ADDR_V | F_OPERAND_PS, F_ADDR_M | F_OPERAND_D, F_ADDR_I | F_OPERAND_B, 0 }, .mnemo="INSERTPS", { F_ADDR_V | F_OPERAND_PS, F_ADDR_U | F_OPERAND_PS, F_ADDR_I | F_OPERAND_B, 0 }, }, .opnum=2, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Insert Packed Single-FP Value */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x22, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="PINSRD", { F_ADDR_V | F_OPERAND_DQ, F_ADDR_E | F_OPERAND_D, F_ADDR_I | F_OPERAND_B, 0 }, .mnemo="PINSRQ", { F_ADDR_V | F_OPERAND_DQ, F_ADDR_E | F_OPERAND_QP, F_ADDR_I | F_OPERAND_B, 0 }, }, .opnum=2, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Insert Dword/Qword */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x40, .reg_op=0xf, .mnemo="DPPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Dot Product of Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x41, .reg_op=0xf, .mnemo="DPPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Dot Product of Packed Double-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x42, .reg_op=0xf, .mnemo="MPSADBW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Compute Multiple Packed Sums of Absolute Difference */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x60, .reg_op=0xf, .mnemo="PCMPESTRM", .ops={ { 0, F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0 },  }, .opnum=1, .grp=GRP(STRTXT, 0, 0),  },		/* DESCRIPTION=Packed Compare Explicit Length Strings, Return Mask */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x61, .reg_op=0xf, .mnemo="PCMPESTRI", .ops={ { REG_ANY_RCX, F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0 },  }, .opnum=1, .grp=GRP(STRTXT, 0, 0),  },		/* DESCRIPTION=Packed Compare Explicit Length Strings, Return Index */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x62, .reg_op=0xf, .mnemo="PCMPISTRM", .ops={ { 0, F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B },  }, .opnum=1, .grp=GRP(STRTXT, 0, 0),  },		/* DESCRIPTION=Packed Compare Implicit Length Strings, Return Mask */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x3A, .op2=0x63, .reg_op=0xf, .mnemo="PCMPISTRI", .ops={ { REG_ANY_RCX, F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B },  }, .opnum=1, .grp=GRP(STRTXT, 0, 0),  },		/* DESCRIPTION=Packed Compare Implicit Length Strings, Return Index */
	{ .tbyte=0x0f, .op1=0x40, .reg_op=0xf, .mnemo="CMOVO", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - overflow (OF=1) */
	{ .tbyte=0x0f, .op1=0x41, .reg_op=0xf, .mnemo="CMOVNO", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - not overflow (OF=0) */
	{ .tbyte=0x0f, .op1=0x42, .reg_op=0xf, .ops=(instr_fop[3]){.mnemo="CMOVB", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVNAE", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVC", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=3, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - below/not above or equal/carry (CF=1) */
	{ .tbyte=0x0f, .op1=0x43, .reg_op=0xf, .ops=(instr_fop[3]){.mnemo="CMOVNB", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVAE", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVNC", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=3, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - not below/above or equal/not carry (CF=0) */
	{ .tbyte=0x0f, .op1=0x44, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="CMOVZ", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVE", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - zero/equal (ZF=1) */
	{ .tbyte=0x0f, .op1=0x45, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="CMOVNZ", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVNE", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - not zero/not equal (ZF=0) */
	{ .tbyte=0x0f, .op1=0x46, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="CMOVBE", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVNA", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - below or equal/not above (CF=1 OR ZF=1) */
	{ .tbyte=0x0f, .op1=0x47, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="CMOVNBE", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVA", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - not below or equal/above (CF=0 AND ZF=0) */
	{ .tbyte=0x0f, .op1=0x48, .reg_op=0xf, .mnemo="CMOVS", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - sign (SF=1) */
	{ .tbyte=0x0f, .op1=0x49, .reg_op=0xf, .mnemo="CMOVNS", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - not sign (SF=0) */
	{ .tbyte=0x0f, .op1=0x4A, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="CMOVP", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVPE", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - parity/parity even (PF=1) */
	{ .tbyte=0x0f, .op1=0x4B, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="CMOVNP", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVPO", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - not parity/parity odd (PF=0) */
	{ .tbyte=0x0f, .op1=0x4C, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="CMOVL", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVNGE", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - less/not greater (SF!=OF) */
	{ .tbyte=0x0f, .op1=0x4D, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="CMOVNL", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVGE", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - not less/greater or equal (SF=OF) */
	{ .tbyte=0x0f, .op1=0x4E, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="CMOVLE", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVNG", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - less or equal/not greater ((ZF=1) OR (SF!=OF)) */
	{ .tbyte=0x0f, .op1=0x4F, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="CMOVNLE", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, .mnemo="CMOVG", { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Conditional Move - not less nor equal/greater ((ZF=0) AND (SF=OF)) */
	{ .tbyte=0x0f, .op1=0x50, .reg_op=0xf, .mnemo="MOVMSKPS", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_U | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, DATAMOV, 0),  },		/* DESCRIPTION=Extract Packed Single-FP Sign Mask */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x50, .reg_op=0xf, .mnemo="MOVMSKPD", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_U | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, DATAMOV, 0),  },		/* DESCRIPTION=Extract Packed Double-FP Sign Mask */
	{ .tbyte=0x0f, .op1=0x51, .reg_op=0xf, .mnemo="SQRTPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Compute Square Roots of Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x51, .reg_op=0xf, .mnemo="SQRTSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Compute Square Root of Scalar Single-FP Value */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x51, .reg_op=0xf, .mnemo="SQRTPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Compute Square Roots of Packed Double-FP Values */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x51, .reg_op=0xf, .mnemo="SQRTSD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Compute Square Root of Scalar Double-FP Value */
	{ .tbyte=0x0f, .op1=0x52, .reg_op=0xf, .mnemo="RSQRTPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Compute Recipr. of Square Roots of Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x52, .reg_op=0xf, .mnemo="RSQRTSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Compute Recipr. of Square Root of Scalar Single-FP Value */
	{ .tbyte=0x0f, .op1=0x53, .reg_op=0xf, .mnemo="RCPPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Compute Reciprocals of Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x53, .reg_op=0xf, .mnemo="RCPSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Compute Reciprocal of Scalar Single-FP Values */
	{ .tbyte=0x0f, .op1=0x54, .reg_op=0xf, .mnemo="ANDPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, LOGICAL, 0),  },		/* DESCRIPTION=Bitwise Logical AND of Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x54, .reg_op=0xf, .mnemo="ANDPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, LOGICAL, 0),  },		/* DESCRIPTION=Bitwise Logical AND of Packed Double-FP Values */
	{ .tbyte=0x0f, .op1=0x55, .reg_op=0xf, .mnemo="ANDNPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, LOGICAL, 0),  },		/* DESCRIPTION=Bitwise Logical AND NOT of Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x55, .reg_op=0xf, .mnemo="ANDNPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, LOGICAL, 0),  },		/* DESCRIPTION=Bitwise Logical AND NOT of Packed Double-FP Values */
	{ .tbyte=0x0f, .op1=0x56, .reg_op=0xf, .mnemo="ORPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, LOGICAL, 0),  },		/* DESCRIPTION=Bitwise Logical OR of Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x56, .reg_op=0xf, .mnemo="ORPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, LOGICAL, 0),  },		/* DESCRIPTION=Bitwise Logical OR of Double-FP Values */
	{ .tbyte=0x0f, .op1=0x57, .reg_op=0xf, .mnemo="XORPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, LOGICAL, 0),  },		/* DESCRIPTION=Bitwise Logical XOR for Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x57, .reg_op=0xf, .mnemo="XORPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, LOGICAL, 0),  },		/* DESCRIPTION=Bitwise Logical XOR for Double-FP Values */
	{ .tbyte=0x0f, .op1=0x58, .reg_op=0xf, .mnemo="ADDPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Add Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x58, .reg_op=0xf, .mnemo="ADDSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Add Scalar Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x58, .reg_op=0xf, .mnemo="ADDPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Add Packed Double-FP Values */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x58, .reg_op=0xf, .mnemo="ADDSD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Add Scalar Double-FP Values */
	{ .tbyte=0x0f, .op1=0x59, .reg_op=0xf, .mnemo="MULPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Multiply Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x59, .reg_op=0xf, .mnemo="MULSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Multiply Scalar Single-FP Value */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x59, .reg_op=0xf, .mnemo="MULPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Multiply Packed Double-FP Values */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x59, .reg_op=0xf, .mnemo="MULSD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Multiply Scalar Double-FP Values */
	{ .tbyte=0x0f, .op1=0x5A, .reg_op=0xf, .mnemo="CVTPS2PD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert Packed Single-FP Values to Double-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x5A, .reg_op=0xf, .mnemo="CVTPD2PS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert Packed Double-FP Values to Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x5A, .reg_op=0xf, .mnemo="CVTSS2SD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert Scalar Single-FP Value to Scalar Double-FP Value */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x5A, .reg_op=0xf, .mnemo="CVTSD2SS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert Scalar Double-FP Value to Scalar Single-FP Value */
	{ .tbyte=0x0f, .op1=0x5B, .reg_op=0xf, .mnemo="CVTDQ2PS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSP, 0, 0),  },		/* DESCRIPTION=Convert Packed DW Integers to Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x5B, .reg_op=0xf, .mnemo="CVTPS2DQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSP, 0, 0),  },		/* DESCRIPTION=Convert Packed Single-FP Values to DW Integers */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x5B, .reg_op=0xf, .mnemo="CVTTPS2DQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSP, 0, 0),  },		/* DESCRIPTION=Convert with Trunc. Packed Single-FP Values to DW Integers */
	{ .tbyte=0x0f, .op1=0x5C, .reg_op=0xf, .mnemo="SUBPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Subtract Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x5C, .reg_op=0xf, .mnemo="SUBSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Subtract Scalar Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x5C, .reg_op=0xf, .mnemo="SUBPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Subtract Packed Double-FP Values */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x5C, .reg_op=0xf, .mnemo="SUBSD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Subtract Scalar Double-FP Values */
	{ .tbyte=0x0f, .op1=0x5D, .reg_op=0xf, .mnemo="MINPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Return Minimum Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x5D, .reg_op=0xf, .mnemo="MINSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Return Minimum Scalar Single-FP Value */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x5D, .reg_op=0xf, .mnemo="MINPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Return Minimum Packed Double-FP Values */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x5D, .reg_op=0xf, .mnemo="MINSD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Return Minimum Scalar Double-FP Value */
	{ .tbyte=0x0f, .op1=0x5E, .reg_op=0xf, .mnemo="DIVPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Divide Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x5E, .reg_op=0xf, .mnemo="DIVSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Divide Scalar Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x5E, .reg_op=0xf, .mnemo="DIVPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Divide Packed Double-FP Values */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x5E, .reg_op=0xf, .mnemo="DIVSD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Divide Scalar Double-FP Values */
	{ .tbyte=0x0f, .op1=0x5F, .reg_op=0xf, .mnemo="MAXPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Return Maximum Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x5F, .reg_op=0xf, .mnemo="MAXSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Return Maximum Scalar Single-FP Value */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x5F, .reg_op=0xf, .mnemo="MAXPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Return Maximum Packed Double-FP Values */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x5F, .reg_op=0xf, .mnemo="MAXSD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, ARITH, 0),  },		/* DESCRIPTION=Return Maximum Scalar Double-FP Value */
	{ .tbyte=0x0f, .op1=0x60, .reg_op=0xf, .mnemo="PUNPCKLBW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_D, 0, 0 },  }, .opnum=1, .grp=GRP(UNPACK, 0, 0),  },		/* DESCRIPTION=Unpack Low Data */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x60, .reg_op=0xf, .mnemo="PUNPCKLBW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack Low Data */
	{ .tbyte=0x0f, .op1=0x61, .reg_op=0xf, .mnemo="PUNPCKLWD", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_D, 0, 0 },  }, .opnum=1, .grp=GRP(UNPACK, 0, 0),  },		/* DESCRIPTION=Unpack Low Data */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x61, .reg_op=0xf, .mnemo="PUNPCKLWD", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack Low Data */
	{ .tbyte=0x0f, .op1=0x62, .reg_op=0xf, .mnemo="PUNPCKLDQ", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_D, 0, 0 },  }, .opnum=1, .grp=GRP(UNPACK, 0, 0),  },		/* DESCRIPTION=Unpack Low Data */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x62, .reg_op=0xf, .mnemo="PUNPCKLDQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack Low Data */
	{ .tbyte=0x0f, .op1=0x63, .reg_op=0xf, .mnemo="PACKSSWB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_D, 0, 0 },  }, .opnum=1, .grp=GRP(CONVER, 0, 0),  },		/* DESCRIPTION=Pack with Signed Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x63, .reg_op=0xf, .mnemo="PACKSSWB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, CONVER, 0),  },		/* DESCRIPTION=Pack with Signed Saturation */
	{ .tbyte=0x0f, .op1=0x64, .reg_op=0xf, .mnemo="PCMPGTB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_D, 0, 0 },  }, .opnum=1, .grp=GRP(COMPAR, 0, 0),  },		/* DESCRIPTION=Compare Packed Signed Integers for Greater Than */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x64, .reg_op=0xf, .mnemo="PCMPGTB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, COMPAR, 0),  },		/* DESCRIPTION=Compare Packed Signed Integers for Greater Than */
	{ .tbyte=0x0f, .op1=0x65, .reg_op=0xf, .mnemo="PCMPGTW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_D, 0, 0 },  }, .opnum=1, .grp=GRP(COMPAR, 0, 0),  },		/* DESCRIPTION=Compare Packed Signed Integers for Greater Than */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x65, .reg_op=0xf, .mnemo="PCMPGTW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, COMPAR, 0),  },		/* DESCRIPTION=Compare Packed Signed Integers for Greater Than */
	{ .tbyte=0x0f, .op1=0x66, .reg_op=0xf, .mnemo="PCMPGTD", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_D, 0, 0 },  }, .opnum=1, .grp=GRP(COMPAR, 0, 0),  },		/* DESCRIPTION=Compare Packed Signed Integers for Greater Than */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x66, .reg_op=0xf, .mnemo="PCMPGTD", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, COMPAR, 0),  },		/* DESCRIPTION=Compare Packed Signed Integers for Greater Than */
	{ .tbyte=0x0f, .op1=0x67, .reg_op=0xf, .mnemo="PACKUSWB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(CONVER, 0, 0),  },		/* DESCRIPTION=Pack with Unsigned Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x67, .reg_op=0xf, .mnemo="PACKUSWB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, CONVER, 0),  },		/* DESCRIPTION=Pack with Unsigned Saturation */
	{ .tbyte=0x0f, .op1=0x68, .reg_op=0xf, .mnemo="PUNPCKHBW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(UNPACK, 0, 0),  },		/* DESCRIPTION=Unpack High Data */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x68, .reg_op=0xf, .mnemo="PUNPCKHBW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack High Data */
	{ .tbyte=0x0f, .op1=0x69, .reg_op=0xf, .mnemo="PUNPCKHWD", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(UNPACK, 0, 0),  },		/* DESCRIPTION=Unpack High Data */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x69, .reg_op=0xf, .mnemo="PUNPCKHWD", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack High Data */
	{ .tbyte=0x0f, .op1=0x6A, .reg_op=0xf, .mnemo="PUNPCKHDQ", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(UNPACK, 0, 0),  },		/* DESCRIPTION=Unpack High Data */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x6A, .reg_op=0xf, .mnemo="PUNPCKHDQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack High Data */
	{ .tbyte=0x0f, .op1=0x6B, .reg_op=0xf, .mnemo="PACKSSDW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(CONVER, 0, 0),  },		/* DESCRIPTION=Pack with Signed Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x6B, .reg_op=0xf, .mnemo="PACKSSDW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, CONVER, 0),  },		/* DESCRIPTION=Pack with Signed Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x6C, .reg_op=0xf, .mnemo="PUNPCKLQDQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack Low Data */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x6D, .reg_op=0xf, .mnemo="PUNPCKHQDQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHUNPCK, 0),  },		/* DESCRIPTION=Unpack High Data */
	{ .tbyte=0x0f, .op1=0x6E, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="MOVD", { F_ADDR_P | F_OPERAND_Q, F_ADDR_E | F_OPERAND_D, 0, 0 }, .mnemo="MOVQ", { F_ADDR_P | F_OPERAND_Q, F_ADDR_E | F_OPERAND_QP, 0, 0 }, }, .opnum=2, .grp=GRP(DATAMOV, 0, 0),  },		/* DESCRIPTION=Move Doubleword/Quadword */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x6E, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="MOVD", { F_ADDR_V | F_OPERAND_DQ, F_ADDR_E | F_OPERAND_D, 0, 0 }, .mnemo="MOVQ", { F_ADDR_V | F_OPERAND_DQ, F_ADDR_E | F_OPERAND_QP, 0, 0 }, }, .opnum=2, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Move Doubleword/Quadword */
	{ .tbyte=0x0f, .op1=0x6F, .reg_op=0xf, .mnemo="MOVQ", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(DATAMOV, 0, 0),  },		/* DESCRIPTION=Move Quadword */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x6F, .reg_op=0xf, .mnemo="MOVDQA", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Move Aligned Double Quadword */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x6F, .reg_op=0xf, .mnemo="MOVDQU", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Move Unaligned Double Quadword */
	{ .tbyte=0x0f, .op1=0x70, .reg_op=0xf, .mnemo="PSHUFW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Shuffle Packed Words */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x70, .reg_op=0xf, .mnemo="PSHUFLW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHUNPCK, 0),  },		/* DESCRIPTION=Shuffle Packed Low Words */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x70, .reg_op=0xf, .mnemo="PSHUFHW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHUNPCK, 0),  },		/* DESCRIPTION=Shuffle Packed High Words */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x70, .reg_op=0xf, .mnemo="PSHUFD", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHUNPCK, 0),  },		/* DESCRIPTION=Shuffle Packed Doublewords */
	{ .tbyte=0x0f, .op1=0x71, .reg_op=2, .mnemo="PSRLW", .ops={ { F_ADDR_N | F_OPERAND_Q, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x71, .reg_op=2, .mnemo="PSRLW", .ops={ { F_ADDR_U | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Logical */
	{ .tbyte=0x0f, .op1=0x71, .reg_op=4, .mnemo="PSRAW", .ops={ { F_ADDR_N | F_OPERAND_Q, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Arithmetic */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x71, .reg_op=4, .mnemo="PSRAW", .ops={ { F_ADDR_U | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Arithmetic */
	{ .tbyte=0x0f, .op1=0x71, .reg_op=6, .mnemo="PSLLW", .ops={ { F_ADDR_N | F_OPERAND_Q, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x71, .reg_op=6, .mnemo="PSLLW", .ops={ { F_ADDR_U | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .tbyte=0x0f, .op1=0x72, .reg_op=2, .mnemo="PSRLD", .ops={ { F_ADDR_N | F_OPERAND_Q, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Double Quadword Right Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x72, .reg_op=2, .mnemo="PSRLD", .ops={ { F_ADDR_U | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Double Quadword Right Logical */
	{ .tbyte=0x0f, .op1=0x72, .reg_op=4, .mnemo="PSRAD", .ops={ { F_ADDR_N | F_OPERAND_Q, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Arithmetic */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x72, .reg_op=4, .mnemo="PSRAD", .ops={ { F_ADDR_U | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Arithmetic */
	{ .tbyte=0x0f, .op1=0x72, .reg_op=6, .mnemo="PSLLD", .ops={ { F_ADDR_N | F_OPERAND_Q, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x72, .reg_op=6, .mnemo="PSLLD", .ops={ { F_ADDR_U | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .tbyte=0x0f, .op1=0x73, .reg_op=2, .mnemo="PSRLQ", .ops={ { F_ADDR_N | F_OPERAND_Q, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x73, .reg_op=2, .mnemo="PSRLQ", .ops={ { F_ADDR_U | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x73, .reg_op=3, .mnemo="PSRLDQ", .ops={ { F_ADDR_U | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHIFT, 0),  },		/* DESCRIPTION=Shift Double Quadword Right Logical */
	{ .tbyte=0x0f, .op1=0x73, .reg_op=6, .mnemo="PSLLQ", .ops={ { F_ADDR_N | F_OPERAND_Q, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x73, .reg_op=6, .mnemo="PSLLQ", .ops={ { F_ADDR_U | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x73, .reg_op=7, .mnemo="PSLLDQ", .ops={ { F_ADDR_U | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHIFT, 0),  },		/* DESCRIPTION=Shift Double Quadword Left Logical */
	{ .tbyte=0x0f, .op1=0x74, .reg_op=0xf, .mnemo="PCMPEQB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(COMPAR, 0, 0),  },		/* DESCRIPTION=Compare Packed Data for Equal */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x74, .reg_op=0xf, .mnemo="PCMPEQB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, COMPAR, 0),  },		/* DESCRIPTION=Compare Packed Data for Equal */
	{ .tbyte=0x0f, .op1=0x75, .reg_op=0xf, .mnemo="PCMPEQW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(COMPAR, 0, 0),  },		/* DESCRIPTION=Compare Packed Data for Equal */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x75, .reg_op=0xf, .mnemo="PCMPEQW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, COMPAR, 0),  },		/* DESCRIPTION=Compare Packed Data for Equal */
	{ .tbyte=0x0f, .op1=0x76, .reg_op=0xf, .mnemo="PCMPEQD", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(COMPAR, 0, 0),  },		/* DESCRIPTION=Compare Packed Data for Equal */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x76, .reg_op=0xf, .mnemo="PCMPEQD", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, COMPAR, 0),  },		/* DESCRIPTION=Compare Packed Data for Equal */
	{ .tbyte=0x0f, .op1=0x77, .mnemo="EMMS", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(X87FPU, CONTROL, 0),  },		/* DESCRIPTION=Empty MMX Technology State */
	{ .tbyte=0x0f, .op1=0x78, .reg_op=0xf, .mnemo="VMREAD", .ops={ { F_ADDR_E | F_OPERAND_Q, F_ADDR_G | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Read Field from Virtual-Machine Control Structure */
	{ .tbyte=0x0f, .op1=0x79, .reg_op=0xf, .mnemo="VMWRITE", .ops={ { F_ADDR_G | F_OPERAND_Q, F_ADDR_E | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Write Field to Virtual-Machine Control Structure */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x7C, .reg_op=0xf, .mnemo="HADDPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Packed Double-FP Horizontal Add */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x7C, .reg_op=0xf, .mnemo="HADDPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Packed Single-FP Horizontal Add */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x7D, .reg_op=0xf, .mnemo="HSUBPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Packed Double-FP Horizontal Subtract */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0x7D, .reg_op=0xf, .mnemo="HSUBPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Packed Single-FP Horizontal Subtract */
	{ .tbyte=0x0f, .op1=0x7E, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="MOVD", { F_ADDR_E | F_OPERAND_D, F_ADDR_P | F_OPERAND_Q, 0, 0 }, .mnemo="MOVQ", { F_ADDR_E | F_OPERAND_QP, F_ADDR_P | F_OPERAND_Q, 0, 0 }, }, .opnum=2, .grp=GRP(DATAMOV, 0, 0),  },		/* DESCRIPTION=Move Doubleword/Quadword */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x7E, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="MOVD", { F_ADDR_E | F_OPERAND_D, F_ADDR_V | F_OPERAND_DQ, 0, 0 }, .mnemo="MOVQ", { F_ADDR_E | F_OPERAND_QP, F_ADDR_V | F_OPERAND_DQ, 0, 0 }, }, .opnum=2, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Move Doubleword/Quadword */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x7E, .reg_op=0xf, .mnemo="MOVQ", .ops={ { F_ADDR_V | F_OPERAND_Q, F_ADDR_W | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Move Quadword */
	{ .tbyte=0x0f, .op1=0x7F, .reg_op=0xf, .mnemo="MOVQ", .ops={ { F_ADDR_Q | F_OPERAND_Q, F_ADDR_P | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(DATAMOV, 0, 0),  },		/* DESCRIPTION=Move Quadword */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0x7F, .reg_op=0xf, .mnemo="MOVDQA", .ops={ { F_ADDR_W | F_OPERAND_DQ, F_ADDR_V | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Move Aligned Double Quadword */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0x7F, .reg_op=0xf, .mnemo="MOVDQU", .ops={ { F_ADDR_W | F_OPERAND_DQ, F_ADDR_V | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Move Unaligned Double Quadword */
	{ .tbyte=0x0f, .op1=0x80, .mnemo="JO", .ops={ { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if overflow (OF=1) */
	{ .tbyte=0x0f, .op1=0x81, .mnemo="JNO", .ops={ { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if not overflow (OF=0) */
	{ .tbyte=0x0f, .op1=0x82, .ops=(instr_fop[3]){.mnemo="JB", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JNAE", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JC", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=3, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if below/not above or equal/carry (CF=1) */
	{ .tbyte=0x0f, .op1=0x83, .ops=(instr_fop[3]){.mnemo="JNB", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JAE", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JNC", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=3, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if not below/above or equal/not carry (CF=0) */
	{ .tbyte=0x0f, .op1=0x84, .ops=(instr_fop[2]){.mnemo="JZ", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JE", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if zero/equal (ZF=1) */
	{ .tbyte=0x0f, .op1=0x85, .ops=(instr_fop[2]){.mnemo="JNZ", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JNE", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if not zero/not equal (ZF=0) */
	{ .tbyte=0x0f, .op1=0x86, .ops=(instr_fop[2]){.mnemo="JBE", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JNA", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if below or equal/not above (CF=1 OR ZF=1) */
	{ .tbyte=0x0f, .op1=0x87, .ops=(instr_fop[2]){.mnemo="JNBE", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JA", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if not below or equal/above (CF=0 AND ZF=0) */
	{ .tbyte=0x0f, .op1=0x88, .mnemo="JS", .ops={ { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if sign (SF=1) */
	{ .tbyte=0x0f, .op1=0x89, .mnemo="JNS", .ops={ { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if not sign (SF=0) */
	{ .tbyte=0x0f, .op1=0x8A, .ops=(instr_fop[2]){.mnemo="JP", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JPE", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if parity/parity even (PF=1) */
	{ .tbyte=0x0f, .op1=0x8B, .ops=(instr_fop[2]){.mnemo="JNP", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JPO", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if not parity/parity odd (PF=0) */
	{ .tbyte=0x0f, .op1=0x8C, .ops=(instr_fop[2]){.mnemo="JL", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JNGE", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if less/not greater (SF!=OF) */
	{ .tbyte=0x0f, .op1=0x8D, .ops=(instr_fop[2]){.mnemo="JNL", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JGE", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if not less/greater or equal (SF=OF) */
	{ .tbyte=0x0f, .op1=0x8E, .ops=(instr_fop[2]){.mnemo="JLE", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JNG", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if less or equal/not greater ((ZF=1) OR (SF!=OF)) */
	{ .tbyte=0x0f, .op1=0x8F, .ops=(instr_fop[2]){.mnemo="JNLE", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, .mnemo="JG", { F_ADDR_J | F_OPERAND_VDS, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, BRANCH, COND),  },		/* DESCRIPTION=Jump near if not less nor equal/greater ((ZF=0) AND (SF=OF)) */
	{ .tbyte=0x0f, .op1=0x90, .reg_op=0xb, .mnemo="SETO", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - overflow (OF=1) */
	{ .tbyte=0x0f, .op1=0x91, .reg_op=0xb, .mnemo="SETNO", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - not overflow (OF=0) */
	{ .tbyte=0x0f, .op1=0x92, .reg_op=0xb, .ops=(instr_fop[3]){.mnemo="SETB", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETNAE", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETC", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=3, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - below/not above or equal/carry (CF=1) */
	{ .tbyte=0x0f, .op1=0x93, .reg_op=0xb, .ops=(instr_fop[3]){.mnemo="SETNB", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETAE", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETNC", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=3, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - not below/above or equal/not carry (CF=0) */
	{ .tbyte=0x0f, .op1=0x94, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="SETZ", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETE", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - zero/equal (ZF=1) */
	{ .tbyte=0x0f, .op1=0x95, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="SETNZ", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETNE", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - not zero/not equal (ZF=0) */
	{ .tbyte=0x0f, .op1=0x96, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="SETBE", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETNA", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - below or equal/not above (CF=1 OR ZF=1) */
	{ .tbyte=0x0f, .op1=0x97, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="SETNBE", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETA", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - not below or equal/above (CF=0 AND ZF=0) */
	{ .tbyte=0x0f, .op1=0x98, .reg_op=0xb, .mnemo="SETS", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - sign (SF=1) */
	{ .tbyte=0x0f, .op1=0x99, .reg_op=0xb, .mnemo="SETNS", .ops={ { F_ADDR_E | F_OPERAND_B, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - not sign (SF=0) */
	{ .tbyte=0x0f, .op1=0x9A, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="SETP", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETPE", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - parity/parity even (PF=1) */
	{ .tbyte=0x0f, .op1=0x9B, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="SETNP", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETPO", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - not parity/parity odd (PF=0) */
	{ .tbyte=0x0f, .op1=0x9C, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="SETL", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETNGE", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - less/not greater (SF!=OF) */
	{ .tbyte=0x0f, .op1=0x9D, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="SETNL", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETGE", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - not less/greater or equal (SF=OF) */
	{ .tbyte=0x0f, .op1=0x9E, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="SETLE", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETNG", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - less or equal/not greater ((ZF=1) OR (SF!=OF)) */
	{ .tbyte=0x0f, .op1=0x9F, .reg_op=0xb, .ops=(instr_fop[2]){.mnemo="SETNLE", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, .mnemo="SETG", { F_ADDR_E | F_OPERAND_B, 0, 0, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Set Byte on Condition - not less nor equal/greater ((ZF=0) AND (SF=OF)) */
	{ .tbyte=0x0f, .op1=0xA0, .mnemo="PUSH", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, 0, 0),  },		/* DESCRIPTION=Push Word, Doubleword or Quadword Onto the Stack */
	{ .tbyte=0x0f, .op1=0xA1, .mnemo="POP", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, 0, 0),  },		/* DESCRIPTION=Pop a Value from the Stack */
	{ .tbyte=0x0f, .op1=0xA2, .mnemo="CPUID", .ops={ { 0, REG_16_EAX, REG_16_ECX, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=CPU Identification */
	{ .tbyte=0x0f, .op1=0xA3, .reg_op=0xf, .mnemo="BT", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BIT, 0),  },		/* DESCRIPTION=Bit Test */
	{ .tbyte=0x0f, .op1=0xA4, .reg_op=0xf, .mnemo="SHLD", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0),  },		/* DESCRIPTION=Double Precision Shift Left */
	{ .tbyte=0x0f, .op1=0xA5, .reg_op=0xf, .mnemo="SHLD", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, REG_8_CL, 0 },  }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0),  },		/* DESCRIPTION=Double Precision Shift Left */
	{ .tbyte=0x0f, .op1=0xA8, .mnemo="PUSH", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, 0, 0),  },		/* DESCRIPTION=Push Word, Doubleword or Quadword Onto the Stack */
	{ .tbyte=0x0f, .op1=0xA9, .mnemo="POP", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, 0, 0),  },		/* DESCRIPTION=Pop a Value from the Stack */
	{ .tbyte=0x0f, .op1=0xAA, .mnemo="RSM", .ops={ { F_ADDR_F | F_OPERAND_W, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, BRANCH, 0),  },		/* DESCRIPTION=Resume from System Management Mode */
	{ .tbyte=0x0f, .op1=0xAB, .reg_op=0xf, .x=X_LOCK, .mnemo="BTS", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BIT, 0),  },		/* DESCRIPTION=Bit Test and Set */
	{ .tbyte=0x0f, .op1=0xAC, .reg_op=0xf, .mnemo="SHRD", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0),  },		/* DESCRIPTION=Double Precision Shift Right */
	{ .tbyte=0x0f, .op1=0xAD, .reg_op=0xf, .mnemo="SHRD", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, REG_8_CL, 0 },  }, .opnum=1, .grp=GRP(GEN, SHFTROT, 0),  },		/* DESCRIPTION=Double Precision Shift Right */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=0xb, .mnemo="FXSAVE", .ops={ { F_ADDR_M | F_OPERAND_STX, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SM, 0, 0),  },		/* DESCRIPTION=Save x87 FPU, MMX, XMM, and MXCSR State */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=0xb, .mnemo="FXSAVE", .ops={ { F_ADDR_M | F_OPERAND_STX, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SM, 0, 0),  },		/* DESCRIPTION=Save x87 FPU, MMX, XMM, and MXCSR State */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=1, .mnemo="FXRSTOR", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SM, 0, 0),  },		/* DESCRIPTION=Restore x87 FPU, MMX, XMM, and MXCSR State */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=1, .mnemo="FXRSTOR", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SM, 0, 0),  },		/* DESCRIPTION=Restore x87 FPU, MMX, XMM, and MXCSR State */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=2, .mnemo="LDMXCSR", .ops={ { F_ADDR_M | F_OPERAND_D, 0, 0, 0 },  }, .opnum=1, .grp=GRP(MXCSRSM, 0, 0),  },		/* DESCRIPTION=Load MXCSR Register */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=3, .mnemo="STMXCSR", .ops={ { F_ADDR_M | F_OPERAND_D, 0, 0, 0 },  }, .opnum=1, .grp=GRP(MXCSRSM, 0, 0),  },		/* DESCRIPTION=Store MXCSR Register State */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=4, .mnemo="XSAVE", .ops={ { 0, REG_16_EDX, REG_16_EAX, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Save Processor Extended States */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=4, .mnemo="XSAVE", .ops={ { 0, REG_16_EDX, REG_16_EAX, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Save Processor Extended States */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=5, .mnemo="LFENCE", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(ORDER, 0, 0),  },		/* DESCRIPTION=Load Fence */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=5, .mnemo="XRSTOR", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, 0, 0),  },		/* DESCRIPTION=Restore Processor Extended States */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=6, .mnemo="MFENCE", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(ORDER, 0, 0),  },		/* DESCRIPTION=Memory Fence */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=7, .mnemo="SFENCE", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(ORDER, 0, 0),  },		/* DESCRIPTION=Store Fence */
	{ .tbyte=0x0f, .op1=0xAE, .reg_op=7, .mnemo="CLFLUSH", .ops={ { F_ADDR_M | F_OPERAND_B, 0, 0, 0 },  }, .opnum=1, .grp=GRP(CACHECT, 0, 0),  },		/* DESCRIPTION=Flush Cache Line */
	{ .tbyte=0x0f, .op1=0xAF, .reg_op=0xf, .mnemo="IMUL", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, ARITH, BINARY),  },		/* DESCRIPTION=Signed Multiply */
	{ .tbyte=0x0f, .op1=0xB0, .reg_op=0xf, .x=X_LOCK, .mnemo="CMPXCHG", .ops={ { F_ADDR_E | F_OPERAND_B, REG_8_AL, F_ADDR_G | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV_ARITH, BINARY),  },		/* DESCRIPTION=Compare and Exchange */
	{ .tbyte=0x0f, .op1=0xB1, .reg_op=0xf, .x=X_LOCK, .mnemo="CMPXCHG", .ops={ { F_ADDR_E | F_OPERAND_VQP, REG_ANY_RAX, F_ADDR_G | F_OPERAND_VQP, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV_ARITH, BINARY),  },		/* DESCRIPTION=Compare and Exchange */
	{ .tbyte=0x0f, .op1=0xB2, .reg_op=0xf, .mnemo="LSS", .ops={ { 0, F_ADDR_G | F_OPERAND_VQP, F_ADDR_M | F_OPERAND_PTP, 0 },  }, .opnum=1, .grp=GRP(GEN, 0, 0),  },		/* DESCRIPTION=Load Far Pointer */
	{ .tbyte=0x0f, .op1=0xB3, .reg_op=0xf, .x=X_LOCK, .mnemo="BTR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BIT, 0),  },		/* DESCRIPTION=Bit Test and Reset */
	{ .tbyte=0x0f, .op1=0xB4, .reg_op=0xf, .mnemo="LFS", .ops={ { 0, F_ADDR_G | F_OPERAND_VQP, F_ADDR_M | F_OPERAND_PTP, 0 },  }, .opnum=1, .grp=GRP(GEN, 0, 0),  },		/* DESCRIPTION=Load Far Pointer */
	{ .tbyte=0x0f, .op1=0xB5, .reg_op=0xf, .mnemo="LGS", .ops={ { 0, F_ADDR_G | F_OPERAND_VQP, F_ADDR_M | F_OPERAND_PTP, 0 },  }, .opnum=1, .grp=GRP(GEN, 0, 0),  },		/* DESCRIPTION=Load Far Pointer */
	{ .tbyte=0x0f, .op1=0xB6, .reg_op=0xf, .mnemo="MOVZX", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONVER, 0),  },		/* DESCRIPTION=Move with Zero-Extend */
	{ .tbyte=0x0f, .op1=0xB7, .reg_op=0xf, .mnemo="MOVZX", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_W, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONVER, 0),  },		/* DESCRIPTION=Move with Zero-Extend */
	{ .tbyte=0x0f, .op1=0xB8, .mnemo="JMPE", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(SYSTEM, BRANCH, 0),  },		/* DESCRIPTION=Jump to IA-64 Instruction Set */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0xB8, .reg_op=0xf, .mnemo="POPCNT", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BIT, 0),  },		/* DESCRIPTION=Bit Population Count */
	{ .tbyte=0x0f, .op1=0xB9, .reg_op=0xf, .mnemo="UD", .ops={ { 0, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONTROL, 0),  },		/* DESCRIPTION=Undefined Instruction */
	{ .tbyte=0x0f, .op1=0xBA, .reg_op=4, .mnemo="BT", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BIT, 0),  },		/* DESCRIPTION=Bit Test */
	{ .tbyte=0x0f, .op1=0xBA, .reg_op=5, .x=X_LOCK, .mnemo="BTS", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BIT, 0),  },		/* DESCRIPTION=Bit Test and Set */
	{ .tbyte=0x0f, .op1=0xBA, .reg_op=6, .x=X_LOCK, .mnemo="BTR", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BIT, 0),  },		/* DESCRIPTION=Bit Test and Reset */
	{ .tbyte=0x0f, .op1=0xBA, .reg_op=7, .x=X_LOCK, .mnemo="BTC", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_I | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BIT, 0),  },		/* DESCRIPTION=Bit Test and Complement */
	{ .tbyte=0x0f, .op1=0xBB, .reg_op=0xf, .x=X_LOCK, .mnemo="BTC", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BIT, 0),  },		/* DESCRIPTION=Bit Test and Complement */
	{ .tbyte=0x0f, .op1=0xBC, .reg_op=0xf, .mnemo="BSF", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BIT, 0),  },		/* DESCRIPTION=Bit Scan Forward */
	{ .tbyte=0x0f, .op1=0xBD, .reg_op=0xf, .mnemo="BSR", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, BIT, 0),  },		/* DESCRIPTION=Bit Scan Reverse */
	{ .tbyte=0x0f, .op1=0xBE, .reg_op=0xf, .mnemo="MOVSX", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONVER, 0),  },		/* DESCRIPTION=Move with Sign-Extension */
	{ .tbyte=0x0f, .op1=0xBF, .reg_op=0xf, .mnemo="MOVSX", .ops={ { F_ADDR_G | F_OPERAND_VQP, F_ADDR_E | F_OPERAND_W, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, CONVER, 0),  },		/* DESCRIPTION=Move with Sign-Extension */
	{ .tbyte=0x0f, .op1=0xC0, .reg_op=0xf, .x=X_LOCK, .mnemo="XADD", .ops={ { F_ADDR_E | F_OPERAND_B, F_ADDR_G | F_OPERAND_B, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV_ARITH, BINARY),  },		/* DESCRIPTION=Exchange and Add */
	{ .tbyte=0x0f, .op1=0xC1, .reg_op=0xf, .x=X_LOCK, .mnemo="XADD", .ops={ { F_ADDR_E | F_OPERAND_VQP, F_ADDR_G | F_OPERAND_VQP, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV_ARITH, BINARY),  },		/* DESCRIPTION=Exchange and Add */
	{ .tbyte=0x0f, .op1=0xC2, .reg_op=0xf, .mnemo="CMPPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, COMPAR, 0),  },		/* DESCRIPTION=Compare Packed Single-FP Values */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0xC2, .reg_op=0xf, .mnemo="CMPSS", .ops={ { F_ADDR_V | F_OPERAND_SS, F_ADDR_W | F_OPERAND_SS, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, COMPAR, 0),  },		/* DESCRIPTION=Compare Scalar Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xC2, .reg_op=0xf, .mnemo="CMPPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, COMPAR, 0),  },		/* DESCRIPTION=Compare Packed Double-FP Values */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0xC2, .reg_op=0xf, .mnemo="CMPSD", .ops={ { F_ADDR_V | F_OPERAND_SD, F_ADDR_W | F_OPERAND_SD, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, COMPAR, 0),  },		/* DESCRIPTION=Compare Scalar Double-FP Values */
	{ .tbyte=0x0f, .op1=0xC3, .reg_op=0xf, .mnemo="MOVNTI", .ops={ { F_ADDR_M | F_OPERAND_DQP, F_ADDR_G | F_OPERAND_DQP, 0, 0 },  }, .opnum=1, .grp=GRP(CACHECT, 0, 0),  },		/* DESCRIPTION=Store Doubleword Using Non-Temporal Hint */
	{ .tbyte=0x0f, .op1=0xC4, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="PINSRW", { F_ADDR_P | F_OPERAND_Q, F_ADDR_R | F_OPERAND_DQP, F_ADDR_I | F_OPERAND_B, 0 }, .mnemo="PINSRW", { F_ADDR_P | F_OPERAND_Q, F_ADDR_M | F_OPERAND_W, F_ADDR_I | F_OPERAND_B, 0 }, }, .opnum=2, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Insert Word */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xC4, .reg_op=0xf, .ops=(instr_fop[2]){.mnemo="PINSRW", { F_ADDR_V | F_OPERAND_DQ, F_ADDR_R | F_OPERAND_DQP, F_ADDR_I | F_OPERAND_B, 0 }, .mnemo="PINSRW", { F_ADDR_V | F_OPERAND_DQ, F_ADDR_M | F_OPERAND_W, F_ADDR_I | F_OPERAND_B, 0 }, }, .opnum=2, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Insert Word */
	{ .tbyte=0x0f, .op1=0xC5, .reg_op=0xf, .mnemo="PEXTRW", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_N | F_OPERAND_Q, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Extract Word */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xC5, .reg_op=0xf, .mnemo="PEXTRW", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_U | F_OPERAND_DQ, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Extract Word */
	{ .tbyte=0x0f, .op1=0xC6, .reg_op=0xf, .mnemo="SHUFPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, SHUNPCK, 0),  },		/* DESCRIPTION=Shuffle Packed Single-FP Values */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xC6, .reg_op=0xf, .mnemo="SHUFPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, F_ADDR_I | F_OPERAND_B, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, SHUNPCK, 0),  },		/* DESCRIPTION=Shuffle Packed Double-FP Values */
	{ .tbyte=0x0f, .op1=0xC7, .reg_op=1, .x=X_LOCK, .mnemo="CMPXCHG8B", .ops={ { F_ADDR_M | F_OPERAND_Q, REG_16_EAX, REG_32_EDX, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV_ARITH, BINARY),  },		/* DESCRIPTION=Compare and Exchange Bytes */
	{ .tbyte=0x0f, .op1=0xC7, .reg_op=1, .x=X_LOCK, .ops=(instr_fop[2]){.mnemo="CMPXCHG8B", { F_ADDR_M | F_OPERAND_Q, REG_16_EAX, REG_32_EDX, 0 }, .mnemo="CMPXCHG16B", { F_ADDR_M | F_OPERAND_DQ, REG_16_RAX, REG_16_RDX, 0 }, }, .opnum=2, .grp=GRP(GEN, DATAMOV_ARITH, BINARY),  },		/* DESCRIPTION=Compare and Exchange Bytes */
	{ .tbyte=0x0f, .op1=0xC7, .reg_op=6, .mnemo="VMPTRLD", .ops={ { F_ADDR_M | F_OPERAND_Q, 0, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Load Pointer to Virtual-Machine Control Structure */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xC7, .reg_op=6, .mnemo="VMCLEAR", .ops={ { F_ADDR_M | F_OPERAND_Q, 0, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Clear Virtual-Machine Control Structure */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0xC7, .reg_op=6, .mnemo="VMXON", .ops={ { F_ADDR_M | F_OPERAND_Q, 0, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Enter VMX Operation */
	{ .tbyte=0x0f, .op1=0xC7, .reg_op=7, .mnemo="VMPTRST", .ops={ { F_ADDR_M | F_OPERAND_Q, 0, 0, 0 },  }, .opnum=1, .grp=GRP(0, 0, 0),  },		/* DESCRIPTION=Store Pointer to Virtual-Machine Control Structure */
	{ .tbyte=0x0f, .op1=0xC8, .flds=1, .mnemo="BSWAP", .ops={ { F_ADDR_Z | F_OPERAND_VQP, 0, 0, 0 },  }, .opnum=1, .grp=GRP(GEN, DATAMOV, 0),  },		/* DESCRIPTION=Byte Swap */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xD0, .reg_op=0xf, .mnemo="ADDSUBPD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Packed Double-FP Add/Subtract */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0xD0, .reg_op=0xf, .mnemo="ADDSUBPS", .ops={ { F_ADDR_V | F_OPERAND_PS, F_ADDR_W | F_OPERAND_PS, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDFP, ARITH, 0),  },		/* DESCRIPTION=Packed Single-FP Add/Subtract */
	{ .tbyte=0x0f, .op1=0xD1, .reg_op=0xf, .mnemo="PSRLW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xD1, .reg_op=0xf, .mnemo="PSRLW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHIFT, 0),  },		/* DESCRIPTION=Shift Packed Data Right Logical */
	{ .tbyte=0x0f, .op1=0xD2, .reg_op=0xf, .mnemo="PSRLD", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xD2, .reg_op=0xf, .mnemo="PSRLD", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHIFT, 0),  },		/* DESCRIPTION=Shift Packed Data Right Logical */
	{ .tbyte=0x0f, .op1=0xD3, .reg_op=0xf, .mnemo="PSRLQ", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xD3, .reg_op=0xf, .mnemo="PSRLQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHIFT, 0),  },		/* DESCRIPTION=Shift Packed Data Right Logical */
	{ .tbyte=0x0f, .op1=0xD4, .reg_op=0xf, .mnemo="PADDQ", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Add Packed Quadword Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xD4, .reg_op=0xf, .mnemo="PADDQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Add Packed Quadword Integers */
	{ .tbyte=0x0f, .op1=0xD5, .reg_op=0xf, .mnemo="PMULLW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Multiply Packed Signed Integers and Store Low Result */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xD5, .reg_op=0xf, .mnemo="PMULLW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Multiply Packed Signed Integers and Store Low Result */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xD6, .reg_op=0xf, .mnemo="MOVQ", .ops={ { F_ADDR_W | F_OPERAND_Q, F_ADDR_V | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Move Quadword */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0xD6, .reg_op=0xf, .mnemo="MOVQ2DQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_N | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Move Quadword from MMX Technology to XMM Register */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0xD6, .reg_op=0xf, .mnemo="MOVDQ2Q", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_U | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, DATAMOV, 0),  },		/* DESCRIPTION=Move Quadword from XMM to MMX Technology Register */
	{ .tbyte=0x0f, .op1=0xD7, .reg_op=0xf, .mnemo="PMOVMSKB", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_N | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Move Byte Mask */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xD7, .reg_op=0xf, .mnemo="PMOVMSKB", .ops={ { F_ADDR_G | F_OPERAND_DQP, F_ADDR_U | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Move Byte Mask */
	{ .tbyte=0x0f, .op1=0xD8, .reg_op=0xf, .mnemo="PSUBUSB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Subtract Packed Unsigned Integers with Unsigned Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xD8, .reg_op=0xf, .mnemo="PSUBUSB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Subtract Packed Unsigned Integers with Unsigned Saturation */
	{ .tbyte=0x0f, .op1=0xD9, .reg_op=0xf, .mnemo="PSUBUSW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Subtract Packed Unsigned Integers with Unsigned Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xD9, .reg_op=0xf, .mnemo="PSUBUSW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Subtract Packed Unsigned Integers with Unsigned Saturation */
	{ .tbyte=0x0f, .op1=0xDA, .reg_op=0xf, .mnemo="PMINUB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Minimum of Packed Unsigned Byte Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xDA, .reg_op=0xf, .mnemo="PMINUB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Minimum of Packed Unsigned Byte Integers */
	{ .tbyte=0x0f, .op1=0xDB, .reg_op=0xf, .mnemo="PAND", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_D, 0, 0 },  }, .opnum=1, .grp=GRP(LOGICAL, 0, 0),  },		/* DESCRIPTION=Logical AND */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xDB, .reg_op=0xf, .mnemo="PAND", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, LOGICAL, 0),  },		/* DESCRIPTION=Logical AND */
	{ .tbyte=0x0f, .op1=0xDC, .reg_op=0xf, .mnemo="PADDUSB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Add Packed Unsigned Integers with Unsigned Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xDC, .reg_op=0xf, .mnemo="PADDUSB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Add Packed Unsigned Integers with Unsigned Saturation */
	{ .tbyte=0x0f, .op1=0xDD, .reg_op=0xf, .mnemo="PADDUSW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Add Packed Unsigned Integers with Unsigned Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xDD, .reg_op=0xf, .mnemo="PADDUSW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Add Packed Unsigned Integers with Unsigned Saturation */
	{ .tbyte=0x0f, .op1=0xDE, .reg_op=0xf, .mnemo="PMAXUB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Maximum of Packed Unsigned Byte Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xDE, .reg_op=0xf, .mnemo="PMAXUB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Maximum of Packed Unsigned Byte Integers */
	{ .tbyte=0x0f, .op1=0xDF, .reg_op=0xf, .mnemo="PANDN", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(LOGICAL, 0, 0),  },		/* DESCRIPTION=Logical AND NOT */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xDF, .reg_op=0xf, .mnemo="PANDN", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, LOGICAL, 0),  },		/* DESCRIPTION=Logical AND NOT */
	{ .tbyte=0x0f, .op1=0xE0, .reg_op=0xf, .mnemo="PAVGB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Average Packed Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xE0, .reg_op=0xf, .mnemo="PAVGB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Average Packed Integers */
	{ .tbyte=0x0f, .op1=0xE1, .reg_op=0xf, .mnemo="PSRAW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Arithmetic */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xE1, .reg_op=0xf, .mnemo="PSRAW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHIFT, 0),  },		/* DESCRIPTION=Shift Packed Data Right Arithmetic */
	{ .tbyte=0x0f, .op1=0xE2, .reg_op=0xf, .mnemo="PSRAD", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Right Arithmetic */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xE2, .reg_op=0xf, .mnemo="PSRAD", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHIFT, 0),  },		/* DESCRIPTION=Shift Packed Data Right Arithmetic */
	{ .tbyte=0x0f, .op1=0xE3, .reg_op=0xf, .mnemo="PAVGW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Average Packed Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xE3, .reg_op=0xf, .mnemo="PAVGW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Average Packed Integers */
	{ .tbyte=0x0f, .op1=0xE4, .reg_op=0xf, .mnemo="PMULHUW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Multiply Packed Unsigned Integers and Store High Result */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xE4, .reg_op=0xf, .mnemo="PMULHUW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Multiply Packed Unsigned Integers and Store High Result */
	{ .tbyte=0x0f, .op1=0xE5, .reg_op=0xf, .mnemo="PMULHW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Multiply Packed Signed Integers and Store High Result */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xE5, .reg_op=0xf, .mnemo="PMULHW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Multiply Packed Signed Integers and Store High Result */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0xE6, .reg_op=0xf, .mnemo="CVTPD2DQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert Packed Double-FP Values to DW Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xE6, .reg_op=0xf, .mnemo="CVTTPD2DQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_PD, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert with Trunc. Packed Double-FP Values to DW Integers */
	{ .pfx=0xF3, .tbyte=0x0f, .op1=0xE6, .reg_op=0xf, .mnemo="CVTDQ2PD", .ops={ { F_ADDR_V | F_OPERAND_PD, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(PCKSCLR, CONVER, 0),  },		/* DESCRIPTION=Convert Packed DW Integers to Double-FP Values */
	{ .tbyte=0x0f, .op1=0xE7, .reg_op=0xf, .mnemo="MOVNTQ", .ops={ { F_ADDR_M | F_OPERAND_Q, F_ADDR_P | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(CACHECT, 0, 0),  },		/* DESCRIPTION=Store of Quadword Using Non-Temporal Hint */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xE7, .reg_op=0xf, .mnemo="MOVNTDQ", .ops={ { F_ADDR_M | F_OPERAND_DQ, F_ADDR_V | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(CACHECT, 0, 0),  },		/* DESCRIPTION=Store Double Quadword Using Non-Temporal Hint */
	{ .tbyte=0x0f, .op1=0xE8, .reg_op=0xf, .mnemo="PSUBSB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Subtract Packed Signed Integers with Signed Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xE8, .reg_op=0xf, .mnemo="PSUBSB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Subtract Packed Signed Integers with Signed Saturation */
	{ .tbyte=0x0f, .op1=0xE9, .reg_op=0xf, .mnemo="PSUBSW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Subtract Packed Signed Integers with Signed Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xE9, .reg_op=0xf, .mnemo="PSUBSW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Subtract Packed Signed Integers with Signed Saturation */
	{ .tbyte=0x0f, .op1=0xEA, .reg_op=0xf, .mnemo="PMINSW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Minimum of Packed Signed Word Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xEA, .reg_op=0xf, .mnemo="PMINSW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Minimum of Packed Signed Word Integers */
	{ .tbyte=0x0f, .op1=0xEB, .reg_op=0xf, .mnemo="POR", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(LOGICAL, 0, 0),  },		/* DESCRIPTION=Bitwise Logical OR */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xEB, .reg_op=0xf, .mnemo="POR", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, LOGICAL, 0),  },		/* DESCRIPTION=Bitwise Logical OR */
	{ .tbyte=0x0f, .op1=0xEC, .reg_op=0xf, .mnemo="PADDSB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Add Packed Signed Integers with Signed Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xEC, .reg_op=0xf, .mnemo="PADDSB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Add Packed Signed Integers with Signed Saturation */
	{ .tbyte=0x0f, .op1=0xED, .reg_op=0xf, .mnemo="PADDSW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Add Packed Signed Integers with Signed Saturation */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xED, .reg_op=0xf, .mnemo="PADDSW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Add Packed Signed Integers with Signed Saturation */
	{ .tbyte=0x0f, .op1=0xEE, .reg_op=0xf, .mnemo="PMAXSW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Maximum of Packed Signed Word Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xEE, .reg_op=0xf, .mnemo="PMAXSW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Maximum of Packed Signed Word Integers */
	{ .tbyte=0x0f, .op1=0xEF, .reg_op=0xf, .mnemo="PXOR", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(LOGICAL, 0, 0),  },		/* DESCRIPTION=Logical Exclusive OR */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xEF, .reg_op=0xf, .mnemo="PXOR", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, LOGICAL, 0),  },		/* DESCRIPTION=Logical Exclusive OR */
	{ .pfx=0xF2, .tbyte=0x0f, .op1=0xF0, .reg_op=0xf, .mnemo="LDDQU", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_M | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(CACHECT, 0, 0),  },		/* DESCRIPTION=Load Unaligned Integer 128 Bits */
	{ .tbyte=0x0f, .op1=0xF1, .reg_op=0xf, .mnemo="PSLLW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xF1, .reg_op=0xf, .mnemo="PSLLW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHIFT, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .tbyte=0x0f, .op1=0xF2, .reg_op=0xf, .mnemo="PSLLD", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xF2, .reg_op=0xf, .mnemo="PSLLD", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHIFT, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .tbyte=0x0f, .op1=0xF3, .reg_op=0xf, .mnemo="PSLLQ", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SHIFT, 0, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xF3, .reg_op=0xf, .mnemo="PSLLQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, SHIFT, 0),  },		/* DESCRIPTION=Shift Packed Data Left Logical */
	{ .tbyte=0x0f, .op1=0xF4, .reg_op=0xf, .mnemo="PMULUDQ", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Multiply Packed Unsigned DW Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xF4, .reg_op=0xf, .mnemo="PMULUDQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Multiply Packed Unsigned DW Integers */
	{ .tbyte=0x0f, .op1=0xF5, .reg_op=0xf, .mnemo="PMADDWD", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_D, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Multiply and Add Packed Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xF5, .reg_op=0xf, .mnemo="PMADDWD", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Multiply and Add Packed Integers */
	{ .tbyte=0x0f, .op1=0xF6, .reg_op=0xf, .mnemo="PSADBW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Compute Sum of Absolute Differences */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xF6, .reg_op=0xf, .mnemo="PSADBW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, 0, 0),  },		/* DESCRIPTION=Compute Sum of Absolute Differences */
	{ .tbyte=0x0f, .op1=0xF7, .reg_op=0xf, .mnemo="MASKMOVQ", .ops={ { F_ADDR_BD | F_OPERAND_Q, F_ADDR_P | F_OPERAND_Q, F_ADDR_N | F_OPERAND_Q, 0 },  }, .opnum=1, .grp=GRP(CACHECT, 0, 0),  },		/* DESCRIPTION=Store Selected Bytes of Quadword */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xF7, .reg_op=0xf, .mnemo="MASKMOVDQU", .ops={ { F_ADDR_BD | F_OPERAND_DQ, F_ADDR_V | F_OPERAND_DQ, F_ADDR_U | F_OPERAND_DQ, 0 },  }, .opnum=1, .grp=GRP(CACHECT, 0, 0),  },		/* DESCRIPTION=Store Selected Bytes of Double Quadword */
	{ .tbyte=0x0f, .op1=0xF8, .reg_op=0xf, .mnemo="PSUBB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Subtract Packed Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xF8, .reg_op=0xf, .mnemo="PSUBB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Subtract Packed Integers */
	{ .tbyte=0x0f, .op1=0xF9, .reg_op=0xf, .mnemo="PSUBW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Subtract Packed Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xF9, .reg_op=0xf, .mnemo="PSUBW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Subtract Packed Integers */
	{ .tbyte=0x0f, .op1=0xFA, .reg_op=0xf, .mnemo="PSUBD", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Subtract Packed Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xFA, .reg_op=0xf, .mnemo="PSUBD", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Subtract Packed Integers */
	{ .tbyte=0x0f, .op1=0xFB, .reg_op=0xf, .mnemo="PSUBQ", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Subtract Packed Quadword Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xFB, .reg_op=0xf, .mnemo="PSUBQ", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Subtract Packed Quadword Integers */
	{ .tbyte=0x0f, .op1=0xFC, .reg_op=0xf, .mnemo="PADDB", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Add Packed Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xFC, .reg_op=0xf, .mnemo="PADDB", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Add Packed Integers */
	{ .tbyte=0x0f, .op1=0xFD, .reg_op=0xf, .mnemo="PADDW", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Add Packed Integers */
	{ .pfx=0x66, .tbyte=0x0f, .op1=0xFD, .reg_op=0xf, .mnemo="PADDW", .ops={ { F_ADDR_V | F_OPERAND_DQ, F_ADDR_W | F_OPERAND_DQ, 0, 0 },  }, .opnum=1, .grp=GRP(SIMDINT, ARITH, 0),  },		/* DESCRIPTION=Add Packed Integers */
	{ .tbyte=0x0f, .op1=0xFE, .reg_op=0xf, .mnemo="PADDD", .ops={ { F_ADDR_P | F_OPERAND_Q, F_ADDR_Q | F_OPERAND_Q, 0, 0 },  }, .opnum=1, .grp=GRP(ARITH, 0, 0),  },		/* DESCRIPTION=Add Packed Integers */
};