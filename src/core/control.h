/*
 * control.h
 * Control class definition
 * Copyright (C) 2005 Christopher han
 */
#ifndef MVM_CONTROL_H
#define MVM_CONTROL_H

class control
{
public:
	control();
	~control();

	bool RegDst;
	bool RegWrite;
	bool ALUSrcA;
	bool MemRead;
	bool MemWrite;
	bool MemtoReg;
	bool IorD;
	bool IRWrite;
	bool PCWrite;
	bool PCWriteCond;
	unsigned char ALUOp;
	unsigned char ALUSrcB;
	unsigned char PCSource;
};

#endif /* MVM_CONTROL_H */
