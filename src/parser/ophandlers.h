/*
 *  ophandlers.h
 *  Opcode handler function prototypes
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
#ifndef _MVM_OPHANDLERS_H
#define _MVM_OPHANDLERS_H

#include <string>
#include <vector>
#include "basic/convenience.h"
#include "basic/opcode.h"
#include "operation.h"
#include "rtype.h"
#include "itype.h"
#include "jtype.h"
#include "ctype.h"
#include "mvm.h"


namespace mvm
{
	namespace parser
	{
		
		static std::string lastlabel;
		static unsigned int opcode_type(const unsigned char opcode)
		{
			if (RTYPE(opcode))
				return TYPE_R;
			else if (JTYPE(opcode))
				return TYPE_J;
			else if (CTYPE(opcode))
				return TYPE_COPROC;
			else if (ITYPE(opcode))
				return TYPE_I;
			else
				return TYPE_NULL;
		}

		static unsigned int instruction_type(std::string ins)
		{
			transform(ins.begin(), ins.end(), ins.begin(), (int(*)(int))tolower);
			if (ins == "add" ||
			    ins == "addu" ||
			    ins == "and" ||
			    ins == "break" ||
			    ins == "div" ||
			    ins == "divu" ||
			    ins == "jalr" ||
			    ins == "jr" ||
			    ins == "mfhi" ||
			    ins == "mflo" ||
			    ins == "mthi" ||
			    ins == "mtlo" ||
			    ins == "mult" ||
			    ins == "multu" ||
			    ins == "nor" ||
			    ins == "or" ||
			    ins == "sll" ||
			    ins == "sllv" ||
			    ins == "slt" ||
			    ins == "sltu" ||
			    ins == "sra" ||
			    ins == "srav" ||
			    ins == "srl" ||
			    ins == "srlv" ||
			    ins == "sub" ||
			    ins == "subu" ||
			    ins == "syscall" ||
			    ins == "xor")
					return TYPE_R;
			else if (ins == "addi" ||
			    ins == "addiu" ||
			    ins == "andi" ||
			    ins == "lui" ||
			    ins == "ori" ||
			    ins == "slti" ||
			    ins == "sltiu" ||
			    ins == "xori" ||
			    ins == "beq" ||
			    ins == "bgez" ||
			    ins == "bgtz" ||
			    ins == "blez" ||
			    ins == "bltz" ||
			    ins == "bne")
					return TYPE_I;
			else if (ins == "lb" ||
			    ins == "lbu" ||
			    ins == "lh" ||
			    ins == "lhu" ||
			    ins == "lw" ||
			    ins == "lwc1" ||
			    ins == "sb" ||
			    ins == "sh" ||
			    ins == "sw" ||
			    ins == "swc1")
					return TYPE_MEM;
			else if (ins == "j" ||
			    ins == "jal")
					return TYPE_J;
			else if (ins == "add.s" ||
			    ins == "cvt.s.w" ||
			    ins == "cvt.w.s" ||
			    ins == "div.s" ||
			    ins == "mfc1" ||
			    ins == "mov.s" ||
			    ins == "mtc1" ||
			    ins == "mul.s" ||
			    ins == "sub.s")
					return TYPE_COPROC;
			return TYPE_NULL;
		}

		static std::string extract_operation(std::string &str)
		{
			std::string op;
			if (str.size()<1)
				return op;
			char ch = str.at(0);
			while (ch != ' ' && ch != '\t') {
				op.push_back(ch);
				str.erase(0,1);
				if (str.size() < 1)
					break;
				ch = str.at(0);
			}
			return op;
		}

		static unsigned int dereference_register(std::string reg)
		{
			if (reg.size() <= 1)
				return 0;
			if (reg.at(0) != '$')
				return 0;
			reg.erase(0,1);
			bool num = true;
			for (unsigned int i = 0; i < reg.size(); i++) {
				if (!isdigit(reg.at(i)))
					num = false;
			}
			if (num)
				return atoi(reg.c_str());
			else if (reg == "zero")
				return 0;
			else if (reg == "at")
				return 1;
			else if (reg == "v0")
				return 2;
			else if (reg == "v1")
				return 3;
			else if (reg == "a0")
				return 4;
			else if (reg == "a1")
				return 5;
			else if (reg == "a2")
				return 6;
			else if (reg == "a3")
				return 7;
			else if (reg == "t0")
				return 8;
			else if (reg == "t1")
				return 9;
			else if (reg == "t2")
				return 10;
			else if (reg == "t3")
				return 11;
			else if (reg == "t4")
				return 12;
			else if (reg == "t5")
				return 13;
			else if (reg == "t6")
				return 14;
			else if (reg == "t7")
				return 15;
			else if (reg == "s0")
				return 16;
			else if (reg == "s1")
				return 17;
			else if (reg == "s2")
				return 18;
			else if (reg == "s3")
				return 19;
			else if (reg == "s4")
				return 20;
			else if (reg == "s5")
				return 21;
			else if (reg == "s6")
				return 22;
			else if (reg == "s7")
				return 23;
			else if (reg == "t8")
				return 24;
			else if (reg == "t9")
				return 25;
			else if (reg == "k0")
				return 26;
			else if (reg == "k1")
				return 27;
			else if (reg == "gp")
				return 28;
			else if (reg == "sp")
				return 29;
			else if (reg == "fp")
				return 30;
			else if (reg == "ra")
				return 31;
			else
				return 0;
		}

		static bool dereference_pointer(std::string pointer, std::string &imm, std::string &rs)
		{
			if (pointer.size() <= 3)
				return false;
			std::string::size_type idx = pointer.find_first_of('(');
			if (idx == std::string::npos)
				return false;
			std::string::size_type idx2 = pointer.find_first_of(')');
			if (idx2 == std::string::npos)
				return false;
			if (idx > idx2)
				return false;
			imm = pointer.substr(0,idx);
			rs = pointer.substr(idx+1,idx2-(idx+1));
			return true;
		}

		static unsigned int dereference_label(std::string label)
		{
			std::map<std::string,unsigned int>::iterator it = VM->dp->labels.find(label);
			if (it != VM->dp->labels.end()) {
				return it->second;
			}
			return 0;
		}

		static operation *assembly_to_op(std::string op)
		{
			operation *o = NULL;
			mvm::basic::strip_leading_whitespace(op);
			mvm::basic::strip_comments(op);
			mvm::basic::strip_trailing_whitespace(op);
			if (op.find_first_of(':')!=std::string::npos) {
				lastlabel = op.substr(0,op.find_first_of(':'));
				op = op.substr(op.find_first_of(':')+1);
				mvm::basic::strip_leading_whitespace(op);
			}
			if (op.empty())
				return NULL;
			std::string cmd = extract_operation(op);
			mvm::basic::strip_leading_whitespace(op);
			std::vector<std::string> params = mvm::basic::tokenize(op,',');
			unsigned int type = instruction_type(cmd);
			switch (type) {
				case TYPE_R:
					o = new rtype(cmd,params);
					break;
				case TYPE_I:
					o = new itype(cmd,params);
					break;
				case TYPE_J:
					o = new jtype(cmd,params);
					break;
				case TYPE_MEM:
					o = new itype(cmd,params);
					break;
				case TYPE_COPROC:
					o = new ctype(cmd,params);
					break;
			}
			if (o && !lastlabel.empty()) {
				VM->dp->labels[lastlabel] = VM->dp->im->instructions.size()<<2;
				lastlabel.clear();
			}
			return o;
		}

		static std::string opcode_to_assembly(const unsigned int opcode)
		{
			return "";
		}

	}
}


#endif /* _MVM_OPHANDLERS_H */
