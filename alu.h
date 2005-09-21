/*
 * alu.h
 * ALU class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef ALU_H
#define ALU_H

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

#endif /* ALU_H */
