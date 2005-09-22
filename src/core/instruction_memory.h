/*
 * instruction_memory.h
 * Instruction memory class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef MVM_INSTRUCTION_MEMORY_H
#define MVM_INSTRUCTION_MEMORY_H

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
	std::deque instructions;
};

#endif /* MVM_INSTRUCTION_MEMORY_H */
