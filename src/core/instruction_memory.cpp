/*
 *  instruction_memory.cpp
 *  Instruction memory class implementation
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
#include "instruction_memory.h"

instruction_memory::instruction_memory()
{
}

instruction_memory::~instruction_memory()
{
	for (std::deque<instruction*>::iterator it = instructions.begin(); it != instructions.end(); it++)
		delete *it;
	instructions.clear();
}

void instruction_memory::push_instruction(instruction *inst)
{
	instructions.push_back(inst);
}

instruction *instruction_memory::pop_instruction()
{
	instruction *f = instructions.front();
	instructions.pop_front();
	return f;
}

instruction *instruction_memory::fetch_instruction(const unsigned int addr)
{
	return instructions.at(addr>>2);
}
