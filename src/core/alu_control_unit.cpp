/*
 *  alu_control_unit.cpp
 *  ALU control unit class implementation
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
#include "alu_control_unit.h"
#include "basic/opcode.h"

alu_control_unit::alu_control_unit()
{
}

alu_control_unit::~alu_control_unit()
{
}

unsigned int alu_control_unit::fire_signal(const unsigned int ctrl, const unsigned int inst)
{
	unsigned int op = OPCODE(inst);
	unsigned int funct = FUNCT(inst);
	switch (ctrl) {
		case 0x0:				/* mem types */
			return 0x2;			/* 010 */
		case 0x1:				/* 01 */
			return 0x6;			/* 110 */
		case 0x2:				/* 10 */
			if (!op) {
				switch (funct) {
					case RTYPE_FUNC_ADD:
						return 0x2;		/* 010 */
					case RTYPE_FUNC_SUB:
						return 0x6;		/* 110 */
					case RTYPE_FUNC_AND:
						return 0x0;
					case RTYPE_FUNC_OR:
						return 0x1;		/* 001 */
					case RTYPE_FUNC_XOR:
						return 0x3;		/* 011 */
					case RTYPE_FUNC_NOR:
						return 0x5;		/* 101 */
					case RTYPE_FUNC_SLT:
						return 0x7;		/* 111 */
					case RTYPE_FUNC_SLTU:
						return 0x7;		/* 111 */
					case RTYPE_FUNC_MULT:
						return 0x8;		/* 1000 */
					case RTYPE_FUNC_DIV:
						return 0x9;		/* 1001 */
				}
			} else {
				switch (op) {
					case ITYPE_OP_ADDI:
						return 0x2;		/* 010 */
					case ITYPE_OP_ANDI:
						return 0x0;
					case ITYPE_OP_ORI:
						return 0x1;		/* 001 */
					case ITYPE_OP_XORI:
						return 0x3;		/* 011 */
					case ITYPE_OP_SLTI:
						return 0x7;		/* 111 */
					case ITYPE_OP_SLTIU:
						return 0x7;		/* 111 */
				}
			}
	}
	return 0;
}
