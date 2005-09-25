/*
 *  Win32Cmd.cpp
 *  Win32 commandline parser class definition
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
#include "win32cmd.h"

/**
 * Constructor
 * @param c argument count
 * @param v array of argument strings
 */
Win32Cmd::Win32Cmd(int c, char **v)
{
	argc = c;
	argv = v;
}

/**
 * Destructor
 */
Win32Cmd::~Win32Cmd()
{
}

/**
 * parse()
 * Iterates through and processes arguments
 */
void Win32Cmd::parse()
{
	for (int i = 1; i < argc; i++) {
		std::string arg = argv[i];
		if (!arg.empty() && arg.at(0) == '/') {
			if (arg.size() >=2) {
				bool valid = false;
				std::string mainpart = arg.substr(1);
				for (std::vector<struct option>::iterator it = options.begin(); it != options.end(); it++) {
					char so[2];
					snprintf(so,2,"%c",it->shortopt);
					if (mainpart == it->longopt || mainpart == std::string(so)) {
						it->given = true;
						if (it->parmtype != OPTPARM_NONE) {
							std::string next;
							next = argv[++i];
							if (it->parmtype == OPTPARM_INT)
								it->ret.intret = atoi(next.c_str());
							else
								strcpy(it->ret.stringret,next.c_str());
						}
						valid = true;
						break;
					}
				}
				if (!valid)
					throw invalidoption(arg);
			} else
				throw invalidoption(arg);
		}
	}
}

void Win32Cmd::usage(std::string program, std::string version)
{
	BaseCmd::usage(program, version);
	for (std::vector<struct option>::iterator it = options.begin(); it != options.end(); it++) {
		std::cout << "\t";
		if (it->shortopt) {
			std::cout << "/" << it->shortopt;
			if (it->parmtype != OPTPARM_NONE)
				std::cout << " [" << it->parmname << "]";
			std::cout << ", ";
		} else {
			std::cout << "  ";
			if (it->parmtype != OPTPARM_NONE)
				std::cout << "\t";
		}
		if (!it->longopt.empty()) {
			std::cout << "/" << it->longopt;
			if (it->parmtype != OPTPARM_NONE)
				std::cout << " [" << it->parmname << "]";
		} else {
			std::cout << "\t";
			if (it->parmtype != OPTPARM_NONE)
				std::cout << "\t";
		}
		std::cout << "\t";
		if (it->longopt.size()<=10)
			std::cout << "\t";
		std::cout << it->desc;
		std::cout << std::endl;
	}
}

