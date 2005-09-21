/*
 * opcode.h
 * Opcode definitions/handling
 * Copyright (C) 2005 Christopher Han
 */
#ifndef OPCODE_H
#define OPCODE_H

#define TYPE_NULL 0
#define TYPE_R 1
#define TYPE_I 2
#define TYPE_J 3
#define TYPE_COPROC 4
#define TYPE_MEM 5

#define BITS5	0x1f		/* 0000000000000000000000011111 */
#define BITS6	0x3f		/* 0000000000000000000000111111 */
#define BITS16	0xffff		/* 0000000000001111111111111111 */
#define BITS26	0x3ffffff	/* 0011111111111111111111111111 */

#define OPCODE(i) ((i>>26)&BITS6)
#define RS(i) ((i>>21)&BITS5)
#define RT(i) ((i>>16)&BITS5)
#define RD(i) ((i>>11)&BITS5)
#define SHAMT(i) ((i>>6)&BITS5)
#define FUNCT(i) ((i)&BITS6)
#define IMMED(i) ((i)&BITS16)
#define ADDR(i) IMMED(i)
#define TARGET(i) ((i)&BITS26)

#define RTYPE(i) ((i)&0x3f==0x0)			/* opcode == 000000 */
#define JTYPE(i) ((i)&0x3e==0x2)			/* opcode == 00001x */
#define CTYPE(i) ((i)&0x3c==0x10)			/* opcode == 0100xx */
#define ITYPE(i) (!(RTYPE(i)||JTYPE(i)||CTYPE(i)))	/* everything else */

/*
 * R-Type instruction
 * 31-26: opcode - operation code (6 bits)
 * 25-21: rs - operand A register (5 bits)
 * 20-16: rt - operand B register (5 bits)
 * 15-11: rd - destination register (5 bits)
 * 10-6 : shamt - shift amount (5 bits)
 *  5-0 : funct - function code (6 bits)
 */
#define RTYPE_FUNC_ADD		0x20	/* add rd,rs,rt 100000 */
#define RTYPE_FUNC_ADDU		0x21	/* addu rd,rs,rt 100001 */
#define RTYPE_FUNC_AND		0x24	/* and rd,rs,rt 100100 */
#define RTYPE_FUNC_BREAK	0x0d	/* break	001101 */
#define RTYPE_FUNC_DIV		0x1a	/* div rs,rt	011010 */
#define RTYPE_FUNC_DIVU		0x1b	/* divu rs,rt	011011 */
#define RTYPE_FUNC_JALR		0x09	/* jalr rs,rt	001001 */
#define RTYPE_FUNC_JR		0x08	/* jr rs	001000 */
#define RTYPE_FUNC_MFHI		0x10	/* mfhi rd	010000 */
#define RTYPE_FUNC_MFLO		0x12	/* mflo rd	010010 */
#define RTYPE_FUNC_MTHI		0x11	/* mthi rs	010001 */
#define RTYPE_FUNC_MTLO		0x13	/* mtlo rs	010011 */
#define RTYPE_FUNC_MULT		0x18	/* mult rs,rt	011000 */
#define RTYPE_FUNC_MULTU	0x19	/* multu rs,rt	011001 */
#define RTYPE_FUNC_NOR		0x27	/* nor rd,rs,rt 100111 */
#define RTYPE_FUNC_OR		0x25	/* or rd,rs,rt	100101 */
#define RTYPE_FUNC_SLL		0x00	/* sll rd,rt,sa	000000 */
#define RTYPE_FUNC_SLLV		0x04	/* sllv rd,rt,rs 000100 */
#define RTYPE_FUNC_SLT		0x2a	/* slt rd,rs,rt 101010 */
#define RTYPE_FUNC_SLTU		0x2b	/* sltu rd,rs,rt 101011 */
#define RTYPE_FUNC_SRA		0x03	/* sra rd,rs,sa	000011 */
#define RTYPE_FUNC_SRAV		0x07	/* srav rd,rt,rs 000111 */
#define RTYPE_FUNC_SRL		0x02	/* srl rd,rt,sa 000010 */
#define RTYPE_FUNC_SRLV		0x06	/* srlv rd,rt,rs 000110 */
#define RTYPE_FUNC_SUB		0x22	/* sub rd,rs,rt 100010 */
#define RTYPE_FUNC_SUBU		0x23	/* subu rd,rs,rt 100011 */
#define RTYPE_FUNC_SYSCALL	0x0c	/* syscall	001100 */
#define RTYPE_FUNC_XOR		0x26	/* xor rd,rs,rt	100110 */

/*
 * I-Type instruction (ALU immediate)
 * 31-26: opcode - operation code (6 bits)
 * 25-21: rs - operand A register (5 bits)
 * 20-16: rt - destination register (5 bits)
 * 15-0 : immed - immediate operand B (16 bits)
 */
#define ITYPE_OP_ADDI	0x08	/* addi rt,rs,immediate	001000 */
#define ITYPE_OP_ADDIU	0x09	/* addiu rt,rs,immediate 001001 */
#define ITYPE_OP_ANDI	0x0c	/* andi rt,rs,immediate	001100 */
#define ITYPE_OP_LUI	0x0f	/* lui rt,immediate	001111 */
#define ITYPE_OP_ORI	0x0d	/* ori rt,rs,immediate	001101 */
#define ITYPE_OP_SLTI	0x0a	/* slti rt,rs,immediate 001010 */
#define ITYPE_OP_SLTIU	0x0b	/* sltiu rt,rs,immediate 001011 */
#define ITYPE_OP_XORI	0x0e	/* xori rt,rs,immediate 001110 */

