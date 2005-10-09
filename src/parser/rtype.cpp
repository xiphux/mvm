/*
 *  rtype.cpp
 *  R-Type operation class implementation
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
#include "../basic/opcode.h"
#include "ophandlers.h"
#include "rtype.h"

mvm::parser::rtype::rtype(const unsigned char o, const unsigned char s, const unsigned char t, const unsigned char d, const unsigned char sh, const unsigned char f)
{
	assemble(o,s,t,d,sh,f);
}

mvm::parser::rtype::rtype(unsigned int ins)
{
	unsigned char f = ins & BITS6;
	ins >>= 6;
	unsigned char sh = ins & BITS5;
	ins >>= 5;
	unsigned char d = ins & BITS5;
	ins >>= 5;
	unsigned char t = ins & BITS5;
	ins >>= 5;
	unsigned char s = ins & BITS5;
	ins >>= 5;
	unsigned char o = ins & BITS6;
	assemble(o,s,t,d,sh,f);
}

mvm::parser::rtype::rtype(std::string cmd, std::vector<std::string> params)
{
	transform(cmd.begin(), cmd.end(), cmd.begin(), (int(*)(int))tolower);
	unsigned char o = 0;
	unsigned char s = 0;
	unsigned char t = 0;
	unsigned char d = 0;
	unsigned char sh = 0;
	unsigned char f = 0;
	if (cmd == "add" && params.size() == 3) {
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(2));
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_ADD;
	} else if (cmd == "addu" && params.size() == 3) {
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(2));
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_ADDU;
	} else if (cmd == "and" && params.size() == 3) {
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(2));
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_AND;
	} else if (cmd == "break" && params.size() == 0) {
		f = RTYPE_FUNC_BREAK;
	} else if (cmd == "div" && params.size() == 2) {
		s = dereference_register(params.at(0));
		t = dereference_register(params.at(1));
		f = RTYPE_FUNC_DIV;
	} else if (cmd == "divu" && params.size() == 2) {
		s = dereference_register(params.at(0));
		t = dereference_register(params.at(1));
		f = RTYPE_FUNC_DIVU;
	} else if (cmd == "jalr" && params.size() == 2) {
		s = dereference_register(params.at(0));
		t = dereference_register(params.at(1));
		f = RTYPE_FUNC_JALR;
	} else if (cmd == "jr" && params.size() == 1) {
		s = dereference_register(params.at(0));
		f = RTYPE_FUNC_JR;
	} else if (cmd == "mfhi" && params.size() == 1) {
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_MFHI;
	} else if (cmd == "mflo" && params.size() == 1) {
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_MFLO;
	} else if (cmd == "mthi" && params.size() == 1) {
		s = dereference_register(params.at(0));
		f = RTYPE_FUNC_MTHI;
	} else if (cmd == "mtlo" && params.size() == 1) {
		s = dereference_register(params.at(0));
		f = RTYPE_FUNC_MTLO;
	} else if (cmd == "mult" && params.size() == 2) {
		s = dereference_register(params.at(0));
		t = dereference_register(params.at(1));
		f = RTYPE_FUNC_MULT;
	} else if (cmd == "multu" && params.size() == 2) {
		s = dereference_register(params.at(0));
		t = dereference_register(params.at(1));
		f = RTYPE_FUNC_MULTU;
	} else if (cmd == "nor" && params.size() == 3) {
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(2));
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_NOR;
	} else if (cmd == "or" && params.size() == 3) {
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(2));
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_OR;
	} else if (cmd == "sll" && params.size() == 3) {
		t = dereference_register(params.at(1));
		d = dereference_register(params.at(0));
		sh = atoi(params.at(2).c_str());
		f = RTYPE_FUNC_SLL;
	} else if (cmd == "sllv" && params.size() == 3) {
		s = dereference_register(params.at(2));
		t = dereference_register(params.at(1));
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_SLLV;
	} else if (cmd == "slt" && params.size() == 3) {
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(2));
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_SLT;
	} else if (cmd == "sltu" && params.size() == 3) {
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(2));
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_SLTU;
	} else if (cmd == "sra" && params.size() == 3) {
		s = dereference_register(params.at(1));
		d = dereference_register(params.at(0));
		sh = atoi(params.at(2).c_str());
		f = RTYPE_FUNC_SRA;
	} else if (cmd == "srav" && params.size() == 3) {
		s = dereference_register(params.at(2));
		t = dereference_register(params.at(1));
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_SRAV;
	} else if (cmd == "srl" && params.size() == 3) {
		t = dereference_register(params.at(1));
		d = dereference_register(params.at(0));
		sh = atoi(params.at(2).c_str());
		f = RTYPE_FUNC_SRL;
	} else if (cmd == "srlv" && params.size() == 3) {
		s = dereference_register(params.at(2));
		t = dereference_register(params.at(1));
		d = dereference_register(params.at(0));
		f = RTYPE_FUNC_SRLV;
	} else if (cmd == "sub" && params.size() == 3) {
		s = dereference_register(params.at(2));
		t = dereference_register(params.at(0));
		d = dereference_register(params.at(1));
		f = RTYPE_FUNC_SUB;
	} else if (cmd == "subu" && params.size() == 3) {
		s = dereference_register(params.at(2));
		t = dereference_register(params.at(0));
		d = dereference_register(params.at(1));
		f = RTYPE_FUNC_SUBU;
	} else if (cmd == "syscall" && params.size() == 0) {
		f = RTYPE_FUNC_SYSCALL;
	} else if (cmd == "xor" && params.size() == 3) {
		s = dereference_register(params.at(2));
		t = dereference_register(params.at(0));
		d = dereference_register(params.at(1));
		f = RTYPE_FUNC_XOR;
	}
	assemble(o,s,t,d,sh,f);
}

mvm::parser::rtype::~rtype()
{
}

void mvm::parser::rtype::assemble(const unsigned char o, const unsigned char s, const unsigned char t, const unsigned char d, const unsigned char sh, const unsigned char f)
{
	opcode = o;
	rs = s;
	rt = t;
	rd = d;
	shamt = sh;
	funct = f;
}

unsigned int mvm::parser::rtype::instruction()
{
	return (((((((((((opcode&BITS6)<<5)|(rs&BITS5))<<5)|(rt&BITS5))<<5)|(rd&BITS5))<<5)|(shamt&BITS5))<<6)|(funct&BITS6));
}
