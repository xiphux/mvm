/*
 *  mux3.cpp
 *  2-signal MUX class implementation
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
#include "mux3.h"

mvm::core::mux3::mux3()
{
}

mvm::core::mux3::~mux3()
{
}

unsigned int mvm::core::mux3::result()
{
}

bool mvm::core::mux3::get_jump_signal()
{
	return jump;
}

bool mvm::core::mux3::get_exception_signal()
{
	return exception;
}

void mvm::core::mux3::set_jump_signal(bool sig)
{
	jump = sig;
}

void mvm::core::mux3::get_jump_signal(bool sig)
{
	exception = sig;
}
