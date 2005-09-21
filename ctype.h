/*
 * ctype.h
 * Coprocessor operation class definition
 * Copyright (C) 2005 Christopher Han
 */
#ifndef CTYPE_H
#define CTYPE_H

#include <string>
#include <vector>
#include "operation.h"

class ctype: public operation
{
public:
	ctype(const unsigned char o, const unsigned char fmt, const unsigned char t, const unsigned char s, const unsigned char d, const unsigned char f);
	ctype(unsigned int ins);
	ctype(std::string cmd, std::vector<std::string> params);
	~ctype();
	unsigned int instruction();
	unsigned int coprocessor();
private:
	void assemble(const unsigned char o, const unsigned char fmt, const unsigned char t, const unsigned char s, const unsigned char d, const unsigned char f);
	unsigned char opcode;
	unsigned char format;
	unsigned char ft;
	unsigned char fs;
	unsigned char fd;
	unsigned char funct;
};

#endif /* CTYPE_H */
