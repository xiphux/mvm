/*
 *  ptype.h
 *  Pseudo operation class definition
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
 *  $Id: ptype.h 210 2005-10-15 04:18:35Z xiphux $
 */
#ifndef _MVM_PTYPE_H
#define _MVM_PTYPE_H

#include <string>
#include <vector>
#include "operation.h"
#include "gcollect.h"

namespace mvm
{
	namespace parser
	{

		class ptype: public operation
		{
		public:
			ptype(std::string cmd, std::vector<std::string> params);
			virtual ~ptype();
			unsigned int instruction(){return 0;}
			virtual bool pseudo(){return true;}
			std::vector<operation*> ops;
			std::vector<std::string> ins;
		private:
			void translate();
			std::string command;
			std::vector<std::string> parms;
			void translate_move();
			void translate_li();
			void translate_lui();
			void translate_la();
			void translate_beqz();
			void translate_bnez();
		};

	}
}

#endif /* _MVM_PTYPE_H */
