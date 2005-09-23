/*
 *  jtype.h
 *  J-Type operation class definition
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
#ifndef _MVM_JTYPE_H
#define _MVM_JTYPE_H

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

#endif /* _MVM_JTYPE_H */
