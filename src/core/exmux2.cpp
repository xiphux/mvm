/*
 *  exmux2.cpp
 *  EX stage 2-input MUX class implementation
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
#include "exmux2.h"

mvm::core::exmux2::exmux2(): signal(false)
{
}

mvm::core::exmux2::~exmux2()
{
}

bool mvm::core::exmux2::get_signal()
{
	return signal;
}

void mvm::core::exmux2::set_signal(const bool s)
{
	signal = s;
}

int mvm::core::exmux2::mux(const int a, const int b)
{
	if (signal)
		return a;
	else if (!signal)
		return b;
	return 0;
}
