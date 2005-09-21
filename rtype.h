/*
 * rtype.h
 * R-Type operation class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef RTYPE_H
#define RTYPE_H

#include <string>
#include <vector>
#include "operation.h"

class rtype: public operation
{
public:
	rtype(const unsigned char o, const unsigned char s, const unsigned char t, const unsigned char d, const unsigned char sh, const unsigned char f);
	rtype(unsigned int ins);
	rtype(std::string cmd, std::vector<std::string> params);
	~rtype();
	unsigned int instruction();
private:
	void assemble(const unsigned char o, const unsigned char s, const unsigned char t, const unsigned char d, const unsigned char sh, const unsigned char f);
	unsigned char opcode;
	unsigned char rs;
	unsigned char rt;
	unsigned char rd;
	unsigned char shamt;
	unsigned char funct;
};

#endif /* RTYPE_H */
