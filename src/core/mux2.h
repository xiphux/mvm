/*
 *  mux2.h
 *  2-Way MUX class definition
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
#ifndef _MVM_MUX2_H
#define _MVM_MUX2_H

#include "basemux.h"
#include "gcollect.h"

namespace mvm
{
	namespace core
	{

		class mux2: public basemux
		{
		public:
			mux2();
			~mux2();
			unsigned int getstate();
			void setstate(const unsigned int st);
			void setstate(const bool st);
		private:
			bool state;
		};

	}
}

#endif /* _MVM_MUX2_H */
