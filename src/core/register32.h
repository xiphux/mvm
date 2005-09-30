/*
 *  register32.h
 *  32-bit register class definition
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
#ifndef _MVM_REGISTER32_H
#define _MVM_REGISTER32_H

namespace mvm
{
	namespace core
	{

		class register32
		{
		public:
			register32();
			~register32();
			unsigned int get();
			void set(const unsigned int v);
		private:
			unsigned int data;
		};

	}
}

#endif /* _MVM_REGISTER32_H */
