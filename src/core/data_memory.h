/*
 *  data_memory.h
 *  Data memory class definition
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
#ifndef _MVM_DATA_MEMORY_H
#define _MVM_DATA_MEMORY_H

#include <vector>

namespace mvm
{
	namespace core
	{

		class data_memory
		{
		public:
			data_memory();
			~data_memory();
			unsigned char read_data(const unsigned int addr);
			void write_data(const unsigned int addr, const unsigned char input);
		private:
			struct databyte {
				unsigned int addr;
				unsigned char data;
			};
			std::vector<struct databyte> data;
		};
	
	}	
}

#endif /* _MVM_DATA_MEMORY_H */
