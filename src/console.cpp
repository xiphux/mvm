/*
 *  console.cpp
 *  Interactive console class implementation
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
#include <iostream>
#include "console.h"
#include "basic/convenience.h"

console::console()
{
	consolecmd *a = new consolecmd("quit","Exit to shell",COMMAND_QUIT);
	a->addalias("exit");
	a->addalias("logout");
	char ch[2];
	snprintf(ch,1,"%c",EOF);
	a->addalias(ch);
	commands.push_back(a);
	consolecmd *b = new consolecmd("step","Execute one clock cycle",COMMAND_STEP);
	b->addalias("next");
	commands.push_back(b);
	consolecmd *c = new consolecmd("run","Finish executing the rest of the program",COMMAND_RUN);
	c->addalias("continue");
	commands.push_back(c);
	consolecmd *d = new consolecmd("help","Display this helptext",COMMAND_HELP);
	commands.push_back(d);
	consolecmd *e = new consolecmd("load","Load instructions from a file",COMMAND_LOAD);
	e->addalias("file");
	commands.push_back(e);
}

console::~console()
{
	for (std::vector<consolecmd*>::iterator it = commands.begin(); it != commands.end(); it++) {
		delete *it;
	}
	commands.clear();
}

void console::draw_prompt()
{
	std::cout << "Mvm:: ";
}

unsigned int console::read_command(std::string &cmd)
{
	strip_leading_whitespace(cmd);
	strip_trailing_whitespace(cmd);
	std::string tmp = cmd;
	if (tmp.find_first_of(' ')!=std::string::npos)
		tmp = tmp.substr(0,tmp.find_first_of(' '));
	for (std::vector<consolecmd*>::iterator it = commands.begin(); it != commands.end(); it++) {
		if (**it == tmp)
			return (*it)->code;
	}
	return COMMAND_NULL;
}

void console::usage()
{
	std::cout << " Known Mvm commands: " << std::endl << std::endl;
	for (std::vector<consolecmd*>::iterator it = commands.begin(); it != commands.end(); it++) {
		std::cout << "  " << (*it)->helpstring() << std::endl;
	}
}
