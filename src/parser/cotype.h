/*
 *  cotype.h
 *  Coprocessor operation class definition
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
#ifndef _MVM_COTYPE_H
#define _MVM_COTYPE_H

#include <string>
#include <vector>
#include "operation.h"
#include "gcollect.h"

namespace mvm
{
	namespace parser
	{

		class cotype: public operation
		{
		public:
			cotype(const unsigned char o, const unsigned char fmt, const unsigned char t, const unsigned char s, const unsigned char d, const unsigned char f);
			cotype(unsigned int ins);
			cotype(std::string cmd, std::vector<std::string> params);
			virtual ~cotype();
			unsigned int instruction();
			unsigned int coprocessor();
		private:
			void assemble(const unsigned char o, const unsigned char fmt, const unsigned char t, const unsigned char s, const unsigned char d, const unsigned char f);
			unsigned char opcode;
			unsigned char format;
			unsigned char ft;
			unsigned char fs;
			unsigned char fd;
			unsigned char funct;
		};

	}
}

#endif /* _MVM_COTYPE_H */
