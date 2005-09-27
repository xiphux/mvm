/*
 *  datapath.cpp
 *  Datapath class implementation
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
#include "datapath.h"
#include "basic/convenience.h"
#include "parser/rtype.h"

datapath::datapath(): complete(false), debug(false), clock(0)
{
	ctrl = new control();
	im = new instruction_memory();
	pc = new PC();
	IDmux = new idmux();
	EXmux3 = new exmux3();
	EXmux4 = new exmux3();
	EXmux5 = new exmux2();
	alu = new ALU();
	acu = new alu_control_unit();
	stage1 = new stage1_if();
	stage2 = new stage2_id();
	stage3 = new stage3_ex();
	stage4 = new stage4_mem();
	stage5 = new stage5_wb();
	if_id = new latch_if_id();
	id_ex = new latch_id_ex();
	ex_mem = new latch_ex_mem();
	mem_wb = new latch_mem_wb();
	init();
}

datapath::~datapath()
{
	delete ctrl;
	delete im;
	delete pc;
	delete IDmux;
	delete EXmux3;
	delete EXmux4;
	delete EXmux5;
	delete acu;
	delete alu;
	delete stage1;
	delete stage2;
	delete stage3;
	delete stage4;
	delete stage5;
	delete if_id;
	delete id_ex;
	delete ex_mem;
	delete mem_wb;
}

void datapath::init()
{
	operation *o = new rtype(0);
	inst = new instruction("nop",o);
}

void datapath::advance_instructions()
{
	temp_IF_ID_PCpiu4 = pc->get_value()+1;
	unsigned int a = stage1->get_instruction();
	unsigned int b = stage2->get_instruction();
	unsigned int c = stage3->get_instruction();
	unsigned int d = stage4->get_instruction();
	if (!stall) {
		if (pc->get_value() > MemIstrDim)
			stage1->set_instruction(0x9);
		else
			stage1->set_instruction(pc->get_value());
		stage2->set_instruction(a);
	} else
		stage2->set_instruction(0x9);
	stage3->set_instruction(b);
	stage4->set_instruction(c);
	stage5->set_instruction(d);
}

bool datapath::detect_completion()
{
	unsigned int a = (stage1->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int b = (stage2->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int c = (stage3->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int d = (stage4->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int e = (stage5->get_instruction()==0x9 /* 1001 */ ?1:0);
	return ((a && b && c && d && e) && (clock > 2));
}

int datapath::execute_alu(const unsigned int wbdata)
{
	int ALUdata1 = EXmux3->mux(id_ex->Data1->get(),wbdata,ex_mem->RIS->get());
	int temp_EX_MEM_DataW = EXmux4->mux(id_ex->Data2->get(),wbdata,ex_mem->RIS->get());
	int ALUdata2 = EXmux5->mux(temp_EX_MEM_DataW,id_ex->imm->get());
	int AluOP = id_ex->EX->get()&0xcfffffff;
	int aluCtrl = acu->fire_signal(AluOP,id_ex->OP->get());
	return alu->execute(aluCtrl,ALUdata1,ALUdata2);
}

