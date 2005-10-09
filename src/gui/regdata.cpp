/*
 *  regdata.cpp
 *  Register data list class implementation
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
#include "regdata.h"
#include "../mvm.h"
#include "../basic/convenience.h"
#include "../parser/ophandlers.h"

static inline void wbinaryprint(WINDOW *win,const int y, const int x, const unsigned int val, const bool zero)
{
	int ny = y;
	int nx = x;
	unsigned int mask = 0x80000000;
	for (int i = 0; i < 32; i++) {
		mvwprintw(win,ny,nx,"%d",(val&mask?1:0));
		mask >>= 1;
		nx++;
	}
}

mvm::gui::regdata::regdata(const int sy, const int sx, const int my, const int mx)
{
	y0 = sy;
	x0 = sx;
	y1 = my;
	x1 = mx;
	regwin = newwin(sy,sx,my,mx);
	//box(regwin,0,0);
	wrefresh(regwin);
	init_pair(4,COLOR_BLACK,COLOR_BLACK);
}

mvm::gui::regdata::~regdata()
{
	delwin(regwin);
}

#define MARGIN 16
void mvm::gui::regdata::reprint()
{
	wclear(regwin);
	attron(COLOR_PAIR(4));
	for (int i = x1; i < x0; i++)
		for (int j = y1; j <= y0; j++)
			mvwaddch(regwin,j,i,' ');
	attroff(COLOR_PAIR(4));
	attron(COLOR_PAIR(1));
	mvwprintw(regwin,y1+1,x1+1,"id_ex->RS:");
	wbinaryprint(regwin,y1+1,x1+MARGIN,VM->dp->id_ex->RS->get(),true);
	mvwprintw(regwin,y1+2,x1+1,"id_ex->RT:");
	wbinaryprint(regwin,y1+2,x1+MARGIN,VM->dp->id_ex->RT->get(),true);
	mvwprintw(regwin,y1+3,x1+1,"id_ex->RD:");
	wbinaryprint(regwin,y1+3,x1+MARGIN,VM->dp->id_ex->RD->get(),true);
	mvwprintw(regwin,y1+4,x1+1,"id_ex->OP:");
	wbinaryprint(regwin,y1+4,x1+MARGIN,VM->dp->id_ex->OP->get(),true);
	mvwprintw(regwin,y1+5,x1+1,"id_ex->WB:");
	mvwprintw(regwin,y1+5,x1+MARGIN,"RegWrite:%d, WBData:%d\n",(VM->dp->id_ex->WB.RegWrite?1:0),(VM->dp->id_ex->WB.WBData?1:0));
	mvwprintw(regwin,y1+6,x1+1,"id_ex->M:");
	mvwprintw(regwin,y1+6,x1+MARGIN,"MemRead:%d, MemWrite:%d, Word:%d\n",(VM->dp->id_ex->M.MemRead?1:0),(VM->dp->id_ex->M.MemWrite?1:0),(VM->dp->id_ex->M.Word?1:0));
	mvwprintw(regwin,y1+7,x1+1,"id_ex->EX:");
	mvwprintw(regwin,y1+7,x1+MARGIN,"RegDest:%d, AluOP:%d%d, AluSrc:%d\n",(VM->dp->id_ex->EX.RegDest?1:0),(VM->dp->id_ex->EX.AluOP1?1:0),(VM->dp->id_ex->EX.AluOP2?1:0),(VM->dp->id_ex->EX.AluSrc?1:0));
	if (VM->dp->inst) {
		mvwprintw(regwin,y1+8,x1+1,"Instruction:");
		std::string tmp = VM->dp->inst->get_instruction();
		mvm::basic::strip_leading_whitespace(tmp);
		mvwprintw(regwin,y1+8,x1+MARGIN,"%s",tmp.c_str());
		mvwprintw(regwin,y1+9,x1+1,"Opcode:");
		wbinaryprint(regwin,y1+9,x1+MARGIN,VM->dp->inst->get_opcode()->instruction(),true);
	}
	mvwprintw(regwin,y1+10,x1+1,"if_id->PCpiu4:");
	wbinaryprint(regwin,y1+10,x1+MARGIN,VM->dp->if_id->PCpiu4->get(),true);
	mvwprintw(regwin,y1+11,x1+1,"id_ex->imm:");
	wbinaryprint(regwin,y1+11,x1+MARGIN,VM->dp->id_ex->imm->get(),true);
	mvwprintw(regwin,y1+12,x1+1,"id_ex->Data1:");
	wbinaryprint(regwin,y1+12,x1+MARGIN,VM->dp->id_ex->Data1->get(),true);
	mvwprintw(regwin,y1+13,x1+1,"id_ex->Data2:");
	wbinaryprint(regwin,y1+13,x1+MARGIN,VM->dp->id_ex->Data2->get(),true);
	mvwprintw(regwin,y1+14,x1+1,"ex_mem->WB:");
	mvwprintw(regwin,y1+14,x1+MARGIN,"RegWrite:%d, WBData:%d\n",(VM->dp->ex_mem->WB.RegWrite?1:0),(VM->dp->ex_mem->WB.WBData?1:0));
	mvwprintw(regwin,y1+15,x1+1,"ex_mem->M:");
	mvwprintw(regwin,y1+15,x1+MARGIN,"MemRead:%d, MemWrite:%d, Word:%d\n",(VM->dp->ex_mem->M.MemRead?1:0),(VM->dp->ex_mem->M.MemWrite?1:0),(VM->dp->ex_mem->M.Word?1:0));
	mvwprintw(regwin,y1+16,x1+1,"ex_mem->DataW:");
	wbinaryprint(regwin,y1+16,x1+MARGIN,VM->dp->ex_mem->DataW->get(),true);
	mvwprintw(regwin,y1+17,x1+1,"ex_mem->RIS:");
	wbinaryprint(regwin,y1+17,x1+MARGIN,VM->dp->ex_mem->RIS->get(),true);
	mvwprintw(regwin,y1+18,x1+1,"ex_mem->RegW:");
	wbinaryprint(regwin,y1+18,x1+MARGIN,VM->dp->ex_mem->RegW->get(),true);
	mvwprintw(regwin,y1+19,x1+1,"mem_wb->WB:");
	mvwprintw(regwin,y1+19,x1+MARGIN,"RegWrite:%d, WBData:%d\n",(VM->dp->mem_wb->WB.RegWrite?1:0),(VM->dp->mem_wb->WB.WBData?1:0));
	mvwprintw(regwin,y1+20,x1+1,"mem_wb->Data:");
	wbinaryprint(regwin,y1+20,x1+MARGIN,VM->dp->mem_wb->Data->get(),true);
	mvwprintw(regwin,y1+21,x1+1,"mem_wb->DataR:");
	wbinaryprint(regwin,y1+21,x1+MARGIN,VM->dp->mem_wb->DataR->get(),true);
	mvwprintw(regwin,y1+22,x1+1,"mem_wb->RegW:");
	wbinaryprint(regwin,y1+22,x1+MARGIN,VM->dp->mem_wb->RegW->get(),true);
	for (int i = 0; i < 32; i++) {
		mvwprintw(regwin,y1+24+i,x1+1,"$%d",i);
		mvwprintw(regwin,y1+24+i,x1+5,"($%s)",mvm::parser::readable_register(i).c_str());
		wbinaryprint(regwin,y1+24+i,x1+MARGIN,VM->dp->rf->get_register(i),true);
	}
	attroff(COLOR_PAIR(1));
}

void mvm::gui::regdata::refresh()
{
	wrefresh(regwin);
}
