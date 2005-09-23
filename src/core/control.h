/*
 *  control.h
 *  Control class definition
 *  Copyright (C) 2005 Christopher han
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
#ifndef _MVM_CONTROL_H
#define _MVM_CONTROL_H

#define SIGNAL_NULL 0
#define SIGNAL_JUMP 1
#define SIGNAL_PCSRC 2
#define SIGNAL_WB 3
#define SIGNAL_M 4
#define SIGNAL_EX 5

class control
{
public:
	control();
	~control();
	void read_instruction(const unsigned int inst, const unsigned int sig);

	bool RegWrite;
	bool MemRead;
	bool MemWrite;
	bool IRWrite;
	bool PCWrite;
	bool PCWriteCond;
	bool CauseWrite;
	bool EPCWrite;
	unsigned char RegDst;
	unsigned char ALUSrcA;
	unsigned char MemtoReg;
	unsigned char IorD;
	unsigned char IntCause;
	unsigned char ALUOp;
	unsigned char ALUSrcB;
	unsigned char PCSource;
};

#endif /* _MVM_CONTROL_H */
