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
#include "parser/ophandlers.h"
#include "parser/operation.h"
#include "basic/convenience.h"
#include "vm.h"

vm::vm(const bool dbg)
{
	dp = new datapath();
	dp->debug = dbg;
}

vm::~vm()
{
	delete dp;
}

bool vm::load_instructions(std::string const file)
{
	std::ifstream infile;
	infile.open(file.c_str(),std::ios::in);
	if (!infile.good())
		return false;
	std::string buf;
	operation *op;
	instruction *in;
	while (!infile.eof()) {
		getline(infile,buf);
		strip_comments(buf);
		strip_trailing_whitespace(buf);
		if (!buf.empty()) {
			op = assembly_to_op(buf);
			if (op) {
				in = new instruction(buf,op);
				dp->im->push_instruction(in);
			}
		}
	}
	infile.close();
	return true;
}

void vm::run()
{
	while (!dp->complete)
		dp->tick();
}

void vm::tick()
{
	dp->tick();
}

void vm::reset()
{
	delete dp;
	dp = new datapath();
}

void vm::print_instructions()
{
	unsigned int i = 0;
	for (std::deque<instruction*>::iterator it = dp->im->instructions.begin(); it != dp->im->instructions.end(); it++) {
		if (dp->pc->get_value() == i++)
			std::cout << "->";
		else
			std::cout << "  ";
		std::cout << (*it)->get_instruction() << std::endl;
	}
}

void vm::set_debug(const bool d)
{
	dp->debug = d;
}
