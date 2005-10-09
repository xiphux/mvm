/*
 *  BaseCmd.h
 *  Base structure for commandline parser class definition
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
 */
#ifndef _MVM_BASECMD_H
#define _MVM_BASECMD_H

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <vector>
#include <string>
#include <iostream>
#include "gcollect.h"

#define OPTPARM_NONE 0
#define OPTPARM_INT 1
#define OPTPARM_STRING 2


#ifdef PACKAGE_VERSION
#define VERSION_STRING PACKAGE_VERSION
#elif defined(VERSION)
#define VERSION_STRING VERSION
#else
#define VERSION_STRING ""
#endif

#ifndef PACKAGE_BUGREPORT
#define PACKAGE_BUGREPORT "cfh@gwu.edu"
#endif

namespace mvm
{
	namespace util
	{

		class BaseCmd
		{
		public:
			BaseCmd();
			virtual ~BaseCmd();
			virtual void usage(std::string program, std::string version);
			void addoption(const char shortopt, std::string longopt, unsigned int parmtype, std::string parmname, std::string desc);
			void deloption(const char o);
			void deloption(std::string o);
			virtual void parse() = 0;
			static BaseCmd *initialize(int c, char **v);
			bool result(const char o);
			bool result(std::string o);
			bool result(const char o, int &ret);
			bool result(std::string o, int &ret);
			bool result(const char o, std::string &ret);
			bool result(std::string o, std::string &ret);
		protected:
			struct option {
				char shortopt;
				std::string longopt;
				unsigned int parmtype;
				std::string parmname;
				std::string desc;
				bool given;
				union {
					int intret;
					char *stringret;
				} ret;
			};
			std::vector<struct option> options;
			int argc;
			char **argv;
			int invalidoption(std::string opt);
		};

	}
}

#endif /* _MVM_BASECMD_H */
