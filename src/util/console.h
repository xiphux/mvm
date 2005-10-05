/*
 *  console.h
 *  Interactive console class definition
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
#ifndef _MVM_CONSOLE_H
#define _MVM_CONSOLE_H

#include <string>
#include "consolecmd.h"

#define COMMAND_NULL 0
#define COMMAND_QUIT 1
#define COMMAND_STEP 2
#define COMMAND_RUN 3
#define COMMAND_HELP 4
#define COMMAND_LOAD 5
#define COMMAND_LIST 6
#define COMMAND_DEBUG 7
#define COMMAND_REGS 8

namespace mvm
{
	namespace util
	{

		class console
		{
		public:
			console();
			~console();
			void draw_prompt();
			void usage();
			unsigned int read_command(std::string &cmd);
		private:
			std::vector<consolecmd*> commands;
		};

	}
}

#endif /* _MVM_CONSOLE_H */
