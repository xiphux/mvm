/*
 *  convenience.cpp
 *  Convenience function implementations
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
#include "convenience.h"

void mvm::basic::strip_leading_whitespace(std::string &str)
{
	if (str.size() < 1)
		return;
	char ch = str.at(0);
	while (ch == ' ' || ch == '\t') {
		str.erase(0,1);
		if (str.empty())
			break;
		ch = str.at(0);
	}
}

void mvm::basic::strip_trailing_whitespace(std::string &str)
{
	if (str.size() <= 1)
		return;
	std::string::size_type s = str.size()-1;
	char ch = str.at(str.size()-1);
	while (ch == ' ' || ch == '\t') {
		str.erase(s,1);
		if (str.empty())
			break;
		s = str.size()-1;
		ch = str.at(s);
	}
}

void mvm::basic::strip_comments(std::string &str)
{
	std::string::size_type i = str.find_first_of('#');
	if (i != std::string::npos)
		str.erase(i);
}

std::vector<std::string> mvm::basic::tokenize(std::string &str, const char delim)
{
	std::vector<std::string> params;
	std::string parm;
	char ch;
	while (str.size()>0) {
		ch = str.at(0);
		if (ch != delim)
			parm.push_back(ch);
		else {
			params.push_back(parm);
			parm.clear();
		}
		str.erase(0,1);
	}
	params.push_back(parm);
	return params;
}

void mvm::basic::binaryprint(const unsigned int val, const bool zero)
{
	if (!zero && !val)
		return;
	unsigned int mask = 0x80000000;
	for (int i = 0; i < 32; i++) {
		printf("%d",(val&mask?1:0));
		mask >>= 1;
	}
	printf("\n");
}
