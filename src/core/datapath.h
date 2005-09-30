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
#include "basic/opcode.h"
#include "core/instruction_memory.h"
#include "core/alu.h"
#include "core/alu_control_unit.h"
#include "core/control.h"
#include "core/exmux2.h"
#include "core/exmux3.h"
#include "core/idmux.h"
#include "core/pc.h"
#include "core/latch_if_id.h"
#include "core/latch_id_ex.h"
#include "core/latch_ex_mem.h"
#include "core/latch_mem_wb.h"
#include "core/register_file.h"
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
			instruction_memory *im;
			PC *pc;
			std::map<std::string,unsigned int> labels;
		private:
			bool stall;
			unsigned int clock;

			control *ctrl;
			idmux *IDmux;
			exmux3 *EXmux3;
			exmux3 *EXmux4;
			exmux2 *EXmux5;
			ALU *alu;
			alu_control_unit *acu;
			register_file *rf;

			stage1_if *stage1;
			stage2_id *stage2;
			stage3_ex *stage3;
			stage4_mem *stage4;
			stage5_wb *stage5;

			latch_if_id *if_id;
			latch_id_ex *id_ex;
			latch_ex_mem *ex_mem;
			latch_mem_wb *mem_wb;

			unsigned int temp_IF_ID_PCpiu4;
			unsigned int temp_IF_ID_IFdiscard;
			unsigned int temp_ID_EX_WB;
			unsigned int temp_ID_EX_M;
			unsigned int temp_ID_EX_EX;
			unsigned int temp_PC;
			instruction *temp_instruction;
			unsigned int temp_ID_EX_imm;
			unsigned int temp_ID_EX_Data1;
			unsigned int temp_ID_EX_Data2;
			unsigned int temp_ID_EX_op;
			unsigned int temp_EX_MEM_WB;
			unsigned int temp_EX_MEM_M;
			unsigned int temp_EX_MEM_DataW;
			unsigned int temp_EX_MEM_RIS;
			unsigned int temp_EX_MEM_RegW;
			unsigned int temp_MEM_WB_WB;
			unsigned int temp_MEM_WB_Data;
			unsigned int temp_MEM_WB_DataR;
			unsigned int temp_MEM_WB_RegW;
			unsigned int MemIstrDim;
			instruction *inst;
			unsigned int ctrl1;
		};

	}
}

#endif /* _MVM_DATAPATH_H */
