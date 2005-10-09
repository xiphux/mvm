/*
 *  latch_mem_wb.h
 *  MEM/WB pipeline latch class definition
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
#ifndef _MVM_LATCH_MEM_WB_H
#define _MVM_LATCH_MEM_WB_H

#include "register32.h"
#include "latch.h"
#include "gcollect.h"

namespace mvm
{
	namespace core
	{

		class latch_mem_wb
		{
		public:
			latch_mem_wb();
			~latch_mem_wb();
			struct latch_wb WB;
			register32 *DataR;
			register32 *Data;
			register32 *RegW;
		};

	}
}

#endif /* _MVM_LATCH_MEM_WB_H */
