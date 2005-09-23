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
#include "parser/ophandlers.h"

int main(int argc, char **argv)
{
	if (argc<2) {
		fprintf(stderr,"Error: no input file given\n");
		return 1;
	}
	std::fstream infile(argv[1],std::ios::in);
	std::string buf;
	operation *op;
	while (!infile.eof()) {
		getline(infile,buf);
		strip_comments(buf);
		strip_trailing_whitespace(buf);
		if (!buf.empty()) {
			printf("%s\n",buf.c_str());
			op = assembly_to_op(buf);
			if (op) {
				binaryprint(op->instruction(),false);
				delete op;
			}
		}
	}
	infile.close();
	return 0;
}
