/*
 *  instruction_memory.h
 *  Instruction memory class definition
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
#ifndef _MVM_INSTRUCTION_MEMORY_H
#define _MVM_INSTRUCTION_MEMORY_H

#include <deque>

class instruction_memory
{
public:
	instruction_memory();
	~instruction_memory();
	void push_instruction(const unsigned int inst);
	unsigned int pop_instruction();
	unsigned int fetch_instruction(const unsigned int addr);
private:
	std::deque<unsigned int> instructions;
};

#endif /* _MVM_INSTRUCTION_MEMORY_H */
