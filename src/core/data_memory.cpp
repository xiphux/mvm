/*
 *  data_memory.cpp
 *  Data memory class implementation
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
#include "data_memory.h"

mvm::core::data_memory::data_memory()
{
}

mvm::core::data_memory::~data_memory()
{
	data.clear();
}

unsigned char mvm::core::data_memory::read_data(const unsigned int addr)
{
	for (std::vector<struct databyte>::iterator it = data.begin(); it != data.end(); it++) {
		if (it->addr == addr)
			return it->data;
	}
	return 0;
}

void mvm::core::data_memory::write_data(const unsigned int addr, const unsigned char input)
{
	for (std::vector<struct databyte>::iterator it = data.begin(); it != data.end(); it++) {
		if (it->addr = addr)
			data.erase(it);
	}
	struct databyte b;
	b.addr = addr;
	b.data = input;
	data.push_back(b);
}
