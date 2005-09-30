/*
 *  stage3_ex.h
 *  Execution stage class definition
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
#ifndef _MVM_STAGE3_EX_H
#define _MVM_STAGE3_EX_H

#include "stage.h"

namespace mvm
{
	namespace core
	{

		class stage3_ex: public stage
		{
		public:
			stage3_ex();
			virtual ~stage3_ex();
			bool tick();
		};

	}
}

#endif /* _MVM_STAGE3_EX_H */
