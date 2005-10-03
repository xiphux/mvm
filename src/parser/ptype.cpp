/*
 *  ptype.cpp
 *  Pseudo operation class implementation
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
#include "ptype.h"
#include "rtype.h"
#include "itype.h"

mvm::parser::ptype::ptype(std::string cmd, std::vector<std::string> params)
{
	command = cmd;
	parms = params;
	translate();
}

mvm::parser::ptype::~ptype()
{
}

void mvm::parser::ptype::translate()
{
	if (command == "move")
		translate_move();
	else if (command == "li")
		translate_li();
	else if (command == "lui")
		translate_lui();
	else if (command == "la")
		translate_la();
	else if (command == "beqz")
		translate_beqz();
	else if (command == "bnez")
		translate_bnez();
}

void mvm::parser::ptype::translate_move()
{
	std::vector<std::string> p;
	p.push_back(parms.at(0));
	p.push_back("$0");
	p.push_back(parms.at(1));
	operation *o = new rtype("add",p);
	ops.push_back(o);
	std::string i = "add "+p.at(0)+","+p.at(1)+","+p.at(2);
	ins.push_back(i);
}

void mvm::parser::ptype::translate_li()
{
	std::vector<std::string> p;
	p.push_back(parms.at(0));
	p.push_back("$0");
	p.push_back(parms.at(1));
	operation *o = new itype("addi",p);
	ops.push_back(o);
	std::string i = "addi "+p.at(0)+","+p.at(1)+","+p.at(2);
	ins.push_back(i);
}

void mvm::parser::ptype::translate_lui()
{
	std::vector<std::string> p;
	p.push_back(parms.at(0));
	p.push_back("$0");
	p.push_back(parms.at(1));
	operation *o = new itype("addiu",p);
	ops.push_back(o);
	std::string i = "addi "+p.at(0)+","+p.at(1)+","+p.at(2);
	ins.push_back(i);
}

void mvm::parser::ptype::translate_la()
{
}

void mvm::parser::ptype::translate_beqz()
{
	std::vector<std::string> p;
	p.push_back(parms.at(0));
	p.push_back("$0");
	p.push_back(parms.at(1));
	operation *o = new itype("beq",p);
	std::string i = "beq "+p.at(0)+","+p.at(1)+","+p.at(2);
	ins.push_back(i);
}

void mvm::parser::ptype::translate_bnez()
{
	std::vector<std::string> p;
	p.push_back(parms.at(0));
	p.push_back("$0");
	p.push_back(parms.at(1));
	operation *o = new itype("bne",p);
	std::string i = "bne "+p.at(0)+","+p.at(1)+","+p.at(2);
	ins.push_back(i);
}
