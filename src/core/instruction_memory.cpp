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
 *
 *  $Id: instruction_memory.cpp 210 2005-10-15 04:18:35Z xiphux $
 */
#include "instruction_memory.h"
#include "../parser/rtype.h"

mvm::core::instruction_memory::instruction_memory()
{
}

mvm::core::instruction_memory::~instruction_memory()
{
	for (std::deque<instruction*>::iterator it = instructions.begin(); it != instructions.end(); it++)
		delete *it;
	instructions.clear();
}

void mvm::core::instruction_memory::push_instruction(instruction *inst)
{
	if (instructions.size() > TEXT_SEGMENT_COUNT)
		return;
	instructions.push_back(inst);
}

mvm::core::instruction *mvm::core::instruction_memory::pop_instruction()
{
	instruction *f = instructions.front();
	instructions.pop_front();
	return f;
}

mvm::core::instruction *mvm::core::instruction_memory::fetch_instruction(const unsigned int addr)
{
	if ((addr>TEXT_SEGMENT_BYTES)||((addr>>2)>=instructions.size()))
		return new instruction("nop",new mvm::parser::rtype(0));
	return instructions.at(addr>>2);
}
