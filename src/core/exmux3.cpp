/*
 *  exmux3.cpp
 *  EX stage 3-input MUX class implementation
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
#include "exmux3.h"

mvm::core::exmux3::exmux3(): signal1(false), signal2(false)
{
}

mvm::core::exmux3::~exmux3()
{
}

bool mvm::core::exmux3::get_signal1()
{
	return signal1;
}

bool mvm::core::exmux3::get_signal2()
{
	return signal2;
}

void mvm::core::exmux3::set_signal1(const bool s)
{
	signal1 = s;
}

void mvm::core::exmux3::set_signal2(const bool s)
{
	signal2 = s;
}

int mvm::core::exmux3::mux(const int a, const int b, const int c)
{
	if (!signal1 && !signal2)
		return a;
	else if (!signal1 && signal2)
		return b;
	else if (signal1 && !signal2)
		return c;
	return 0;
}

