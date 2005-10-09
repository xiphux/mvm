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
#include "../basic/opcode.h"
#include <stdio.h>

mvm::core::alu_control_unit::alu_control_unit()
{
}

mvm::core::alu_control_unit::~alu_control_unit()
{
}

unsigned int mvm::core::alu_control_unit::fire_signal(const unsigned int ctrl, const unsigned int funct, const unsigned int op)
{
	printf("CTRL = %d\n",ctrl);
	printf("OPCODE = %d\n",op);
	printf("FUNCT = %d\n",funct);
	switch (ctrl) {
		case 0x0:				/* mem types */
			printf("0x0\n");
			return 0x2;			/* 010 */
		case 0x1:				/* 01 */
			printf("0x1\n");
			return 0x6;			/* 110 */
		case 0x2:				/* 10 */
			printf("0x2\n");
			if (!op) {
				switch (funct) {
					case RTYPE_FUNC_ADD:
						printf("RTYPE_FUNC_ADD\n");
						return 0x2;		/* 010 */
					case RTYPE_FUNC_SUB:
						printf("RTYPE_FUNC_SUB\n");
						return 0x6;		/* 110 */
					case RTYPE_FUNC_AND:
						printf("RTYPE_FUNC_AND\n");
						return 0x0;
					case RTYPE_FUNC_OR:
						printf("RTYPE_FUNC_OR\n");
						return 0x1;		/* 001 */
					case RTYPE_FUNC_XOR:
						printf("RTYPE_FUNC_XOR\n");
						return 0x3;		/* 011 */
					case RTYPE_FUNC_NOR:
						printf("RTYPE_FUNC_NOR\n");
						return 0x5;		/* 101 */
					case RTYPE_FUNC_SLT:
						printf("RTYPE_FUNC_SLT\n");
						return 0x7;		/* 111 */
					case RTYPE_FUNC_SLTU:
						printf("RTYPE_FUNC_SLTU\n");
						return 0x7;		/* 111 */
					case RTYPE_FUNC_MULT:
						printf("RTYPE_FUNC_MULT\n");
						return 0x8;		/* 1000 */
					case RTYPE_FUNC_DIV:
						printf("RTYPE_FUNC_DIV\n");
						return 0x9;		/* 1001 */
					default:
						printf("Unknown RTYPE!\n");
				}
			} else {
				switch (op) {
					case ITYPE_OP_ADDI:
						printf("ITYPE_OP_ADDI\n");
						return 0x2;		/* 010 */
					case ITYPE_OP_ANDI:
						printf("ITYPE_OP_ANDI\n");
						return 0x0;
					case ITYPE_OP_ORI:
						printf("ITYPE_OP_ORI\n");
						return 0x1;		/* 001 */
					case ITYPE_OP_XORI:
						printf("ITYPE_OP_XORI\n");
						return 0x3;		/* 011 */
					case ITYPE_OP_SLTI:
						printf("ITYPE_OP_SLTI\n");
						return 0x7;		/* 111 */
					case ITYPE_OP_SLTIU:
						printf("ITYPE_OP_SLTIU\n");
						return 0x7;		/* 111 */
					default:
						printf("Unknown ITYPE!\n");
				}
			}
	}
	return 0;
}
