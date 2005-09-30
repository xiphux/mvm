/*
 *  rtype.h
 *  R-Type operation class definition
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
#ifndef _MVM_RTYPE_H
#define _MVM_RTYPE_H

#include <string>
#include <vector>
#include "operation.h"

namespace mvm
{
	namespace parser
	{

		class rtype: public operation
		{
		public:
			rtype(const unsigned char o, const unsigned char s, const unsigned char t, const unsigned char d, const unsigned char sh, const unsigned char f);
			rtype(unsigned int ins);
			rtype(std::string cmd, std::vector<std::string> params);
			virtual ~rtype();
			unsigned int instruction();
		private:
			void assemble(const unsigned char o, const unsigned char s, const unsigned char t, const unsigned char d, const unsigned char sh, const unsigned char f);
			unsigned char opcode;
			unsigned char rs;
			unsigned char rt;
			unsigned char rd;
			unsigned char shamt;
			unsigned char funct;
		};

	}
}

#endif /* _MVM_RTYPE_H */
