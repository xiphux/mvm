/*
 *  jtype.cpp
 *  J-Type operation class implementation
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
#include "jtype.h"

mvm::parser::jtype::jtype(const unsigned char o, const unsigned int t)
{
	assemble(o,t);
}

mvm::parser::jtype::jtype(unsigned int ins)
{
	unsigned int t = ins & BITS26;
	ins >>= 26;
	unsigned char o = ins & BITS6;
	assemble(o,t);
}

mvm::parser::jtype::jtype(std::string cmd, std::vector<std::string> params)
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

mvm::parser::jtype::~jtype()
{
}

unsigned int mvm::parser::jtype::instruction()
{
	return (((opcode&BITS6)<<26)|(target&BITS26));
}

void mvm::parser::jtype::assemble(const unsigned char o, const unsigned int t)
{
	opcode = o;
	target = t;
}
