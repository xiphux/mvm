/*
 *  control.cpp
 *  Control class implementation
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
 *
 *  $Id: control.cpp 251 2005-12-07 10:01:26Z xiphux $
 */
#include "control.h"
#include "../basic/opcode.h"

mvm::core::control::control()
{
}

mvm::core::control::~control()
{
}

unsigned int mvm::core::control::read_instruction(const unsigned int inst, const unsigned int sig)
{
	unsigned int op = OPCODE(inst);
	unsigned int ex,mem,wb;
	switch (op) {
		case 0: {
				unsigned int funct = FUNCT(inst);
				if (!funct) {
					ex = 0x0;
					mem = 0x0;
					wb = 0x0;
				} else {
					ex = 0xc;		/* 1100 */
					mem = 0x0;
					wb = 0x2;		/* 10 */
				}
			}
			break;
		case ITYPE_OP_ADDI:
		case ITYPE_OP_ANDI:
		case ITYPE_OP_ORI:
		case ITYPE_OP_SLTI:
		case ITYPE_OP_SLTIU:
		case ITYPE_OP_XORI:
			ex = 0x5;		/* 0101 */
			mem = 0x0;
			wb = 0x2;		/* 10 */
			break;
		case ITYPE_OP_BEQ:
		case ITYPE_OP_BNE:
			ex = 0x0;
			mem = 0x0;
			wb = 0x0;
			break;
		case ITYPE_OP_LB:
		case ITYPE_OP_LBU:
			ex = 0x0;
			mem = 0x4;		/* 100 */
			wb = 0x3;		/* 11 */
			break;
		case ITYPE_OP_LW:
			ex = 0x0;
			mem = 0x5;		/* 101 */
			wb = 0x3;		/* 11 */
			break;
		case ITYPE_OP_SB:
			ex = 0x0;
			mem = 0x2;		/* 010 */
			wb = 0x1;		/* 01 */
			break;
		case ITYPE_OP_SW:
			ex = 0x0;
			mem = 0x3;		/* 011 */
			wb = 0x1;		/* 01 */
			break;
		default:
			ex = 0x0;
			mem = 0x0;
			wb = 0x0;
			break;
	}
	switch (sig) {
		case SIGNAL_JUMP:
			if ((op == 2) ||
				(op == 3) ||
				(op == 4) ||
				(op == 5) ||
				(FUNCT(inst) == 8))
				return 1;
			break;
		case SIGNAL_PCSRC:
			/* Exception */
			break;
		case SIGNAL_WB:
			return wb;
		case SIGNAL_M:
			return mem;
		case SIGNAL_EX:
			return ex;
	}
	return 0;
}
