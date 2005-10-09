/*
 *  ophandlers.h
 *  Opcode handler function definitions
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
#ifndef _MVM_OPHANDLERS_H
#define _MVM_OPHANDLERS_H

#include <string>
#include "operation.h"
#include "gcollect.h"

#define MODE_NONE 0
#define MODE_DATA 1
#define MODE_TEXT 2

namespace mvm
{
	namespace parser
	{
		
		unsigned int opcode_type(const unsigned char opcode);
		unsigned int instruction_type(std::string ins);
		std::string extract_operation(std::string &str);
		std::string readable_register(const unsigned int reg);
		unsigned int dereference_register(std::string reg);
		bool dereference_pointer(std::string pointer, std::string &imm, std::string &rs);
		unsigned int dereference_label(std::string label);
		void read_mode(std::string &sect);
		operation *assembly_to_op(std::string op);
		std::string opcode_to_assembly(const unsigned int opcode);

	}
}


#endif /* _MVM_OPHANDLERS_H */