void datapath::tick()
{
	clock++;
	if (complete = detect_completion())
		return;

	unsigned int WBdata;
	if (mem_wb->WB->get()&0x1)
		WBdata = mem_wb->DataR->get();
	else
		WBdata = mem_wb->Data->get();
	if (mem_wb->WB->get()&0x8fffffff)
		mem_wb->RegW->set(WBdata);
	unsigned char RL1 = RS(inst->get_opcode()->instruction());
	unsigned char RL2 = RT(inst->get_opcode()->instruction());
	if (id_ex->M->get()>>31) {
		unsigned int rt = id_ex->RT->get();
		if (rt == RL1 || rt == RL2)
			stall = true;
	} else
		stall = false;
	unsigned int isBne = OPCODE(inst->get_opcode()->instruction());
	unsigned int ctrl_EX = id_ex->WB->get()>>31;
	unsigned int exDest;
	if (ctrl_EX && (isBne == 0x4 || isBne == 0x5)) {
		if (!(id_ex->EX->get()>>31))
			exDest = id_ex->RT->get();
		else
			exDest = id_ex->RD->get();
		if (exDest == RL1 || exDest == RL1)
			stall = true;
	}
	if (!stall)
		temp_instruction = im->fetch_instruction(pc->get_address());
	else
		temp_instruction = inst;

	advance_instructions();

	temp_ID_EX_imm = inst->get_opcode()->instruction() & 0xffff;
	temp_ID_EX_op = OPCODE(inst->get_opcode()->instruction());

	id_ex->PCpiu4->set(if_id->PCpiu4->get());

	unsigned int IsJump = OPCODE(inst->get_opcode()->instruction());
	unsigned int NewPC1, NewPC2;
	if (IsJump == 0x2 || IsJump == 0x3)
		NewPC1 = ADDR(inst->get_opcode()->instruction());
	else
		NewPC1 = temp_ID_EX_imm;

	NewPC2 = temp_IF_ID_PCpiu4;

	temp_ID_EX_Data1 = RL1;
	temp_ID_EX_Data2 = RL2;

	// Riferimenti alla memoria dati
	//    Save
	//    Load
	
	// Unit di propagazione 2b
	
	unsigned int jump = ctrl->read_instruction(inst->get_opcode()->instruction(), SIGNAL_JUMP);
	unsigned int temp_ctrl1 = ctrl1;
	ctrl1 &= jump;
	unsigned int ctrl2 = ctrl->read_instruction(inst->get_opcode()->instruction(), SIGNAL_PCSRC);
	ctrl2 = 0;
	if (!stall) {
		IDmux->set_signal1(ctrl1);
		IDmux->set_signal2(ctrl2);
		temp_PC = IDmux->mux(NewPC1,NewPC2);
	} else
		temp_PC = pc->get_value();
	unsigned int ID_discard = ctrl->read_instruction(inst->get_opcode()->instruction(),SIGNAL_DISCARD);
	unsigned int ID_MuxCtrl = ID_discard || stall;
	unsigned int ctrl_WB = ctrl->read_instruction(inst->get_opcode()->instruction(),SIGNAL_WB);
	unsigned int ctrl_M = ctrl->read_instruction(inst->get_opcode()->instruction(),SIGNAL_M);
	ctrl_EX = ctrl->read_instruction(inst->get_opcode()->instruction(),SIGNAL_EX);
	if (!ID_MuxCtrl) {
		temp_ID_EX_WB = ctrl_WB;
		temp_ID_EX_M = ctrl_M;
		temp_ID_EX_EX = ctrl_EX;
	} else {
		temp_ID_EX_WB = 0x0;
		temp_ID_EX_M = 0x0;
		temp_ID_EX_EX = 0x0;
	}

	temp_EX_MEM_RIS = execute_alu(WBdata);
	
	if (!(id_ex->EX->get()&0x8fffffff))
		temp_EX_MEM_RegW = id_ex->RT->get();
	else
		temp_EX_MEM_RegW = id_ex->RD->get();
	temp_MEM_WB_WB = ex_mem->WB->get();
	temp_MEM_WB_Data = ex_mem->RIS->get();
	if (ctrl1) {
		temp_instruction = 0x0;
		temp_IF_ID_PCpiu4 = 0x0;
		temp_IF_ID_IFdiscard = 0x0;
	}
	temp_EX_MEM_WB = id_ex->WB->get();
	temp_EX_MEM_M = id_ex->M->get();
	temp_MEM_WB_RegW = ex_mem->RegW->get();
	set_registers();
	if (debug)
		print_debug();
}

