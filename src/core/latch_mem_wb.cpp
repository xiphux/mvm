/*
 *  latch_mem_wb.cpp
 *  MEM/WB pipeline latch class implementation
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
 *  $Id: latch_mem_wb.cpp 210 2005-10-15 04:18:35Z xiphux $
 */
#include "latch_mem_wb.h"

mvm::core::latch_mem_wb::latch_mem_wb()
{
	DataR = new register32();
	Data = new register32();
	RegW = new register32();
	WB.RegWrite = false;
	WB.WBData = false;
}

mvm::core::latch_mem_wb::~latch_mem_wb()
{
	delete DataR;
	delete Data;
	delete RegW;
}

