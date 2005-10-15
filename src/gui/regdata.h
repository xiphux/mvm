/*
 *  regdata.h
 *  Register data list class definition
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
 *  $Id: regdata.h 210 2005-10-15 04:18:35Z xiphux $
 */
#ifndef _MVM_REGDATA_H
#define _MVM_REGDATA_H

#include "base.h"
#include "gcollect.h"

namespace mvm
{
	namespace gui
	{

		class regdata
		{
		public:
			regdata(const int sy,const int sx, const int my, const int mx);
			virtual ~regdata();
			void reprint();
			void refresh();
		private:
			WINDOW *regwin;
			int x0,y0,x1,y1;
		};

	}
}

#endif /* _MVM_REGDATA_H */
