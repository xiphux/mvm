/*
 *  consolecmd.cpp
 *  Console command class implementation
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
#include "consolecmd.h"

mvm::util::consolecmd::consolecmd(std::string c, std::string d, const unsigned int cod):code(cod),cmd(c),desc(d)
{
}

mvm::util::consolecmd::~consolecmd()
{
	aliases.clear();
}

std::string mvm::util::consolecmd::getcmd()
{
	return cmd;
}

std::string mvm::util::consolecmd::getdesc()
{
	return desc;
}

bool mvm::util::consolecmd::addalias(std::string a)
{
	for (std::vector<std::string>::iterator it = aliases.begin(); it != aliases.end(); it++) {
		if (*it == a)
			return false;
	}
	aliases.push_back(a);
	return true;
}

std::string mvm::util::consolecmd::helpstring()
{
	std::string ret = cmd;
	int j = 0;
	for (std::vector<std::string>::iterator it = aliases.begin(); it != aliases.end(); it++) {
		if (it->size()>1) {
			ret += ", " + *it;
			j++;
		}
	}
	for (int i = 0; i < (5-j); i++)
		ret += "\t";
	ret += desc;
	return ret;
}

bool mvm::util::consolecmd::operator== (std::string c)
{
	if (c == cmd)
		return true;
	for (std::vector<std::string>::iterator it = aliases.begin(); it != aliases.end(); it++) {
		if (*it == c)
			return true;
	}
	return false;
}
