/*
 *  idmux.h
 *  ID stage MUX class definition
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
#ifndef _MVM_IDMUX_H
#define _MVM_IDMUX_H

#include "basemux.h"

class idmux
{
public:
	idmux();
	~idmux();
	bool get_signal1();
	bool get_signal2();
	void set_signal1(const bool s);
	void set_signal2(const bool s);
	int mux(const int a, const int b);
private:
	bool signal1;
	bool signal2;
};

#endif /* _MVM_IDMUX_H */
