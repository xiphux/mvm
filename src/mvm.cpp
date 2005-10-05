/*
 *  mvm.cpp
 *  Mvm core implementation
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
#include "util/basecmd.h"
#include "parser/ophandlers.h"
#include "util/console.h"
#include "mvm.h"
#ifdef NCURSES_GUI
#include <signal.h>
#include "gui/gui.h"
#endif

static bool complete = false;
static bool debug = false;
static bool loaded = false;
mvm::core::vm *VM = 0;
static mvm::util::console *con = 0;
#ifdef NCURSES_GUI
static mvm::gui::gui *maingui = 0;
#endif
static std::vector<std::string> files;
static unsigned int maxx,maxy;

static inline void display_version_string()
{
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
}

static inline void trydebug(std::string &cmd)
{
	if (cmd.size()<6) {
		std::cout << " Debugging: ";
		if (debug)
			std::cout << " enabled";
		else
			std::cout << " disabled";
		std::cout << std::endl;
	} else {
		std::string tmp = cmd.substr(6);
		if (tmp == "true" || tmp == "on") {
			debug = true;
			std::cout << " Debugging enabled" << std::endl;
		} else if (tmp == "false" || tmp == "off") {
			debug = false;
			std::cout << " Debugging disabled" << std::endl;
		} else
			std::cout << " Usage: " << cmd.substr(0,cmd.find_first_of(' ')) << " [STATE]" << std::endl;
		VM->set_debug(debug);
	}
}

static inline void try_op(const unsigned int state)
{
	if (loaded) {
		switch (state) {
			case COMMAND_RUN:
				VM->run();
				break;
			case COMMAND_STEP:
				VM->tick();
				break;
			case COMMAND_LIST:
				VM->print_instructions();
				break;
		}
	} else
		std::cout << " No file loaded" << std::endl;
}

static inline void process_input(std::string &command)
{
	if (command.size()>0) {	
		unsigned int ret = con->read_command(command);
		if (ret == COMMAND_RUN || ret == COMMAND_STEP || ret == COMMAND_LIST)
			try_op(ret);
		else if (ret == COMMAND_QUIT)
			complete = true;
		else if (ret == COMMAND_HELP)
			con->usage();
		else if (ret == COMMAND_DEBUG)
			trydebug(command);
		else if (ret == COMMAND_LOAD) {
			if (command.size()<=5)
				std::cout << " Usage: " << command << " [FILENAME]" << std::endl;
			else {
				VM->reset();
				if (VM->load_instructions(command.substr(5))) {
					std::cout << " Successfully loaded instructions from file ";
					loaded = true;
				} else
					std::cout << " Failed to load instructions from file ";
				std::cout << command.substr(5) << std::endl;
			}
		} else
			std::cout << " Invalid command" << std::endl;
	}
	command.clear();
}

static inline void run_console()
{
	con = new mvm::util::console();
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
				process_input(command);
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
}

#ifdef NCURSES_GUI
static void handle_resize(int sig)
{
	getmaxyx(stdscr,maxx,maxy);
	maingui->resize(maxx,maxy);
}

static inline void run_gui()
{
	initscr();
	clear();
	start_color();
	cbreak();
	keypad(stdscr,TRUE);
	noecho();
	curs_set(0);
	werase(stdscr);
	signal(SIGWINCH,handle_resize);
	maxy = LINES;
	maxx = COLS;
	maingui = new mvm::gui::gui(0,0,maxy,maxx);
	//box(stdscr,0,0);
	if (!files.empty())
		VM->load_instructions(files.at(0));
	int ch;
	while (!maingui->complete) {
		maingui->draw();
		maingui->refresh();
		maingui->keypressed(getch());
	}
	curs_set(1);
	endwin();
	return;
}
#endif

int main(int argc, char **argv)
{
	mvm::util::BaseCmd *cmd = mvm::util::BaseCmd::initialize(argc,argv);
	cmd->addoption('d',"debug",OPTPARM_NONE,"","Enable debugging output");
	cmd->addoption('b',"batch",OPTPARM_NONE,"","Run entire file (no console)");
#ifdef NCURSES_GUI
	cmd->addoption('g',"gui",OPTPARM_NONE,"","Use ncurses gui");
#endif
	cmd->parse();
	if (cmd->result("help")) {
		cmd->usage("Mvm",VERSION_STRING);
		delete cmd;
		return 0;
	} else if (cmd->result("version")) {
		display_version_string();
		delete cmd;
		return 0;
	}
	if (cmd->result("debug")) {
		debug = true;
		printf("Enabling debugging output\n");
	}
	VM = new mvm::core::vm(debug);
	for (int i = 1; i < argc; i++) {
		std::string tmp = argv[i];
		if (tmp.at(0) != '-') {
			files.push_back(tmp);
			loaded = true;
		}
	}

	if (cmd->result("batch")) {
		if (files.empty()) {
			fprintf(stderr,"Error: no input file given\n");
			delete cmd;
			delete VM;
			return 1;
		}
		for (std::vector<std::string>::iterator it = files.begin(); it != files.end(); it++) {
			VM->load_instructions(*it);
			VM->run();
			VM->reset();
		}
	} else
#ifdef NCURSES_GUI
	if (cmd->result("gui")) {
		run_gui();
		delete maingui;
	} else
#endif
		run_console();
	delete VM;
	delete cmd;
	return 0;
}
