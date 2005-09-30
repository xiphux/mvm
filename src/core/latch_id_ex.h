/*
 *  latch_id_ex.h
 *  ID/EX pipeline latch class definition
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
#ifndef _MVM_LATCH_ID_EX_H
#define _MVM_LATCH_ID_EX_H

#include "register32.h"

namespace mvm
{
	namespace core
	{

		class latch_id_ex
		{
		public:
			latch_id_ex();
			~latch_id_ex();
			register32 *WB;
			register32 *M;
			register32 *EX;
			register32 *PCpiu4;
			register32 *Data1;
			register32 *Data2;
			register32 *imm;
			register32 *RS;
			register32 *RT;
			register32 *RD;
			register32 *OP;
		};

	}
}

#endif /* _MVM_LATCH_ID_EX_H */
