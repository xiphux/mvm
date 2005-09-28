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
}

void datapath::init()
{
	operation *o = new rtype(0);
	inst = new instruction("nop",o);
}

void datapath::advance_instructions()
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

bool datapath::detect_completion()
{
	return false;
	unsigned int a = (stage1->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int b = (stage2->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int c = (stage3->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int d = (stage4->get_instruction()==0x9 /* 1001 */ ?1:0);
	unsigned int e = (stage5->get_instruction()==0x9 /* 1001 */ ?1:0);
	return ((a && b && c && d && e) && (clock > 2));
}

int datapath::execute_alu(const unsigned int wbdata)
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

void datapath::tick()
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
	if (mem_wb->WB->get()&0x8fffffff)
		mem_wb->RegW->set(WBdata);

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
	if (ctrl_EX && (isBne == 0x4 || isBne == 0x5)) {
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
		temp_instruction = im->fetch_instruction(pc->get_address());
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
	if (IsJump == 0x2 || IsJump == 0x3)
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
	temp_ID_EX_Data1 = RL1;

	/*
	 * Read data 2 corresponds to the value of RT
	 */
	temp_ID_EX_Data2 = RL2;

	/*
	 * Given references to the memory
	 */
	//    Load
	//
	/*
	 * Save to memory (MemWrite = 1)
	 */
	if (ex_mem->M->get()&0x40000000) {
		if (ex_mem->M->get()&0x1) {
			if (ex_mem->RIS->get()%4) {
				printf("Memory access error");
			}
			/*
		byte1 = mid(insieme,1,8)
		byte2 = mid(insieme,9,8)
		byte3 = mid(insieme,17,8)
		byte4 = mid(insieme,25,8)
		prova = EX_MEM_RIS mod 4
		if prova <> 0 then
			response.Write "<div align=center><font color=red size=3><b>ERRORE: INDIRIZZO DI MEMORIA ERRATO!</b></font></div>"
			response.End
		end if
		EX_MEM_RIS = cint(EX_MEM_RIS)
		if EX_MEM_RIS =< 4996 then 
			MemDati(EX_MEM_RIS) = byte1
			MemDati(EX_MEM_RIS + 1) = byte2
			MemDati(EX_MEM_RIS + 2) = byte3
			MemDati(EX_MEM_RIS + 3) = byte4
		end if
			 */
		} else {
			/*
			 * Save byte
			 */
			/*
		dato = IntToBin(EX_MEM_DataW,8,0)	'Save Byte
		lungh = len(dato)
		if lungh > 8 then
			dato = right(dato,8)
		end if
		MemDati(EX_MEM_RIS) = dato
		*/
		}
	}

	/*
	 * Load word (MemRead = 1)
	 */
	/*
if left(EX_MEM_M,1) = "1" then				'Caso di una Load (MemRead = 1)
	
		if right(EX_MEM_M,1) = "1" then			'Load Word
		prova = EX_MEM_RIS mod 4
		if prova <> 0 then
			response.Write "<div align=center><font color=red size=3><b>ERRORE: INDIRIZZO DI MEMORIA ERRATO!</b></font></div>"
			response.End
		end if
		if EX_MEM_RIS =< 4996 then 
			byte1 = MemDati(EX_MEM_RIS)
			byte2 = MemDati(EX_MEM_RIS + 1)
			byte3 = MemDati(EX_MEM_RIS + 2)
			byte4 = MemDati(EX_MEM_RIS + 3)
			temp_MEM_WB_DataR = byte1 & byte2 & byte3 & byte4
			temp_MEM_WB_DataR = bintoInt(temp_MEM_WB_DataR,0)
		else
			temp_MEM_WB_DataR = 1
		end if
		
	else
		temp_MEM_WB_DataR = MemDati(EX_MEM_RIS)		'Load Byte
		temp_MEM_WB_DataR = BinToInt(temp_MEM_WB_DataR,0)
	end if
end if
	 */

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
		if (isBne == 5)
			ctrl1 = 0;
		else
			ctrl1 = 1;
	} else {
		if (isBne == 5)
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
	if (isBne == 2 || isBne == 3) {
		ctrl1 = 1;
		if (isBne == 3)
			rf->set_register(31,pc->get_value());
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
		temp_PC = IDmux->mux(NewPC1,NewPC2);
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
