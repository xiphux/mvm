/*
 *  exmux3.h
 *  EX stage 3-input MUX class definition
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
 *  $Id: exmux3.h 210 2005-10-15 04:18:35Z xiphux $
 */
#ifndef _MVM_EXMUX3_H
#define _MVM_EXMUX3_H

#include "basemux.h"
#include "gcollect.h"

namespace mvm
{
	namespace core
	{

		class exmux3: public basemux
		{
		public:
			exmux3();
			~exmux3();
			bool get_signal1();
			bool get_signal2();
			void set_signal1(const bool s);
			void set_signal2(const bool s);
			int mux(const int a, const int b, const int c);
		private:
			bool signal1;
			bool signal2;
		};

	}
}

#endif /* _MVM_EXMUX3_H */
