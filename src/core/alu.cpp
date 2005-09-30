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
 */
#include "alu.h"
#include "basic/convenience.h"

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
			return a & b;
		case 3:			/* 011 (XOR) */
			return a ^ b;
		case 5:			/* 101 (NOR) */
			return ~(a | b);
		case 1:			/* 001 (OR) */
			return a | b;
		case 2:			/* 010 (ADD) */
			return a + b;
		case 6:			/* 110 (SUB) */
			return a - b;
		case 7:			/* 111 (SLT) */
			return (a<b?1:0);
		case 4:			/* 100 (SLTIU) */
			return (abs(a)<abs(b)?1:0);
		case 8:			/* 1000 (MUL) */
			return a * b;
		case 9:			/* 1001 (DIV) */
			return a / b;
	}
	return 0;
}
