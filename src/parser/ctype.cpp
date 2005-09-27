/*
 *  ctype.cpp
 *  Coprocessor operation class implementation
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
#include "basic/opcode.h"
#include "ctype.h"

ctype::ctype(const unsigned char o, const unsigned char fmt, const unsigned char t, const unsigned char s, const unsigned char d, const unsigned char f)
{
	assemble(o,fmt,t,s,d,f);
}

ctype::ctype(unsigned int ins)
{
	unsigned char f = ins & BITS6;
	ins >>= 6;
	unsigned char d = ins & BITS5;
	ins >>= 5;
	unsigned char s = ins & BITS5;
	ins >>= 5;
	unsigned char t = ins & BITS5;
	ins >>= 5;
	unsigned char fmt = ins & BITS5;
	ins >>= 5;
	unsigned char o = ins & BITS6;
	assemble(o,fmt,t,s,d,f);
}

ctype::ctype(std::string cmd, std::vector<std::string> params)
{
	assemble(0,0,0,0,0,0);
}

ctype::~ctype()
{
}

unsigned int ctype::instruction()
{
	return (((((((((((opcode&BITS6)<<5)|(format&BITS5))<<5)|(ft&BITS5))<<5)|(fs&BITS5))<<5)|(fd&BITS5))<<6)|(funct&BITS6));
}

unsigned int ctype::coprocessor()
{
	return opcode & 0x3;
}

void ctype::assemble(const unsigned char o, const unsigned char fmt, const unsigned char t, const unsigned char s, const unsigned char d, const unsigned char f)
{
	opcode = o;
	format = fmt;
	ft = t;
	fs = s;
	fd = d;
	funct = f;
}
