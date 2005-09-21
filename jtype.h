/*
 * jtype.h
 * J-Type operation class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef JTYPE_H
#define JTYPE_H

#include <string>
#include <vector>
#include "operation.h"

class jtype: public operation
{
public:
	jtype(const unsigned char o, const unsigned int t);
	jtype(unsigned int ins);
	jtype(std::string cmd, std::vector<std::string> params);
	~jtype();
	unsigned int instruction();
private:
	void assemble(const unsigned char o, const unsigned int t);
	unsigned char opcode;
	unsigned int target;
};

#endif /* JTYPE_H */
