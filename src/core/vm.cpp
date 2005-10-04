/*
 *  vm.cpp
 *  Base virtual machine class implementation
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
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include "../parser/ophandlers.h"
#include "../parser/operation.h"
#include "../basic/convenience.h"
#include "../parser/ptype.h"
#include "vm.h"

mvm::core::vm::vm(const bool dbg)
{
	dp = new datapath();
	dp->debug = dbg;
}

mvm::core::vm::~vm()
{
	delete dp;
}

bool mvm::core::vm::load_instructions(std::string const file, const bool load)
{
	std::ifstream infile;
	infile.open(file.c_str(),std::ios::in);
	if (!infile.good())
		return false;
	std::string buf;
	mvm::parser::operation *op;
	instruction *in;
	while (!infile.eof()) {
		getline(infile,buf);
		mvm::basic::strip_comments(buf);
		mvm::basic::strip_trailing_whitespace(buf);
		if (!buf.empty()) {
			op = mvm::parser::assembly_to_op(buf);
			if (op) {
				in = new instruction(buf,op);
				if (in) {
					if (in->get_opcode()->pseudo()) {
						int i = 0;
						char tm[4];
						instruction *in2;
						mvm::parser::ptype *p = dynamic_cast<mvm::parser::ptype*>(in->get_opcode());
						for (std::vector<mvm::parser::operation*>::iterator it = p->ops.begin(); it != p->ops.end(); it++) {
							snprintf(tm,4,"%d",i+1);
							std::string s = "\t\t";
							if (buf.size()<14)
								s.append("\t");
							s.append("(pseudo step ");
							s.append(tm).append(" : ").append(p->ins.at(i++)).append(")");
							in2 = new instruction(buf.append(s),*it);
							dp->as->im->push_instruction(in2);
						}
						delete in;
					} else
						dp->as->im->push_instruction(in);
				}
			}
		}
	}
	infile.close();
	if (!load) {
		instruction *i;
		while (!dp->as->im->instructions.empty()) {
			i = dp->as->im->pop_instruction();
			delete i;
		}
		return load_instructions(file,true);
	}
	return true;
}

void mvm::core::vm::run()
{
	while (!dp->complete)
		dp->tick();
}

void mvm::core::vm::tick()
{
	dp->tick();
}

void mvm::core::vm::reset()
{
	delete dp;
	dp = new datapath();
}

void mvm::core::vm::print_instructions()
{
	unsigned int i = 0;
	for (std::deque<instruction*>::iterator it = dp->as->im->instructions.begin(); it != dp->as->im->instructions.end(); it++) {
		for (std::map<std::string,unsigned int>::iterator it2 = dp->labels.begin(); it2 != dp->labels.end(); it2++) {
			if (it2->second == i<<2)
				std::cout << it2->first << ":" << std::endl;
		}
		if (dp->pc->get_value() == i++)
			std::cout << "->";
		else
			std::cout << "  ";
		std::cout << (*it)->get_instruction() << std::endl;
	}
}

void mvm::core::vm::set_debug(const bool d)
{
	dp->debug = d;
}
