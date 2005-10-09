/*
 *  latch_ex_mem.cpp
 *  EX/MEM pipeline latch class implementation
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
#include "latch_ex_mem.h"

mvm::core::latch_ex_mem::latch_ex_mem()
{
	RIS = new register32();
	DataW = new register32();
	RegW = new register32();
	WB.RegWrite = false;
	WB.WBData = false;
	M.MemRead = false;
	M.MemWrite = false;
	M.Word = false;
}

mvm::core::latch_ex_mem::~latch_ex_mem()
{
	delete RIS;
	delete DataW;
	delete RegW;
}

