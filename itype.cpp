/*
 * itype.cpp
 * I-Type operation class implementation
 * Copyright (C) 2005 Christopher Han
 */
#include "ophandlers.h"
#include "itype.h"

itype::itype(const unsigned char o, const unsigned char s, const unsigned char t, const unsigned short a)
{
	assemble(o,s,t,a);
}

itype::itype(unsigned int ins)
{
	unsigned short a = ins & BITS16;
	ins >>= 16;
	unsigned char t = ins & BITS5;
	ins >>= 5;
	unsigned char s = ins & BITS5;
	ins >>= 5;
	unsigned char o = ins & BITS6;
	assemble(o,s,t,a);
}

itype::itype(std::string cmd, std::vector<std::string> params)
{
	transform(cmd.begin(), cmd.end(), cmd.begin(), (int(*)(int))tolower);
	unsigned char o = 0;
	unsigned char s = 0;
	unsigned char t = 0;
	unsigned short a = 0;
	if (cmd == "addi" && params.size() == 3) {
		o = ITYPE_OP_ADDI;
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(0));
		a = atoi(params.at(2).c_str());
	} else if (cmd == "addiu" && params.size() == 3) {
		o = ITYPE_OP_ADDIU;
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(0));
		a = atoi(params.at(2).c_str());
	} else if (cmd == "andi" && params.size() == 3) {
		o = ITYPE_OP_ANDI;
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(0));
		a = atoi(params.at(2).c_str());
	} else if (cmd == "lui" && params.size() == 2) {
		o = ITYPE_OP_LUI;
		t = dereference_register(params.at(0));
		a = atoi(params.at(1).c_str());
	} else if (cmd == "ori" && params.size() == 3) {
		o = ITYPE_OP_ORI;
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(0));
		a = atoi(params.at(2).c_str());
	} else if (cmd == "slti" && params.size() == 3) {
		o = ITYPE_OP_SLTI;
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(0));
		a = atoi(params.at(2).c_str());
	} else if (cmd == "sltiu" && params.size() == 3) {
		o = ITYPE_OP_SLTIU;
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(0));
		a = atoi(params.at(2).c_str());
	} else if (cmd == "xori" && params.size() == 3) {
		o = ITYPE_OP_XORI;
		s = dereference_register(params.at(1));
		t = dereference_register(params.at(0));
		a = atoi(params.at(2).c_str());
	} else if (cmd == "beq" && params.size() == 3) {
		o = ITYPE_OP_BEQ;
		s = dereference_register(params.at(0));
		t = dereference_register(params.at(1));
		a = dereference_label(params.at(2));
	} else if (cmd == "bgez" && params.size() == 2) {
		o = ITYPE_OP_BGEZ;
		s = dereference_register(params.at(0));
		t = ITYPE_RT_BGEZ;
		a = dereference_label(params.at(1));
	} else if (cmd == "bgtz" && params.size() == 2) {
		o = ITYPE_OP_BGTZ;
		s = dereference_register(params.at(0));
		t = ITYPE_RT_BGTZ;
		a = dereference_label(params.at(1));
	} else if (cmd == "blez" && params.size() == 2) {
		o = ITYPE_OP_BLEZ;
		s = dereference_register(params.at(0));
		t = ITYPE_RT_BLEZ;
		a = dereference_label(params.at(1));
	} else if (cmd == "bltz" && params.size() == 2) {
		o = ITYPE_OP_BLTZ;
		s = dereference_register(params.at(0));
		t = ITYPE_RT_BLTZ;
		a = dereference_label(params.at(1));
	} else if (cmd == "bne" && params.size() == 3) {
		o = ITYPE_OP_BNE;
		s = dereference_register(params.at(0));
		t = dereference_register(params.at(1));
		a = dereference_label(params.at(2));
	} else if (params.size() == 2) {
		if (cmd == "lb")
			o = ITYPE_OP_LB;
		else if (cmd == "lbu")
			o = ITYPE_OP_LBU;
		else if (cmd == "lh")
			o = ITYPE_OP_LH;
		else if (cmd == "lhu")
			o = ITYPE_OP_LHU;
		else if (cmd == "lw")
			o = ITYPE_OP_LW;
		else if (cmd == "lwc1")
			o = ITYPE_OP_LWC1;
		else if (cmd == "sb")
			o = ITYPE_OP_SB;
		else if (cmd == "sh")
			o = ITYPE_OP_SH;
		else if (cmd == "sw")
			o = ITYPE_OP_SW;
		else if (cmd == "swc1")
			o = ITYPE_OP_SWC1;
		if (o) {
			std::string _imm;
			std::string _s;
			if (dereference_pointer(params.at(1),_imm,_s)) {
				s = dereference_register(_s);
				t = dereference_register(params.at(0));
				a = atoi(_imm.c_str());
			}
		}
	}
	assemble(o,s,t,a);
}

itype::~itype()
{
}

unsigned int itype::instruction()
{
	return (((((((opcode&BITS6)<<5)|(rs&BITS5))<<5)|(rt&BITS5))<<16)|(addr&BITS16));
}

void itype::assemble(const unsigned char o, const unsigned char s, const unsigned char t, const unsigned short a)
{
	opcode = o;
	rs = s;
	rt = t;
	addr = a;
}
