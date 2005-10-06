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
#include "../basic/convenience.h"
#include "../parser/rtype.h"

mvm::core::datapath::datapath(): complete(false), debug(false), align(4), clock(0)
{
	ctrl = new control();
	as = new address_space();
	pc = new PC();
	IDmux = new idmux();
	EXmux3 = new exmux3();
	EXmux4 = new exmux3();
	EXmux5 = new exmux2();
	alu = new ALU();
	acu = new alu_control_unit();
	rf = new register_file();
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

mvm::core::datapath::~datapath()
{
	delete ctrl;
	delete as;
	delete pc;
	delete IDmux;
	delete EXmux3;
	delete EXmux4;
	delete EXmux5;
	delete acu;
	delete alu;
	delete rf;
	delete stage1;
	delete stage2;
	delete stage3;
	delete stage4;
	delete stage5;
	delete if_id;
	delete id_ex;
	delete ex_mem;
	delete mem_wb;
	delete nop;
	labels.clear();
}

void mvm::core::datapath::init()
{
	mvm::parser::operation *o = new mvm::parser::rtype(0);
	nop = new instruction("nop",o);
	inst = nop;
}

void mvm::core::datapath::advance_instructions()
{
	/*
	 * Increment the PC of the running instruction
	 */
	temp_IF_ID_PCpiu4 = pc->get_value()+1;
	unsigned int a = stage1->get_instruction();
	unsigned int b = stage2->get_instruction();
	unsigned int c = stage3->get_instruction();
	unsigned int d = stage4->get_instruction();
	if (!stall) {
		if (pc->get_value() > MemIstrDim)
			stage1->set_instruction(0x9);
		else
			/*
			 * Instruction found in state IF
			 */
			stage1->set_instruction(pc->get_value());
		stage2->set_instruction(a);
	} else
		/*
		 * Stall
		 */
		stage2->set_instruction(0x9);
	/*
	 * Instruction found in state EX
	 */
	stage3->set_instruction(b);
	/*
	 * Instruction found in state MEM
	 */
	stage4->set_instruction(c);
	/*
	 * Instruction found in state WB
	 */
	stage5->set_instruction(d);
}

bool mvm::core::datapath::detect_completion()
{
	return false;
	unsigned int a = (stage1->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int b = (stage2->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int c = (stage3->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int d = (stage4->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int e = (stage5->get_instruction()==0x9 /* 1001 */ ?1:0);
	return ((a && b && c && d && e) && (clock > 2));
}

int mvm::core::datapath::execute_alu(const unsigned int wbdata)
{
	/*
	 * Choose one of the three possibilities to be ALU operand 1
	 */
	int ALUdata1 = EXmux3->mux(id_ex->Data1->get(),wbdata,ex_mem->RIS->get());
	/*
	 * Choose one of the three possibilities to be ALU operand 2
	 */
	int temp_EX_MEM_DataW = EXmux4->mux(id_ex->Data2->get(),wbdata,ex_mem->RIS->get());
	/*
	 * Choose between the two operators and the immediate field
	 */
	int ALUdata2 = EXmux5->mux(temp_EX_MEM_DataW,id_ex->imm->get());
	/*
	 * AluOP is the second and third bit of register ID/EX.M
	 */
	int AluOP = id_ex->EX->get()&0xcfffffff;
	/*
	 * Function field tells instruction
	 */
	/*
	 * Create ALU instruction
	 */
	int aluCtrl = acu->fire_signal(AluOP,id_ex->OP->get());
	/*
	 * ALU does its job
	 */
	return alu->execute(aluCtrl,ALUdata1,ALUdata2);
}

void mvm::core::datapath::tick()
{
	clock++;
	if (complete = detect_completion())
		return;

	/*
	 * Depending on the state of WB, save to the given register
	 */

	/*
	 * Choose value to save
	 */
	unsigned int WBdata;
	if (mem_wb->WB->get()&0x1)
		WBdata = mem_wb->DataR->get();
	else
		WBdata = mem_wb->Data->get();

	/*
	 * Save only if RegWrite = 1
	 */
	if (mem_wb->WB->get()&0x80000000)
		rf->set_register(mem_wb->RegW->get(),WBdata);

	/*
	 * Temporarily prevent segfaults
	 */
	if (!inst)
		inst = nop;
	
	/*
	 * Value of register RS
	 */
	unsigned char RL1 = RS(inst->get_opcode()->instruction());

	/*
	 * Value of register RT
	 */
	unsigned char RL2 = RT(inst->get_opcode()->instruction());

	/*
	 * MemRead means the next op is LW
	 */
	if (id_ex->M->get()>>31) {
		unsigned int rt = id_ex->RT->get();
		/*
		 * If the destination is one of the registers
		 * we have to wait one clock cycle
		 */
		if (rt == RL1 || rt == RL2)
			stall = true;
	} else
		/*
		 * Otherwise continue
		 */
		stall = false;

	/*
	 * Opcode field indicates if we have a BNE (op == 5)
	 */
	unsigned int isBne = OPCODE(inst->get_opcode()->instruction());

	/*
	 * Forwarding unit 2a present only if one of the
	 * two registers is a destination for a successive state,
	 * must make a stall cycle
	 */
	/*
	 * Regwrite of the former state
	 */
	unsigned int ctrl_EX = id_ex->WB->get()>>31;
	unsigned int exDest;
	if (ctrl_EX && (isBne == ITYPE_OP_BEQ || isBne == ITYPE_OP_BNE)) {
		if (!(id_ex->EX->get()>>31))
			exDest = id_ex->RT->get();
		else
			exDest = id_ex->RD->get();
		if (exDest == RL1 || exDest == RL1)
			stall = true;
	}

	/*
	 * If not stalling, advance instructions
	 */
	if (!stall)
		/*
		 * New instruction from instruction memory
		 */
		temp_instruction = as->im->fetch_instruction(pc->get_address());
	else
		temp_instruction = inst;

	advance_instructions();

	/*
	 * Immediate value
	 */
	temp_ID_EX_imm = inst->get_opcode()->instruction() & 0xffff;

	/*
	 * OP field controls the ALU
	 */
	temp_ID_EX_op = OPCODE(inst->get_opcode()->instruction());

	/*
	 * Forward PC
	 */
	id_ex->PCpiu4->set(if_id->PCpiu4->get());

	/*
	 * Control if the unit is type J
	 */
	unsigned int IsJump = OPCODE(inst->get_opcode()->instruction());
	unsigned int NewPC1, NewPC2;

	/*
	 * Possible new PC 1
	 */
	if (IsJump == JTYPE_OP_J || IsJump == JTYPE_OP_JAL)
		NewPC1 = ADDR(inst->get_opcode()->instruction());
	else
		NewPC1 = temp_ID_EX_imm;

	/*
	 * Possible new PC 2
	 */
	NewPC2 = temp_IF_ID_PCpiu4;

	/*
	 * Read data 1 corresponds to the value of RS
	 */
	temp_ID_EX_Data1 = rf->get_register(RL1);

	/*
	 * Read data 2 corresponds to the value of RT
	 */
	temp_ID_EX_Data2 = rf->get_register(RL2);

	/*
	 * Given references to the memory
	 */
	/*
	 * Save to memory (MemWrite = 1)
	 */
	if (ex_mem->M->get()&0x40000000) {
		if (ex_mem->M->get()&0x1) {
			unsigned int ris = ex_mem->RIS->get();
			if (ris%align) {
				printf("Memory access error\n");
			}
			unsigned char byte1 = (inst->get_opcode()->instruction()>>24)&0xff;
			unsigned char byte2 = (inst->get_opcode()->instruction()>>16)&0xff;
			unsigned char byte3 = (inst->get_opcode()->instruction()>>8)&0xff;
			unsigned char byte4 = inst->get_opcode()->instruction()&0xff;
			if (ris <= 4996) {
				as->dm->write_data(ris,byte1);
				as->dm->write_data(ris+(1<<2),byte2);
				as->dm->write_data(ris+(2<<2),byte3);
				as->dm->write_data(ris+(3<<2),byte4);
			}
		} else {
			/*
			 * Save byte
			 */
			unsigned char d = ex_mem->DataW->get()&0xff;
			as->dm->write_data(ex_mem->RIS->get(),d);
		}
	}

	/*
	 * Load word (MemRead = 1)
	 */
	if (ex_mem->M->get()&0x80000000) {
		if (ex_mem->M->get()&0x1) {
			unsigned int ris = ex_mem->RIS->get();
			if (ris%align) {
				printf("Memory access error\n");
			}
			if (ris <= 4996) {
				unsigned char byte1 = as->dm->read_data(ris);
				unsigned char byte2 = as->dm->read_data(ris+(1<<2));
				unsigned char byte3 = as->dm->read_data(ris+(2<<2));
				unsigned char byte4 = as->dm->read_data(ris+(3<<2));
				temp_MEM_WB_DataR = (((((byte1<<8)&byte2)<<8)&byte3)<<8)&byte4;
			} else {
				temp_MEM_WB_DataR = 1;
			}
		} else {
			/*
			 * Load byte
			 */
			temp_MEM_WB_DataR = as->dm->read_data(ex_mem->RIS->get());
		}
	}

	/*
	 * Forwarding unit 2b present only during branch
	 * if one of the two registers is the register destination
	 * of the state MEM, must forward the new value
	 */
	/*
	 * RegWrite in the state MEM
	 */
	unsigned int ctrl_MEM = ex_mem->WB->get()>>31;
	unsigned int bData1 = temp_ID_EX_Data1;
	unsigned int bData2 = temp_ID_EX_Data2;
	if (ctrl_MEM) {
		if (ex_mem->RegW->get() == RL1) {
			if (ex_mem->WB->get()&0x1)
				bData1 = temp_MEM_WB_DataR;
			else
				bData1 = ex_mem->RIS->get();
		}
		if (ex_mem->RegW->get() == RL2) {
			if (ex_mem->WB->get()&0x1)
				bData2 = temp_MEM_WB_DataR;
			else
				bData2 = ex_mem->RIS->get();
		}
	}

	/*
	 * If the two read data are equal
	 */
	if (bData1 == bData2) {
		if (isBne == ITYPE_OP_BNE)
			ctrl1 = 0;
		else
			ctrl1 = 1;
	} else {
		if (isBne == ITYPE_OP_BNE)
			/*
			 * BNE
			 */
			ctrl1 = 1;
		else
			ctrl1 = 0;
	}

	/*
	 * In the case of an unconditional jump, ctrl is always 1
	 */
	if (isBne == JTYPE_OP_J || isBne == JTYPE_OP_JAL) {
		ctrl1 = 1;
		if (isBne == JTYPE_OP_JAL)
			rf->set_register(31,pc->get_address());
	}

	unsigned int isjr = inst->get_opcode()->instruction()&0x3f;
	if (!isBne && isjr == 8) {
		NewPC1 = rf->get_register(31);
		ctrl1 = 1;
	}

	/*
	 * Jump case
	 */
	unsigned int jump = ctrl->read_instruction(inst->get_opcode()->instruction(), SIGNAL_JUMP);
	unsigned int temp_ctrl1 = ctrl1;
	/*
	 * Logical and
	 */
	ctrl1 &= jump;
	/*
	 * Second data controlled by the control unit
	 */
	unsigned int ctrl2 = ctrl->read_instruction(inst->get_opcode()->instruction(), SIGNAL_PCSRC);
	ctrl2 = 0;
	/*
	 * Stall controls whether PC forwards
	 */
	if (!stall) {
		/*
		 * They control whether the new instruction is NewPC1 or NewPC2
		 */
		IDmux->set_signal1(ctrl1);
		IDmux->set_signal2(ctrl2);
		temp_PC = IDmux->mux(NewPC1>>2,NewPC2);
	} else
		temp_PC = pc->get_value();
	unsigned int ID_discard = ctrl->read_instruction(inst->get_opcode()->instruction(),SIGNAL_DISCARD);

	/*
	 * Control signal generation
	 */
	/*
	 * Control MUX for control signals
	 */
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

	/*
	 * Forwarding
	 */

	temp_EX_MEM_RIS = execute_alu(WBdata);

	/*
	 * Signal RegDest
	 */
	if (!(id_ex->EX->get()&0x8fffffff))
		/*
		 * RT if the instruction is type I
		 */
		temp_EX_MEM_RegW = id_ex->RT->get();
	else
		/*
		 * RS if the instruction is type R
		 */
		temp_EX_MEM_RegW = id_ex->RD->get();
	/*
	 * Forward control signals
	 */
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

void mvm::core::datapath::print_debug()
{
	printf("id_ex->RS: ");
	mvm::basic::binaryprint(id_ex->RS->get(),true);
	printf("id_ex->RT: ");
	mvm::basic::binaryprint(id_ex->RT->get(),true);
	printf("id_ex->RD: ");
	mvm::basic::binaryprint(id_ex->RD->get(),true);
	printf("id_ex->OP: ");
	mvm::basic::binaryprint(id_ex->OP->get(),true);
	printf("id_ex->WB: ");
	mvm::basic::binaryprint(id_ex->WB->get(),true);
	printf("id_ex->M: ");
	mvm::basic::binaryprint(id_ex->M->get(),true);
	printf("id_ex->EX: ");
	mvm::basic::binaryprint(id_ex->EX->get(),true);
	printf("PC: ");
	mvm::basic::binaryprint(pc->get_value(),true);
	if (inst) {
		printf("instruction: ");
		printf("%s\n",inst->get_instruction().c_str());
		printf("instruction (opcode): ");
		mvm::basic::binaryprint(inst->get_opcode()->instruction(),true);
	}
	printf("if_id->PCpiu4: ");
	mvm::basic::binaryprint(if_id->PCpiu4->get(),true);
	printf("id_ex->imm: ");
	mvm::basic::binaryprint(id_ex->imm->get(),true);
	printf("id_ex->Data1: ");
	mvm::basic::binaryprint(id_ex->Data1->get(),true);
	printf("id_ex->Data2: ");
	mvm::basic::binaryprint(id_ex->Data2->get(),true);
	printf("ex_mem->WB: ");
	mvm::basic::binaryprint(ex_mem->WB->get(),true);
	printf("ex_mem->M: ");
	mvm::basic::binaryprint(ex_mem->M->get(),true);
	printf("ex_mem->DataW: ");
	mvm::basic::binaryprint(ex_mem->DataW->get(),true);
	printf("ex_mem->RIS: ");
	mvm::basic::binaryprint(ex_mem->RIS->get(),true);
	printf("ex_mem->RegW: ");
	mvm::basic::binaryprint(ex_mem->RegW->get(),true);
	printf("mem_wb->WB: ");
	mvm::basic::binaryprint(mem_wb->WB->get(),true);
	printf("mem_wb->Data: ");
	mvm::basic::binaryprint(mem_wb->Data->get(),true);
	printf("mem_wb->DataR: ");
	mvm::basic::binaryprint(mem_wb->DataR->get(),true);
	printf("mem_wb->RegW: ");
	mvm::basic::binaryprint(mem_wb->RegW->get(),true);
}

void mvm::core::datapath::configure_muxes()
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

void mvm::core::datapath::set_registers()
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

bool mvm::core::datapath::disassemble(const unsigned int op)
{
	return true;
}
