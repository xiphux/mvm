/*
 *  mvm.cpp
 *  Mvm core class implementation
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
#include <fstream>
#include "basecmd.h"
#include "parser/ophandlers.h"
#include "core/vm.h"
#include "console.h"

int main(int argc, char **argv)
{
	BaseCmd *cmd = BaseCmd::initialize(argc,argv);
	cmd->addoption('d',"debug",OPTPARM_NONE,"","Enable debugging output");
	cmd->addoption('i',"interactive",OPTPARM_NONE,"","Enable interactive console");
	cmd->parse();
	if (cmd->result("help")) {
		cmd->usage("Mvm",VERSION_STRING);
		delete cmd;
		return 0;
	} else if (cmd->result("version")) {
#ifdef PACKAGE_STRING
		printf("%s\n",PACKAGE_STRING);
#elif defined(PACKAGE_VERSION)||defined(VERSION)
#if defined(PACKAGE_NAME)
		printf("%s %s\n",PACKAGE_NAME,VERSION_STRING);
#elif defined(PACKAGE)
		printf("%s %s\n",PACKAGE,VERSION_STRING);
#else
		printf("Mvm %s\n",VERSION_STRING);
#endif
#else
		printf("Mvm\n");
#endif
		printf("Copyright (C) 2005 Christopher Han <%s>\n",PACKAGE_BUGREPORT);
		printf("This program is licensed under the GNU General Public License\n");
		delete cmd;
		return 0;
	}
	bool debug = false;
	if (cmd->result("debug")) {
		debug = true;
		printf("Enabling debugging output\n");
	}
	vm *VM = new vm(debug);
	std::vector<std::string> files;
	for (int i = 1; i < argc; i++) {
		std::string tmp = argv[i];
		if (tmp.at(0) != '-')
			files.push_back(tmp);
	}

	if (cmd->result("interactive")) {
		bool complete = false;
		console *con = new console();
		if (!files.empty())
			VM->load_instructions(files.at(0));
		char ch;
		con->draw_prompt();
		std::string command;
		while (!complete) {
			ch = getchar();
			switch (ch) {
				case EOF:
					complete = true;
					break;

				case '\n':
					if (command.size()>0) {	
						unsigned int ret = con->read_command(command);
						if (ret == COMMAND_RUN)
							VM->run();
						else if (ret == COMMAND_STEP)
							VM->tick();
						else if (ret == COMMAND_QUIT)
							complete = true;
						else if (ret == COMMAND_HELP)
							con->usage();
						else if (ret == COMMAND_LOAD) {
							if (command.size()<=5) {
								std::cout << " Usage: " << command << " [FILENAME]" << std::endl;
							} else {
								VM->reset();
								VM->load_instructions(command.substr(5));
							}
						} else
							std::cout << " Invalid command" << std::endl;
					}
					command.clear();
					if (!complete)
						con->draw_prompt();
					break;
				default:
					command.push_back(ch);
					break;
			}
		}
		std::cout << std::endl;
		delete con;
	} else {
		if (files.empty()) {
			fprintf(stderr,"Error: no input file given\n");
			delete cmd;
			return 1;
		}
		for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); it++) {
			VM->load_instructions(*it);
			VM->run();
			VM->reset();
		}
	}
	delete cmd;
	return 0;
}
