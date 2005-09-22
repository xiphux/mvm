/*
 * instruction_memory.cpp
 * Instruction memory class implementation
 * Copyright (C) 2005 Christopher Han
 */
#include "instruction_memory.h"

instruction_memory::instruction_memory()
{
}

instruction_memory::~instruction_memory()
{
	instructions.clear();
}

void instruction_memory::push_instruction(const unsigned int inst)
{
	instructions.push_back(inst);
}

unsigned int instruction_memory::pop_instruction()
{
	unsigned int f = instructions.front();
	instructions.pop_front();
	return f;
}

unsigned int instruction_memory::fetch_instruction(const unsigned int addr)
{
	return instructions.at(addr>>2);
}

