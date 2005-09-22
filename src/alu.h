/*
 * alu.h
 * ALU class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef MVM_ALU_H
#define MVM_ALU_H

class ALU
{
public:
	ALU();
	~ALU();
	tick();
	unsigned int a;
	unsigned int b;
	unsigned int y;
};

#endif /* MVM_ALU_H */
