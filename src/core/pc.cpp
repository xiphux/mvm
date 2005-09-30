/*
 *  pc.cpp
 *  Program Counter class implementation
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
#include "pc.h"

mvm::core::PC::PC(): value(0)
{
}

mvm::core::PC::~PC()
{
}

unsigned int mvm::core::PC::get_value()
{
	return value;
}

unsigned int mvm::core::PC::get_address()
{
	return value << 2;
}

void mvm::core::PC::set_value(const unsigned int val)
{
	value = val;
}

void mvm::core::PC::set_address(const unsigned int addr)
{
	value = addr >> 2;
}
