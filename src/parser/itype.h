/*
 * itype.h
 * I-Type operation class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef MVM_ITYPE_H
#define MVM_ITYPE_H

#include <string>
#include <vector>
#include "operation.h"

class itype: public operation
{
public:
	itype(const unsigned char o, const unsigned char s, const unsigned char t, const unsigned short a);
	itype(unsigned int ins);
	itype(std::string cmd, std::vector<std::string> params);
	~itype();
	unsigned int instruction();
private:
	void assemble(const unsigned char o, const unsigned char s, const unsigned char t, const unsigned short a);
	unsigned char opcode;
	unsigned char rs;
	unsigned char rt;
	unsigned short addr;
};

#endif /* MVM_ITYPE_H */