void datapath::print_debug()
{
	printf("id_ex->RS: ");
	binaryprint(id_ex->RS->get(),true);
	printf("id_ex->RT: ");
	binaryprint(id_ex->RT->get(),true);
	printf("id_ex->RD: ");
	binaryprint(id_ex->RD->get(),true);
	printf("id_ex->OP: ");
	binaryprint(id_ex->OP->get(),true);
	printf("id_ex->WB: ");
	binaryprint(id_ex->WB->get(),true);
	printf("id_ex->M: ");
	binaryprint(id_ex->M->get(),true);
	printf("id_ex->EX: ");
	binaryprint(id_ex->EX->get(),true);
	printf("PC: ");
	binaryprint(pc->get_value(),true);
	printf("instruction: ");
	printf("%s\n",inst->get_instruction().c_str());
	printf("instruction (opcode): ");
	binaryprint(inst->get_opcode()->instruction(),true);
	printf("if_id->PCpiu4: ");
	binaryprint(if_id->PCpiu4->get(),true);
	printf("id_ex->imm: ");
	binaryprint(id_ex->imm->get(),true);
	printf("id_ex->Data1: ");
	binaryprint(id_ex->Data1->get(),true);
	printf("id_ex->Data2: ");
	binaryprint(id_ex->Data2->get(),true);
	printf("ex_mem->WB: ");
	binaryprint(ex_mem->WB->get(),true);
	printf("ex_mem->M: ");
	binaryprint(ex_mem->M->get(),true);
	printf("ex_mem->DataW: ");
	binaryprint(ex_mem->DataW->get(),true);
	printf("ex_mem->RIS: ");
	binaryprint(ex_mem->RIS->get(),true);
	printf("ex_mem->RegW: ");
	binaryprint(ex_mem->RegW->get(),true);
	printf("mem_wb->WB: ");
	binaryprint(mem_wb->WB->get(),true);
	printf("mem_wb->Data: ");
	binaryprint(mem_wb->Data->get(),true);
	printf("mem_wb->DataR: ");
	binaryprint(mem_wb->DataR->get(),true);
	printf("mem_wb->RegW: ");
	binaryprint(mem_wb->RegW->get(),true);
}

void datapath::configure_muxes()
{
	EXmux3->set_signal1(false);
	EXmux3->set_signal2(false);
	if (ex_mem->RegW->get() == id_ex->RS->get() && ex_mem->WB->get() >> 31) {
		EXmux3->set_signal1(true);
		EXmux3->set_signal2(false);
	}
	if (mem_wb->RegW->get() == id_ex->RS->get() && mem_wb->WB->get() >> 31) {
		EXmux3->set_signal1(false);
		EXmux3->set_signal2(true);
	}
	EXmux4->set_signal1(false);
	EXmux4->set_signal2(false);
	if (ex_mem->RegW->get() == id_ex->RT->get() && ex_mem->WB->get() >> 31) {
		EXmux4->set_signal1(true);
		EXmux4->set_signal2(false);
	}
	if (mem_wb->RegW->get() == id_ex->RT->get() && mem_wb->WB->get() >> 31) {
		EXmux4->set_signal1(false);
		EXmux4->set_signal2(true);
	}
	EXmux5->set_signal(id_ex->EX->get()>>31);
}

void datapath::set_registers()
{
	id_ex->RS->set(RS(inst->get_opcode()->instruction()));
	id_ex->RT->set(RT(inst->get_opcode()->instruction()));
	id_ex->RD->set(RD(inst->get_opcode()->instruction()));
	id_ex->OP->set(OPCODE(inst->get_opcode()->instruction()));
	id_ex->WB->set(temp_ID_EX_WB);
	id_ex->M->set(temp_ID_EX_M);
	id_ex->EX->set(temp_ID_EX_EX);
	pc->set_value(temp_PC);
	inst = temp_instruction;
	if_id->PCpiu4->set(temp_IF_ID_PCpiu4);
	id_ex->imm->set(temp_ID_EX_imm);
	id_ex->Data1->set(temp_ID_EX_Data1);
	id_ex->Data2->set(temp_ID_EX_Data2);
	ex_mem->WB->set(temp_EX_MEM_WB);
	ex_mem->M->set(temp_EX_MEM_M);
	ex_mem->DataW->set(temp_EX_MEM_DataW);
	ex_mem->RIS->set(temp_EX_MEM_RIS);
	ex_mem->RegW->set(temp_EX_MEM_RegW);
	mem_wb->WB->set(temp_MEM_WB_WB);
	mem_wb->Data->set(temp_MEM_WB_Data);
	mem_wb->DataR->set(temp_MEM_WB_DataR);
	mem_wb->RegW->set(temp_MEM_WB_RegW);
}

bool datapath::disassemble(const unsigned int op)
{
	return true;
}
