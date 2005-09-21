/*
 * jtype.cpp
 * J-Type operation class implementation
 * Copyright (C) 2005 Christopher Han
 */
#include "ophandlers.h"
#include "jtype.h"

jtype::jtype(const unsigned char o, const unsigned int t)
{
	assemble(o,t);
}

jtype::jtype(unsigned int ins)
{
	unsigned int t = ins & BITS26;
	ins >>= 26;
	unsigned char o = ins & BITS6;
	assemble(o,t);
}

jtype::jtype(std::string cmd, std::vector<std::string> params)
{
	transform(cmd.begin(), cmd.end(), cmd.begin(), (int(*)(int))tolower);
	unsigned char o = 0;
	unsigned int t = 0;
	if (cmd == "j" && params.size() == 1) {
		o = JTYPE_OP_J;
		t = dereference_label(params.at(0));
	} else if (cmd =="jal"  && params.size() == 1) {
		o = JTYPE_OP_JAL;
		t = dereference_label(params.at(0));
	}
	assemble(o,t);
}

jtype::~jtype()
{
}

unsigned int jtype::instruction()
{
	return (((opcode&BITS6)<<26)|(target&BITS26));
}

void jtype::assemble(const unsigned char o, const unsigned int t)
{
	opcode = o;
	target = t;
}
