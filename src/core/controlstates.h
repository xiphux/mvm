/*
 *  controlstates.h
 *  Control state macros
 *  Copyright (C) 2005 Christopher Han
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
#ifndef _MVM_CONTROLSTATES_H
#define _MVM_CONTROLSTATES_H

#define UNASSERT(ctrl)			\
do {					\
	(ctrl)->RegWrite = false;	\
	(ctrl)->MemRead = false;	\
	(ctrl)->MemWrite = false;	\
	(ctrl)->IRWrite = false;	\
	(ctrl)->PCWrite = false;	\
	(ctrl)->PCWriteCond = false;	\
	(ctrl)->CauseWrite = false;	\
	(ctrl)->EPCWrite = false;	\
} while (0)

#define INSTRUCTION_FETCH(ctrl)		\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->MemRead = true;		\
	(ctrl)->ALUSrcA = 0;		\
	(ctrl)->IorD = 0;		\
	(ctrl)->IRWrite = true;		\
	(ctrl)->ALUSrcB = 0x01;		\
	(ctrl)->ALUOp = 0x00;		\
	(ctrl)->PCWrite = true;		\
	(ctrl)->PCSource = 0x00;	\
} while (0)

#define INSTRUCTION_DECODE(ctrl)	\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->ALUSrcA = 0;		\
	(ctrl)->ALUSrcB = 0x11;		\
	(ctrl)->ALUOp = 0x00;		\
} while (0)

#define MEMORY_ADDRESS(ctrl)		\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->ALUSrcA = 1;		\
	(ctrl)->ALUSrcB = 0x01;		\
	(ctrl)->ALUOp = 0x00;		\
} while (0)

#define LMEM_ACCESS(ctrl)		\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->MemRead = true;		\
	(ctrl)->IorD = 1;		\
} while (0)

#define WRITEBACK(ctrl)			\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->RegWrite = true;	\
	(ctrl)->MemtoReg = 1;		\
	(ctrl)->RegDst = 0;		\
} while (0)

#define SMEM_ACCESS(ctrl)		\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->MemWrite = true;	\
	(ctrl)->IorD = 1;		\
} while (0)

#define EXECUTION(ctrl)			\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->ALUSrcA = 1;		\
	(ctrl)->ALUSrcB = 0x00;		\
	(ctrl)->ALUOp = 0x10;		\
} while (0)

#define RTYPE_COMPLETION(ctrl)		\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->RegDst = 1;		\
	(ctrl)->RegWrite = true;	\
	(ctrl)->MemtoReg = 0;		\
} while (0)

#define BRANCH_COMPLETION(ctrl)		\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->ALUSrcA = 1;		\
	(ctrl)->ALUSrcB = 0x00;		\
	(ctrl)->ALUOp = 0x01;		\
	(ctrl)->PCWriteCond = true;	\
	(ctrl)->PCSource = 0x01;	\
} while (0)

#define JUMP_COMPLETION(ctrl)		\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->PCWrite = true;		\
	(ctrl)->PCSource = 0x10;	\
} while (0);

#define OTHER_OP(ctrl)			\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->IntCause = 0;		\
	(ctrl)->CauseWrite = true;	\
	(ctrl)->ALUSrcA = 0;		\
	(ctrl)->ALUSrcB = 0x01;		\
	(ctrl)->ALUOp = 0x01;		\
	(ctrl)->EPCWrite = true;	\
	(ctrl)->PCWrite = true;		\
	(ctrl)->PCSource = 0x11;	\
} while (0)

#define OVERFLOW(ctrl)			\
do {					\
	UNASSERT(ctrl);			\
	(ctrl)->IntCause = 1;		\
	(ctrl)->CauseWrite = true;	\
	(ctrl)->ALUSrcA = 0;		\
	(ctrl)->ALUSrcB = 0x01;		\
	(ctrl)->ALUOp = 0x01;		\
	(ctrl)->EPCWrite = true;	\
	(ctrl)->PCWrite = true;		\
	(ctrl)->PCSource = 0x11;	\
} while (0)

#endif /* _MVM_CONTROLSTATES_H */
