/*
 *  alu.cpp
 *  ALU class implementation
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
 *  $Id: alu.cpp 210 2005-10-15 04:18:35Z xiphux $
 */
#include "alu.h"
#include "../basic/convenience.h"
#include "../mvm.h"

mvm::core::ALU::ALU()
{
}

mvm::core::ALU::~ALU()
{
}

int mvm::core::ALU::execute(unsigned int op, int a, int b)
{
	switch (op) {
		case 0:			/* 000 (AND) */
			if (debug) printf("ALU AND\n");
			return a & b;
		case 3:			/* 011 (XOR) */
			if (debug) printf("ALU XOR\n");
			return a ^ b;
		case 5:			/* 101 (NOR) */
			if (debug) printf("ALU NOR\n");
			return ~(a | b);
		case 1:			/* 001 (OR) */
			if (debug) printf("ALU OR\n");
			return a | b;
		case 2:			/* 010 (ADD) */
			if (debug) printf("ALU ADD\n");
			return a + b;
		case 6:			/* 110 (SUB) */
			if (debug) printf("ALU SUB\n");
			return a - b;
		case 7:			/* 111 (SLT) */
			if (debug) printf("ALU SLT\n");
			return (a<b?1:0);
		case 4:			/* 100 (SLTIU) */
			if (debug) printf("ALU SLTIU\n");
			return (abs(a)<abs(b)?1:0);
		case 8:			/* 1000 (MUL) */
			if (debug) printf("ALU MUL\n");
			return a * b;
		case 9:			/* 1001 (DIV) */
			if (debug) printf("ALU DIV\n");
			return a / b;
	}
	return 0;
}
