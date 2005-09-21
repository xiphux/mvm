/*
 *  mux2.cpp
 *  2-Way MUX class implementation
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
 *
 *  $Id: mux2.cpp 210 2005-10-15 04:18:35Z xiphux $
 */
#include "mux2.h"

mvm::core::mux2::mux2()
{
	state = false;
}

mvm::core::mux2::~mux()
{
}

unsigned int mvm::core::mux2::getstate()
{
	return (state?1:0);
}

void mvm::core::mux2::setstate(const unsigned int st)
{
	state = (st?true:false);
}

void mvm::core::mux2::setstate(const bool st)
{
	state = st;
}
