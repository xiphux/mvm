/*
 *  latch_id_ex.cpp
 *  ID/EX pipeline latch class implementation
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
 *  $Id: latch_id_ex.cpp 210 2005-10-15 04:18:35Z xiphux $
 */
#include "latch_id_ex.h"

mvm::core::latch_id_ex::latch_id_ex()
{
	PCpiu4 = new register32();
	Data1 = new register32();
	Data2 = new register32();
	imm = new register32();
	RS = new register32();
	RT = new register32();
	RD = new register32();
	OP = new register32();
	WB.RegWrite = false;
	WB.WBData = false;
	M.MemRead = false;
	M.MemWrite = false;
	M.Word = false;
	EX.RegDest = false;
	EX.AluOP1 = false;
	EX.AluOP2 = false;
	EX.AluSrc = false;
}

mvm::core::latch_id_ex::~latch_id_ex()
{
	delete PCpiu4;
	delete Data1;
	delete Data2;
	delete imm;
	delete RS;
	delete RT;
	delete RD;
	delete OP;
}

