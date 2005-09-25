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
#include "vm.h"

int main(int argc, char **argv)
{
	BaseCmd *cmd = BaseCmd::initialize(argc,argv);
	cmd->addoption('d',"debug",OPTPARM_NONE,"","Enable debugging output");
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
	std::string file;
	for (int i = 1; i < argc; i++) {
		std::string tmp = argv[i];
		if (tmp.at(0) != '-') {
			file = tmp;
			break;
		}
	}
	if (file.empty()) {
		fprintf(stderr,"Error: no input file given\n");
		return 1;
	}
	vm *VM = new vm(debug);
	VM->load_instructions(file);
	VM->run();
	return 0;
}