/*
 * I-Type instruction (Load/Store)
 * 31-26: opcode - operation code (6 bits)
 * 25-21: rs - address base (5 bits)
 * 20-16: rt - source/destination (5 bits)
 * 15-0 : addr - memory offset address (16 bits)
 */
#define ITYPE_OP_LB	0x20	/* lb rt,immediate(rs)	100000 */
#define ITYPE_OP_LBU	0x24	/* lbu rt,immediate(rs)	100100 */
#define ITYPE_OP_LH	0x21	/* lh rt,immediate(rs)	100001 */
#define ITYPE_OP_LHU	0x25	/* lhu rt,immediate(rs)	100101 */
#define ITYPE_OP_LW	0x23	/* lw rt,immediate(rs)	100011 */
#define ITYPE_OP_LWC1	0x31	/* lwc1 rt,immediate(rs) 110001 */
#define ITYPE_OP_SB	0x28	/* sb rt,immediate(rs)	101000 */
#define ITYPE_OP_SH	0x29	/* sh rt,immediate(rs)	101001 */
#define ITYPE_OP_SW	0x2b	/* sw rt,immediate(rs)	101011 */
#define ITYPE_OP_SWC1	0x39	/* swc1 rt,immediate(rs) 111001 */

/*
 * I-Type instruction (Branch)
 * 31-26: opcode - operation code (6 bits)
 * 25-21: rs - branch operand A (5 bits)
 * 20-16: rt - branch operand B (5 bits)
 * 15-0 : addr - branch offset address (16 bits)
 */
#define ITYPE_OP_BEQ	0x04	/* beq rs,rt,label	000100 */
#define ITYPE_OP_BGEZ	0x01	/* bgez rs,label	000001 */
#define ITYPE_RT_BGEZ	0x01	/* bgez rs,label	rt=00001 */
#define ITYPE_OP_BGTZ	0x07	/* bgtz rs,label	000111 */
#define ITYPE_RT_BGTZ	0x00	/* bgtz rs,label	rt=00000 */
#define ITYPE_OP_BLEZ	0x06	/* blez rs,label	000110 */
#define ITYPE_RT_BLEZ	0x00	/* blez rs,label	rt=00000 */
#define ITYPE_OP_BLTZ	0x01	/* bltz rs,label	000001 */
#define ITYPE_RT_BLTZ	0x00	/* bltz rs,label	rt=00000 */
#define ITYPE_OP_BNE	0x05	/* bne rs,rt,label	000101 */

/*
 * J-Type instruction
 * 31-26: opcode - operation code (6 bits)
 * 25-0 : target - jump target (26 bits)
 */
#define JTYPE_OP_J	0x02	/* j label	000010 */
#define JTYPE_OP_JAL	0x03	/* jal label	000011 */

/*
 * Coprocessor instruction
 * 31-26: opcode - operation code (6 bits)
 * 25-21: format -  (5 bits)
 * 20-16: ft -  register (5 bits)
 * 15-11: fs - destination register (5 bits)
 * 10-6 : fd - shift amount (5 bits)
 *  5-0 : funct - function code (6 bits)
 */
#define CTYPE_FUNC_ADD_S	0x00	/* add.s fd,fs,ft	000000 */
#define CTYPE_FMT_ADD_S		0x10	/* add.s fd,fs,ft	10000 */
#define CTYPE_FUNC_CVT_S_W	0x20	/* cvt.s.w fd,fs,ft	100000 */
#define CTYPE_FMT_CVT_S_W	0x14	/* cvt.s.w fd,fs,ft	10100 */
#define CTYPE_FUNC_CVT_W_S	0x24	/* cvt.w.s fd,fs,ft	100100 */
#define CTYPE_FMT_CVT_W_S	0x10	/* cvt.w.s fd,fs,ft	10000 */
#define CTYPE_FUNC_DIV_S	0x03	/* div.s fd,fs,ft	000011 */
#define CTYPE_FMT_DIV_S		0x10	/* div.s fd,fs,ft	10000 */
#define CTYPE_FUNC_MFC1		0x00	/* mfc1 ft,fs		000000 */
#define CTYPE_FMT_MFC1		0x00	/* mfc1 ft,fs		00000 */
#define CTYPE_FUNC_MOV_S	0x06	/* mov.s fd,fs		000110 */
#define CTYPE_FMT_MOV_S		0x10	/* mov.s fd,fs		10000 */
#define CTYPE_FUNC_MTC1		0x00	/* mtc1 ft,fs		000000 */
#define CTYPE_FMT_MTC1		0x04	/* mtc1 ft,fs		00100 */
#define CTYPE_FUNC_MUL_S	0x02	/* mul.s fd,fs,ft	000010 */
#define CTYPE_FMT_MUL_S		0x10	/* mul.s fd,fs,ft	10000 */
#define CTYPE_FUNC_SUB_S	0x01	/* sub.s fd,fs,ft	000001 */
#define CTYPE_FMT_SUB_S		0x10	/* sub.s fd,fs,ft	10000 */

#endif /* OPCODE_H */
