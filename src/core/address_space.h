/*
 *  address_space.h
 *  Address space class definition
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
 *  $Id: address_space.h 210 2005-10-15 04:18:35Z xiphux $
 */
#ifndef _MVM_ADDRESS_SPACE_H
#define _MVM_ADDRESS_SPACE_H

#include "instruction_memory.h"
#include "data_memory.h"
#include "stack.h"
#include "gcollect.h"

namespace mvm
{
	namespace core
	{

		class address_space
		{
		public:
			address_space();
			virtual ~address_space();
			instruction_memory *im;
			data_memory *dm;
			stack *stk;
		};

	}
}

#endif /* _MVM_ADDRESS_SPACE_H */
