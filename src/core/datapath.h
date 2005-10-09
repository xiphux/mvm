/*
 *  datapath.h
 *  Datapath class definition
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
#ifndef _MVM_DATAPATH_H
#define _MVM_DATAPATH_H

#include <map>
#include "../basic/opcode.h"
#include "address_space.h"
#include "alu.h"
#include "alu_control_unit.h"
#include "control.h"
#include "exmux2.h"
#include "exmux3.h"
#include "idmux.h"
#include "pc.h"
#include "latch_if_id.h"
#include "latch_id_ex.h"
#include "latch_ex_mem.h"
#include "latch_mem_wb.h"
#include "register_file.h"
#include "stage1_if.h"
#include "stage2_id.h"
#include "stage3_ex.h"
#include "stage4_mem.h"
#include "stage5_wb.h"

namespace mvm
{
	namespace core
	{

		class datapath
		{
		public:
			datapath();
			~datapath();
			void init();
			void tick();
			void advance_instructions();
			void set_registers();
			void configure_muxes();
			bool detect_completion();
			int execute_alu(const unsigned int wbdata);
			bool disassemble(const unsigned int op);
			void print_debug();

			bool complete;
			bool debug;
			address_space *as;
			PC *pc;
			register_file *rf;
			exmux3 *EXmux3;
			exmux3 *EXmux4;
			exmux2 *EXmux5;
			latch_ex_mem *ex_mem;
			latch_mem_wb *mem_wb;
			latch_if_id *if_id;
			latch_id_ex *id_ex;
			instruction *inst;

			std::map<std::string,unsigned int> labels;
			unsigned int align;
			unsigned int ID_MuxCtrl;
			unsigned int ctrl_MEM;
			unsigned int jump;
			unsigned int temp_ctrl1;
			unsigned int ID_discard;
			bool collision;
			idmux *IDmux;
			bool stall;
		private:
			unsigned int clock;

			control *ctrl;
			ALU *alu;
			alu_control_unit *acu;

			stage1_if *stage1;
			stage2_id *stage2;
			stage3_ex *stage3;
			stage4_mem *stage4;
			stage5_wb *stage5;

			unsigned int temp_IF_ID_PCpiu4;
			unsigned int temp_IF_ID_IFdiscard;
			struct latch_wb temp_ID_EX_WB;
			struct latch_m temp_ID_EX_M;
			struct latch_ex temp_ID_EX_EX;
			unsigned int temp_PC;
			instruction *temp_instruction;
			unsigned int temp_ID_EX_imm;
			unsigned int temp_ID_EX_Data1;
			unsigned int temp_ID_EX_Data2;
			unsigned int temp_ID_EX_op;
			struct latch_wb temp_EX_MEM_WB;
			struct latch_m temp_EX_MEM_M;
			unsigned int temp_EX_MEM_DataW;
			unsigned int temp_EX_MEM_RIS;
			unsigned int temp_EX_MEM_RegW;
			struct latch_wb temp_MEM_WB_WB;
			unsigned int temp_MEM_WB_Data;
			unsigned int temp_MEM_WB_DataR;
			unsigned int temp_MEM_WB_RegW;
			unsigned int MemIstrDim;
			unsigned int ctrl1;
			instruction *nop;
		};

	}
}

#endif /* _MVM_DATAPATH_H */
