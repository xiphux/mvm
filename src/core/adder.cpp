/*
 *  adder.cpp
 *  Adder class implementation
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
#include "adder.h"

mvm::core::adder::adder():a(0),b(0),result(0)
{
}

mvm::core::adder::~adder()
{
}

void mvm::core::adder::setaval(const int v)
{
	a = v;
}

void mvm::core::adder::setbval(const int v)
{
	b = v;
}

void mvm::core::adder::execute()
{
	result = a + b;
}

int mvm::core::adder::getresult()
{
	return result;
}
