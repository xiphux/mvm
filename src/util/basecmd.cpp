/*
 *  BaseCmd.cpp
 *  Base structure for commandline parser class implementation
 *  Copyright (C) 2005 Christopher Han <xiphux@gmail.com>
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
 *  $Id: basecmd.cpp 210 2005-10-15 04:18:35Z xiphux $
 */
#include "basecmd.h"
#ifdef _WIN32
#include "win32cmd.h"
#else
#include "posixcmd.h"
#endif

/**
 * Constructor
 */
mvm::util::BaseCmd::BaseCmd()
{
	addoption('h',"help",OPTPARM_NONE,"","This help message");
	addoption('V',"version",OPTPARM_NONE,"","Display program version");
}

/**
 * Destructor
 */
mvm::util::BaseCmd::~BaseCmd()
{
}

/**
 * initialize()
 * Returns a new Win32Cmd or PosixCmd instance,
 * depending on the platform
 * @param c argument count
 * @param v array of argument strings
 */
mvm::util::BaseCmd *mvm::util::BaseCmd::initialize(int c, char **v)
{
#ifdef _WIN32
	return new Win32Cmd(c,v);
#else
	return new PosixCmd(c,v);
#endif
}

/**
 * addoption()
 * Adds an option to the list of recognized options
 * @param shortopt short option letter
 * @param longopt long option string
 * @param parmtype type of parameter the argument takes
 * @param desc description string
 */
void mvm::util::BaseCmd::addoption(const char shortopt, std::string longopt, const unsigned int parmtype, std::string parmname, std::string desc)
{
	struct option opt;
	opt.shortopt = shortopt;
	opt.longopt = longopt;
	opt.parmtype = parmtype;
	opt.parmname = parmname;
	opt.desc = desc;
	opt.given = false;
	options.push_back(opt);
}

/**
 * deloption()
 * Remove an option from the list of recognized options
 * @param o short option to find
 */
void mvm::util::BaseCmd::deloption(const char o)
{
	for (std::vector<struct option>::iterator it = options.begin(); it != options.end(); it++) {
		if (it->shortopt == o) {
			options.erase(it);
			break;
		}
	}
}

/**
 * deloption()
 * Remove an option from the list of recognized options
 * @param o long option to find
 */
void mvm::util::BaseCmd::deloption(std::string o)
{
	for (std::vector<struct option>::iterator it = options.begin(); it != options.end(); it++) {
		if (it->longopt == o) {
			options.erase(it);
			break;
		}
	}
}

/**
 * usage()
 * Print usage message
 */
void mvm::util::BaseCmd::usage(std::string program, std::string version)
{
	if (!program.empty()) {
		std::cout << program;
		if (!version.empty())
			std::cout << " " << version;
		std::cout << std::endl;
		std::cout << "Copyright (C) 2005 Christopher Han <" << PACKAGE_BUGREPORT << ">" << std::endl;
		std::cout << "This program is licensed under the GNU General Public License" << std::endl;
	}
	std::cout << "Usage: " << argv[0] << " [OPTIONS]" << std::endl;
}

/**
 * result()
 * Gets the post-parse result of an OPTPARM_NONE option
 * @param o short option to get
 */
bool mvm::util::BaseCmd::result(const char o)
{
	for (std::vector<struct option>::iterator it = options.begin(); it != options.end(); it++) {
		if (it->shortopt == o && it->parmtype == OPTPARM_NONE)
			return it->given;
	}
	return false;
}

/**
 * result()
 * Gets the post-parse result of an OPTPARM_NONE option
 * @param o long option to get
 */
bool mvm::util::BaseCmd::result(std::string o)
{
	for (std::vector<struct option>::iterator it = options.begin(); it != options.end(); it++) {
		if (it->longopt == o && it->parmtype == OPTPARM_NONE)
			return it->given;
	}
	return false;
}

/**
 * result()
 * Gets the post-parse result of an OPTPARM_INT option
 * @param o short option to get
 * @param ret reference to int where result should be stored
 */
bool mvm::util::BaseCmd::result(const char o, int &ret)
{
	for (std::vector<struct option>::iterator it = options.begin(); it != options.end(); it++) {
		if (it->shortopt == o && it->parmtype == OPTPARM_INT) {
			if (it->given)
				ret = it->ret.intret;
			return it->given;
		}
	}
	return false;
}

/**
 * result()
 * Gets the post-parse result of an OPTPARM_INT option
 * @param o long option to get
 * @param ret reference to int where result should be stored
 */
bool mvm::util::BaseCmd::result(std::string o, int &ret)
{
	for (std::vector<struct option>::iterator it = options.begin(); it != options.end(); it++) {
		if (it->longopt == o && it->parmtype == OPTPARM_INT) {
			if (it->given)
				ret = it->ret.intret;
			return it->given;	
		}
	}
	return false;
}

/**
 * result()
 * Gets the post-parse result of an OPTPARM_STRING option
 * @param o short option to get
 * @param ret reference to string where result should be stored
 */
bool mvm::util::BaseCmd::result(const char o, std::string &ret)
{
	for (std::vector<struct option>::iterator it = options.begin(); it != options.end(); it++) {
		if (it->shortopt == o && it->parmtype == OPTPARM_STRING) {
			if (it->given)
				ret = it->ret.stringret;
			return it->given;
		}
	}
	return false;
}

/**
 * result()
 * Gets the post-parse result of an OPTPARM_STRING option
 * @param o long option to get
 * @param ret reference to string where result should be stored
 */
bool mvm::util::BaseCmd::result(std::string o, std::string &ret)
{
	for (std::vector<struct option>::iterator it = options.begin(); it != options.end(); it++) {
		if (it->longopt == o && it->parmtype == OPTPARM_STRING) {
			if (it->given)
				ret = it->ret.stringret;
			return it->given;
		}
	}
	return false;
}

/**
 * invalidoption()
 * Prints usage message and terminates when given an invalid option
 * @param opt invalid option
 */
int mvm::util::BaseCmd::invalidoption(std::string opt)
{
	std::cerr << "BaseCmd error: Unrecognized option " << opt << std::endl;
	usage("","");
	exit(1);
	return 1;
}
