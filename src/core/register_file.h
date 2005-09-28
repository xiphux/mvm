/*
 *  register_file.h
 *  Register File class definition
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
#ifndef _MVM_REGISTER_FILE_H
#define _MVM_REGISTER_FILE_H

#include "register32.h"

class register_file
{
public:
	register_file();
	~register_file();
	unsigned int get_register(const unsigned int reg);
	void set_register(const unsigned int reg, const unsigned int val);
private:
	register32 *regs[32];
};

#endif /* _MVM_REGISTER_FILE_H */
