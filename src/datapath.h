/*
 *  datapath.h
 *  Datapath class definition
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
#ifndef _MVM_DATAPATH_H
#define _MVM_DATAPATH_H

#include "instruction_memory.h"
#include "stage1_if.h"
#include "stage2_id.h"
#include "stage3_ex.h"
#include "stage4_mem.h"
#include "stage5_wb.h"

class datapath
{
public:
	datapath();
	~datapath();
	void tick();
	bool disassemble(const unsigned int op);

private:
	control *ctrl;
	stage1_if *stage1;
	stage2_id *stage2;
	stage3_ex *stage3;
	stage4_mem *stage4;
	stage5_wb *stage5;
	instruction_memory *im;
};

#endif /* _MVM_DATAPATH_H */
