/*
 *  gui.cpp
 *  GUI class implementation
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
#include "gui.h"
#include "../mvm.h"

#define vmidpoint(b)	((b).starty+(b).height/2)
#define hmidpoint(b)	((b).startx+(b).width/2)

#define SCROLLAMT 5

#define XMAX (170)
#define YMAX (45)

mvm::gui::gui::gui(const int sy,const  int sx, const int my, const int mx): complete(false)
{
	x0 = sx;
	y0 = sy;
	x1 = mx;
	y1 = my;
	//dpwin = newwin(my,mx,sy,sx);
	//box(dpwin,0,0);
	init_pair(1,COLOR_GREEN,COLOR_BLACK);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	init_pair(3,COLOR_RED,COLOR_BLACK);
}

mvm::gui::gui::~gui()
{
//	wborder(dpwin, ' ', ' ', ' ',' ',' ',' ',' ',' ');
//	wrefresh(dpwin);
//	delwin(dpwin);
}

void mvm::gui::gui::refresh()
{
	wrefresh(stdscr);
}

void mvm::gui::gui::keypressed(int ch)
{
	switch (ch) {
		case 27:
			complete = true;
			break;
		case KEY_LEFT:
			if (x0<0){x0+=SCROLLAMT;}
			break;
		case KEY_RIGHT:
			if ((x0+XMAX)>=x1){x0-=SCROLLAMT;}
			break;
		case KEY_UP:
			if (y0<0){y0+=SCROLLAMT;}
			break;
		case KEY_DOWN:
			if ((y0+YMAX)>=y1){y0-=SCROLLAMT;}
			break;
		case KEY_F(5):
			if (VM->dp->as->im->instructions.size()>1){VM->tick();}
			break;
		case KEY_F(1):
			showregs = !showregs;
			break;
	}
}

void mvm::gui::gui::draw()
{
	wattron(stdscr,COLOR_PAIR(1));
	drawbackground();
	drawcomponents();
	wattroff(stdscr,COLOR_PAIR(1));
	wattron(stdscr,COLOR_PAIR(2));
	drawdatapaths();
	wattroff(stdscr,COLOR_PAIR(2));
	wattron(stdscr,COLOR_PAIR(3));
	drawcontrolpaths();
	wattroff(stdscr,COLOR_PAIR(3));

	touchwin(stdscr);
}

void mvm::gui::gui::drawbackground()
{
	bgbox.height = LINES;
	bgbox.width = COLS;
	bgbox.starty = 0;
	bgbox.startx = 0;
	bgbox.border.ls = ACS_VLINE;
	bgbox.border.rs = ACS_VLINE;
	bgbox.border.ts = ACS_HLINE;
	bgbox.border.bs = ACS_HLINE;
	bgbox.border.tl = ACS_ULCORNER;
	bgbox.border.tr = ACS_URCORNER;
	bgbox.border.bl = ACS_LLCORNER;
	bgbox.border.br = ACS_LRCORNER;
	drawprimitive(&bgbox,false);
	//drawprimitive(&bgbox);
}

void mvm::gui::gui::drawcomponents()
{
	/*
	 * PC
	 */
	pc.height = 2;
	pc.width = 3;
	pc.starty = y0+26;
	pc.startx = x0+4;
	pc.border.ls = ACS_VLINE;
	pc.border.rs = ACS_VLINE;
	pc.border.ts = ACS_HLINE;
	pc.border.bs = ACS_HLINE;
	pc.border.tl = ACS_ULCORNER;
	pc.border.tr = ACS_URCORNER;
	pc.border.bl = ACS_LLCORNER;
	pc.border.br = ACS_LRCORNER;
	drawprimitive(&pc);
	mvwprintw(stdscr,vmidpoint(pc),hmidpoint(pc),"PC");

	/*
	 * PC Incrementer
	 */
	pci.height = 4;
	pci.width = 6;
	pci.starty = y0+17;
	pci.startx = x0+13;
	pci.border.ls = ACS_VLINE;
	pci.border.rs = ACS_VLINE;
	pci.border.ts = ACS_HLINE;
	pci.border.bs = ACS_HLINE;
	pci.border.tl = ACS_ULCORNER;
	pci.border.tr = ACS_URCORNER;
	pci.border.bl = ACS_LLCORNER;
	pci.border.br = ACS_LRCORNER;
	drawprimitive(&pci);
	mvwprintw(stdscr,vmidpoint(pci),hmidpoint(pci),"+");

	/*
	 * IF MUX
	 */
	ifmux.height = 4;
	ifmux.width = 4;
	ifmux.starty = y0+11;
	ifmux.startx = x0+14;
	ifmux.border.ls = ACS_VLINE;
	ifmux.border.rs = ACS_VLINE;
	ifmux.border.ts = ACS_HLINE;
	ifmux.border.bs = ACS_HLINE;
	ifmux.border.tl = ACS_ULCORNER;
	ifmux.border.tr = ACS_URCORNER;
	ifmux.border.bl = ACS_LLCORNER;
	ifmux.border.br = ACS_LRCORNER;
	drawprimitive(&ifmux);
	mvwprintw(stdscr,y0+12,hmidpoint(ifmux),"M");
	mvwprintw(stdscr,y0+13,hmidpoint(ifmux),"U");
	mvwprintw(stdscr,y0+14,hmidpoint(ifmux),"X");

	/*
	 * IF AND
	 */
	ifand.height = 2;
	ifand.width = 4;
	ifand.starty = y0+4;
	ifand.startx = x0+14;
	ifand.border.ls = ACS_VLINE;
	ifand.border.rs = ACS_VLINE;
	ifand.border.ts = ACS_HLINE;
	ifand.border.bs = ACS_HLINE;
	ifand.border.tl = ACS_ULCORNER;
	ifand.border.tr = ACS_URCORNER;
	ifand.border.bl = ACS_LLCORNER;
	ifand.border.br = ACS_LRCORNER;
	drawprimitive(&ifand);
	mvwprintw(stdscr,y0+5,x0+15,"AND");

	/*
	 * Instruction Memory
	 */
	im.height = 7;
	im.width = 12;
	im.starty = y0+23;
	im.startx = x0+10;
	im.border.ls = ACS_VLINE;
	im.border.rs = ACS_VLINE;
	im.border.ts = ACS_HLINE;
	im.border.bs = ACS_HLINE;
	im.border.tl = ACS_ULCORNER;
	im.border.tr = ACS_URCORNER;
	im.border.bl = ACS_LLCORNER;
	im.border.br = ACS_LRCORNER;
	drawprimitive(&im);
	mvwprintw(stdscr,y0+24,x0+11,"Instruction");
	mvwprintw(stdscr,y0+25,x0+13,"Memory");
	mvwprintw(stdscr,y0+27,x0+11,"Address");
	mvwprintw(stdscr,y0+29,x0+12,"Data Value");

	/*
	 * IF/ID Latch
	 */
	ifidlatch.height = 20;
	ifidlatch.width = 6;
	ifidlatch.starty = y0+16;
	ifidlatch.startx = x0+25;
	ifidlatch.border.ls = ACS_VLINE;
	ifidlatch.border.rs = ACS_VLINE;
	ifidlatch.border.ts = ACS_HLINE;
	ifidlatch.border.bs = ACS_HLINE;
	ifidlatch.border.tl = ACS_ULCORNER;
	ifidlatch.border.tr = ACS_URCORNER;
	ifidlatch.border.bl = ACS_LLCORNER;
	ifidlatch.border.br = ACS_LRCORNER;
	drawprimitive(&ifidlatch);
	mvwprintw(stdscr,y0+35,x0+26,"IF/ID");

	/*
	 * Hazard Detection Unit
	 */
	hdu.height = 5;
	hdu.width = 10;
	hdu.starty = y0+3;
	hdu.startx = x0+40;
	hdu.border.ls = ACS_VLINE;
	hdu.border.rs = ACS_VLINE;
	hdu.border.ts = ACS_HLINE;
	hdu.border.bs = ACS_HLINE;
	hdu.border.tl = ACS_ULCORNER;
	hdu.border.tr = ACS_URCORNER;
	hdu.border.bl = ACS_LLCORNER;
	hdu.border.br = ACS_LRCORNER;
	drawprimitive(&hdu);
	mvwprintw(stdscr,y0+4,x0+42,"Hazard");
	mvwprintw(stdscr,y0+5,x0+41,"Detection");
	mvwprintw(stdscr,y0+6,x0+43,"Unit");

	/*
	 * Control unit
	 */
	cu.height = 7;
	cu.width = 8;
	cu.starty = y0+9;
	cu.startx = x0+39;
	cu.border.ls = ACS_VLINE;
	cu.border.rs = ACS_VLINE;
	cu.border.ts = ACS_HLINE;
	cu.border.bs = ACS_HLINE;
	cu.border.tl = ACS_ULCORNER;
	cu.border.tr = ACS_URCORNER;
	cu.border.bl = ACS_LLCORNER;
	cu.border.br = ACS_LRCORNER;
	drawprimitive(&cu);
	mvwprintw(stdscr,y0+12,x0+40,"Control");
	mvwprintw(stdscr,y0+13,x0+41,"Unit");

	/*
	 * Register Memory
	 */
	rm.height = 10;
	rm.width = 17;
	rm.starty = vmidpoint(pci)+1;
	rm.startx = x0+50;
	rm.border.ls = ACS_VLINE;
	rm.border.rs = ACS_VLINE;
	rm.border.ts = ACS_HLINE;
	rm.border.bs = ACS_HLINE;
	rm.border.tl = ACS_ULCORNER;
	rm.border.tr = ACS_URCORNER;
	rm.border.bl = ACS_LLCORNER;
	rm.border.br = ACS_LRCORNER;
	drawprimitive(&rm);
	mvwprintw(stdscr,vmidpoint(pci)+2,x0+56,"Read Data 1");
	mvwprintw(stdscr,vmidpoint(pci)+3,x0+51,"Read Register 1");
	mvwprintw(stdscr,vmidpoint(pci)+4,x0+51,"Read Register 2");
	mvwprintw(stdscr,vmidpoint(pci)+6,x0+54,"Registers");
	mvwprintw(stdscr,vmidpoint(pci)+8,x0+51,"Write Register");
	mvwprintw(stdscr,vmidpoint(pci)+9,x0+56,"Read Data 2");
	mvwprintw(stdscr,vmidpoint(pci)+10,x0+51,"Write Data");

	/*
	 * ID/EX Latch
	 */
	idexlatch.height = 30;
	idexlatch.width = 6;
	idexlatch.starty = y0+6;
	idexlatch.startx = x0+75;
	idexlatch.border.ls = ACS_VLINE;
	idexlatch.border.rs = ACS_VLINE;
	idexlatch.border.ts = ACS_HLINE;
	idexlatch.border.bs = ACS_HLINE;
	idexlatch.border.tl = ACS_ULCORNER;
	idexlatch.border.tr = ACS_URCORNER;
	idexlatch.border.bl = ACS_LLCORNER;
	idexlatch.border.br = ACS_LRCORNER;
	drawprimitive(&idexlatch);
	mvwprintw(stdscr,y0+35,x0+76,"ID/EX");

	/*
	 * ID Equals
	 */
	ideq.height = 4;
	ideq.width = 3;
	ideq.starty = vmidpoint(pci)+4;
	ideq.startx = x0+69;
	ideq.border.ls = ACS_VLINE;
	ideq.border.rs = ACS_VLINE;
	ideq.border.ts = ACS_HLINE;
	ideq.border.bs = ACS_HLINE;
	ideq.border.tl = ACS_ULCORNER;
	ideq.border.tr = ACS_URCORNER;
	ideq.border.bl = ACS_LLCORNER;
	ideq.border.br = ACS_LRCORNER;
	drawprimitive(&ideq);
	mvwprintw(stdscr,vmidpoint(pci)+6,x0+70,"=");

	/*
	 * ID MUX
	 */
	idmux.height = 4;
	idmux.width = 3;
	idmux.starty = y0+10;
	idmux.startx = x0+67;
	idmux.border.ls = ACS_VLINE;
	idmux.border.rs = ACS_VLINE;
	idmux.border.ts = ACS_HLINE;
	idmux.border.bs = ACS_HLINE;
	idmux.border.tl = ACS_ULCORNER;
	idmux.border.tr = ACS_URCORNER;
	idmux.border.bl = ACS_LLCORNER;
	idmux.border.br = ACS_LRCORNER;
	drawprimitive(&idmux);
	mvwprintw(stdscr,y0+11,x0+68,"M");
	mvwprintw(stdscr,y0+12,x0+68,"U");
	mvwprintw(stdscr,y0+13,x0+68,"X");

	/*
	 * ID OR
	 */
	idor.height = 2;
	idor.width = 3;
	idor.starty = y0+5;
	idor.startx = x0+66;
	idor.border.ls = ACS_VLINE;
	idor.border.rs = ACS_VLINE;
	idor.border.ts = ACS_HLINE;
	idor.border.bs = ACS_HLINE;
	idor.border.tl = ACS_ULCORNER;
	idor.border.tr = ACS_URCORNER;
	idor.border.bl = ACS_LLCORNER;
	idor.border.br = ACS_LRCORNER;
	drawprimitive(&idor);
	mvwprintw(stdscr,vmidpoint(idor),hmidpoint(idor),"OR");

	/*
	 * Sign Extension
	 */
	se.height = 3;
	se.width = 7;
	se.starty = y0+28;
	se.startx = x0+38;
	se.border.ls = ACS_VLINE;
	se.border.rs = ACS_VLINE;
	se.border.ts = ACS_HLINE;
	se.border.bs = ACS_HLINE;
	se.border.tl = ACS_ULCORNER;
	se.border.tr = ACS_URCORNER;
	se.border.bl = ACS_LLCORNER;
	se.border.br = ACS_LRCORNER;
	drawprimitive(&se);
	mvwprintw(stdscr,y0+29,x0+39,"Sign");
	mvwprintw(stdscr,y0+30,x0+39,"Extend");

	/*
	 * ID/EX.WB
	 */
	mvwaddch(stdscr,y0+10,x0+75,ACS_LTEE);
	for (int i = 76; i <= 80; i++)
		mvwaddch(stdscr,y0+10,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+10,x0+81,ACS_RTEE);
	mvwprintw(stdscr,y0+8,x0+77,"WB");

	/*
	 * ID/EX.M
	 */
	mvwaddch(stdscr,y0+14,x0+75,ACS_LTEE);
	for (int i = 76; i <= 80; i++)
		mvwaddch(stdscr,y0+14,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+14,x0+81,ACS_RTEE);
	mvwprintw(stdscr,y0+12,x0+77,"M");

	/*
	 * ID/EX.EX
	 */
	mvwaddch(stdscr,y0+18,x0+75,ACS_LTEE);
	for (int i = 76; i <= 80; i++)
		mvwaddch(stdscr,y0+18,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+18,x0+81,ACS_RTEE);
	mvwprintw(stdscr,y0+16,x0+77,"EX");

	/*
	 * EX MUX 4
	 */
	exmux4.height = 4;
	exmux4.width = 3;
	exmux4.starty = y0+32;
	exmux4.startx = x0+88;
	exmux4.border.ls = ACS_VLINE;
	exmux4.border.rs = ACS_VLINE;
	exmux4.border.ts = ACS_HLINE;
	exmux4.border.bs = ACS_HLINE;
	exmux4.border.tl = ACS_ULCORNER;
	exmux4.border.tr = ACS_URCORNER;
	exmux4.border.bl = ACS_LLCORNER;
	exmux4.border.br = ACS_LRCORNER;
	drawprimitive(&exmux4);
	mvwprintw(stdscr,y0+33,x0+89,"M");
	mvwprintw(stdscr,y0+34,x0+89,"U");
	mvwprintw(stdscr,y0+35,x0+89,"X");

	/*
	 * EX MUX 2
	 */
	exmux2.height = 4;
	exmux2.width = 3;
	exmux2.starty = y0+23;
	exmux2.startx = x0+88;
	exmux2.border.ls = ACS_VLINE;
	exmux2.border.rs = ACS_VLINE;
	exmux2.border.ts = ACS_HLINE;
	exmux2.border.bs = ACS_HLINE;
	exmux2.border.tl = ACS_ULCORNER;
	exmux2.border.tr = ACS_URCORNER;
	exmux2.border.bl = ACS_LLCORNER;
	exmux2.border.br = ACS_LRCORNER;
	drawprimitive(&exmux2);
	mvwprintw(stdscr,y0+24,x0+89,"M");
	mvwprintw(stdscr,y0+25,x0+89,"U");
	mvwprintw(stdscr,y0+26,x0+89,"X");

	/*
	 * EX MUX 3
	 */
	exmux3.height = 4;
	exmux3.width = 3;
	exmux3.starty = y0+23;
	exmux3.startx = x0+94;
	exmux3.border.ls = ACS_VLINE;
	exmux3.border.rs = ACS_VLINE;
	exmux3.border.ts = ACS_HLINE;
	exmux3.border.bs = ACS_HLINE;
	exmux3.border.tl = ACS_ULCORNER;
	exmux3.border.tr = ACS_URCORNER;
	exmux3.border.bl = ACS_LLCORNER;
	exmux3.border.br = ACS_LRCORNER;
	drawprimitive(&exmux3);
	mvwprintw(stdscr,y0+24,x0+95,"M");
	mvwprintw(stdscr,y0+25,x0+95,"U");
	mvwprintw(stdscr,y0+26,x0+95,"X");

	/*
	 * EX MUX 1
	 */
	exmux1.height = 4;
	exmux1.width = 3;
	exmux1.starty = y0+17;
	exmux1.startx = x0+88;
	exmux1.border.ls = ACS_VLINE;
	exmux1.border.rs = ACS_VLINE;
	exmux1.border.ts = ACS_HLINE;
	exmux1.border.bs = ACS_HLINE;
	exmux1.border.tl = ACS_ULCORNER;
	exmux1.border.tr = ACS_URCORNER;
	exmux1.border.bl = ACS_LLCORNER;
	exmux1.border.br = ACS_LRCORNER;
	drawprimitive(&exmux1);
	mvwprintw(stdscr,y0+18,x0+89,"M");
	mvwprintw(stdscr,y0+19,x0+89,"U");
	mvwprintw(stdscr,y0+20,x0+89,"X");

	/*
	 * EX MUX 5
	 */
	exmux5.height = 4;
	exmux5.width = 3;
	exmux5.starty = y0+11;
	exmux5.startx = x0+107;
	exmux5.border.ls = ACS_VLINE;
	exmux5.border.rs = ACS_VLINE;
	exmux5.border.ts = ACS_HLINE;
	exmux5.border.bs = ACS_HLINE;
	exmux5.border.tl = ACS_ULCORNER;
	exmux5.border.tr = ACS_URCORNER;
	exmux5.border.bl = ACS_LLCORNER;
	exmux5.border.br = ACS_LRCORNER;
	drawprimitive(&exmux5);
	mvwprintw(stdscr,y0+12,x0+108,"M");
	mvwprintw(stdscr,y0+13,x0+108,"U");
	mvwprintw(stdscr,y0+14,x0+108,"X");

	/*
	 * EX MUX 6
	 */
	exmux6.height = 4;
	exmux6.width = 3;
	exmux6.starty = y0+7;
	exmux6.startx = x0+102;
	exmux6.border.ls = ACS_VLINE;
	exmux6.border.rs = ACS_VLINE;
	exmux6.border.ts = ACS_HLINE;
	exmux6.border.bs = ACS_HLINE;
	exmux6.border.tl = ACS_ULCORNER;
	exmux6.border.tr = ACS_URCORNER;
	exmux6.border.bl = ACS_LLCORNER;
	exmux6.border.br = ACS_LRCORNER;
	drawprimitive(&exmux6);
	mvwprintw(stdscr,y0+8,x0+103,"M");
	mvwprintw(stdscr,y0+9,x0+103,"U");
	mvwprintw(stdscr,y0+10,x0+103,"X");

	/*
	 * ALU Control Unit
	 */
	acu.height = 5;
	acu.width = 10;
	acu.starty = y0+26;
	acu.startx = x0+101;
	acu.border.ls = ACS_VLINE;
	acu.border.rs = ACS_VLINE;
	acu.border.ts = ACS_HLINE;
	acu.border.bs = ACS_HLINE;
	acu.border.tl = ACS_ULCORNER;
	acu.border.tr = ACS_URCORNER;
	acu.border.bl = ACS_LLCORNER;
	acu.border.br = ACS_LRCORNER;
	drawprimitive(&acu);
	mvwprintw(stdscr,y0+28,x0+104,"ALU");
	mvwprintw(stdscr,y0+29,x0+103,"Control");
	mvwprintw(stdscr,y0+30,x0+104,"Unit");

	/*
	 * EX/MEM Latch
	 */
	idexlatch.height = 27;
	idexlatch.width = 7;
	idexlatch.starty = y0+9;
	idexlatch.startx = x0+115;
	idexlatch.border.ls = ACS_VLINE;
	idexlatch.border.rs = ACS_VLINE;
	idexlatch.border.ts = ACS_HLINE;
	idexlatch.border.bs = ACS_HLINE;
	idexlatch.border.tl = ACS_ULCORNER;
	idexlatch.border.tr = ACS_URCORNER;
	idexlatch.border.bl = ACS_LLCORNER;
	idexlatch.border.br = ACS_LRCORNER;
	drawprimitive(&idexlatch);
	mvwprintw(stdscr,y0+35,x0+116,"EX/MEM");

	/*
	 * EX/MEM.WB
	 */
	mvwaddch(stdscr,y0+13,x0+115,ACS_LTEE);
	for (int i = 116; i <= 121; i++)
		mvwaddch(stdscr,y0+13,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+13,x0+122,ACS_RTEE);
	mvwprintw(stdscr,y0+11,x0+118,"WB");

	/*
	 * EX/MEM.M
	 */
	mvwaddch(stdscr,y0+17,x0+115,ACS_LTEE);
	for (int i = 116; i <= 121; i++)
		mvwaddch(stdscr,y0+17,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+17,x0+122,ACS_RTEE);
	mvwprintw(stdscr,y0+15,x0+118,"M");

	/*
	 * ALU
	 */
	alu.height = 4;
	alu.width = 8;
	alu.starty = y0+20;
	alu.startx = x0+102;
	alu.border.ls = ACS_VLINE;
	alu.border.rs = ACS_VLINE;
	alu.border.ts = ACS_HLINE;
	alu.border.bs = ACS_HLINE;
	alu.border.tl = ACS_ULCORNER;
	alu.border.tr = ACS_URCORNER;
	alu.border.bl = ACS_LLCORNER;
	alu.border.br = ACS_LRCORNER;
	drawprimitive(&alu);
	mvwprintw(stdscr,y0+22,x0+105,"ALU");

	/*
	 * Data Memory
	 */
	dm.height = 10;
	dm.width = 17;
	dm.starty = vmidpoint(pci)+1;
	dm.startx = x0+128;
	dm.border.ls = ACS_VLINE;
	dm.border.rs = ACS_VLINE;
	dm.border.ts = ACS_HLINE;
	dm.border.bs = ACS_HLINE;
	dm.border.tl = ACS_ULCORNER;
	dm.border.tr = ACS_URCORNER;
	dm.border.bl = ACS_LLCORNER;
	dm.border.br = ACS_LRCORNER;
	drawprimitive(&dm);
	mvwprintw(stdscr,vmidpoint(pci)+2,x0+131,"Data Memory");
	mvwprintw(stdscr,vmidpoint(pci)+6,x0+129,"Address");
	mvwprintw(stdscr,vmidpoint(pci)+8,x0+135,"Data Value");
	mvwprintw(stdscr,vmidpoint(pci)+10,x0+129,"Written Value");

	/*
	 * Forwarding Unit
	 */
	fwd.height = 3;
	fwd.width = 11;
	fwd.starty = y0+36;
	fwd.startx = x0+100;
	fwd.border.ls = ACS_VLINE;
	fwd.border.rs = ACS_VLINE;
	fwd.border.ts = ACS_HLINE;
	fwd.border.bs = ACS_HLINE;
	fwd.border.tl = ACS_ULCORNER;
	fwd.border.tr = ACS_URCORNER;
	fwd.border.bl = ACS_LLCORNER;
	fwd.border.br = ACS_LRCORNER;
	drawprimitive(&fwd);
	mvwprintw(stdscr,y0+37,x0+101,"Forwarding");
	mvwprintw(stdscr,y0+38,x0+104,"Unit");

	/*
	 * MEM/WB Latch
	 */
	memwblatch.height = 24;
	memwblatch.width = 7;
	memwblatch.starty = y0+12;
	memwblatch.startx = x0+150;
	memwblatch.border.ls = ACS_VLINE;
	memwblatch.border.rs = ACS_VLINE;
	memwblatch.border.ts = ACS_HLINE;
	memwblatch.border.bs = ACS_HLINE;
	memwblatch.border.tl = ACS_ULCORNER;
	memwblatch.border.tr = ACS_URCORNER;
	memwblatch.border.bl = ACS_LLCORNER;
	memwblatch.border.br = ACS_LRCORNER;
	drawprimitive(&memwblatch);
	mvwprintw(stdscr,y0+35,x0+151,"MEM/WB");

	/*
	 * MEM/WB.WB
	 */
	mvwaddch(stdscr,y0+16,x0+150,ACS_LTEE);
	for (int i = 151; i <= 156; i++)
		mvwaddch(stdscr,y0+16,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+16,x0+157,ACS_RTEE);
	mvwprintw(stdscr,y0+14,x0+153,"WB");

	/*
	 * WB MUX
	 */
	wbmux.height = 4;
	wbmux.width = 3;
	wbmux.starty = y0+26;
	wbmux.startx = x0+161;
	wbmux.border.ls = ACS_VLINE;
	wbmux.border.rs = ACS_VLINE;
	wbmux.border.ts = ACS_HLINE;
	wbmux.border.bs = ACS_HLINE;
	wbmux.border.tl = ACS_ULCORNER;
	wbmux.border.tr = ACS_URCORNER;
	wbmux.border.bl = ACS_LLCORNER;
	wbmux.border.br = ACS_LRCORNER;
	drawprimitive(&wbmux);
	mvwprintw(stdscr,y0+27,x0+162,"M");
	mvwprintw(stdscr,y0+28,x0+162,"U");
	mvwprintw(stdscr,y0+29,x0+162,"X");

}

void mvm::gui::gui::drawprimitive(struct win_s *p, bool border)
{
	int x, y, w, h;

	x = p->startx;
	y = p->starty;
	w = p->width;
	h = p->height;

	if (border == TRUE) {
		mvwaddch(stdscr, y, x, p->border.tl);
		mvwaddch(stdscr, y, x + w, p->border.tr);
		mvwaddch(stdscr, y + h, x, p->border.bl);
		mvwaddch(stdscr, y + h, x + w, p->border.br);
		mvwhline(stdscr, y, x + 1, p->border.ts, w - 1);
		mvwhline(stdscr, y + h, x + 1, p->border.bs, w - 1);
		mvwvline(stdscr, y + 1, x, p->border.ls, h - 1);
		mvwvline(stdscr, y + 1, x + w, p->border.rs, h - 1);
	} else {
		for(int j = y; j <= y + h; ++j)
			for(int i = x; i <= x + w; ++i)
				mvwaddch(stdscr,j, i, ' ');
	}
}

void mvm::gui::gui::resize(const int my, const int mx)
{
	x1 = mx;
	y1 = my;
	draw();
}

void mvm::gui::gui::drawdatapaths()
{
	int i;
	/*
	 * PC -> Instruction Memory
	 */
	mvwaddch(stdscr,vmidpoint(pc),x0+7,ACS_LTEE);
	mvwaddch(stdscr,vmidpoint(pc),x0+8,ACS_BTEE);
	mvwaddch(stdscr,vmidpoint(pc),x0+9,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pc),x0+10,ACS_RARROW);

	/*
	 * Instruction Memory -> IF/ID Latch
	 */
	mvwaddch(stdscr,y0+29,x0+22,ACS_LTEE);
	mvwaddch(stdscr,y0+29,x0+23,ACS_HLINE);
	mvwaddch(stdscr,y0+29,x0+24,ACS_HLINE);
	mvwaddch(stdscr,y0+29,x0+25,ACS_RARROW);

	/*
	 * PC -> PC Incrementer
	 */
	mvwaddch(stdscr,y0+18,x0+8,ACS_ULCORNER);
	for (i = 19; i <= 26; i++)
		mvwaddch(stdscr,y0+i,x0+8,ACS_VLINE);
	for (i = 9; i <= 12; i++)
		mvwaddch(stdscr,y0+18,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+18,x0+13,ACS_RARROW);

	/*
	 * 4 -> PC Incrementer
	 */
	mvwaddch(stdscr,y0+20,x0+13,ACS_RARROW);
	mvwaddch(stdscr,y0+20,x0+12,ACS_HLINE);
	mvwaddch(stdscr,y0+20,x0+11,ACS_HLINE);
	mvwaddch(stdscr,y0+20,x0+10,'4');

	/*
	 * PC Incrementer -> IF/ID Latch
	 */
	mvwaddch(stdscr,vmidpoint(pci),x0+19,ACS_LTEE);
	mvwaddch(stdscr,vmidpoint(pci),x0+20,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci),x0+21,ACS_BTEE);
	mvwaddch(stdscr,vmidpoint(pci),x0+22,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci),x0+23,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci),x0+24,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci),x0+25,ACS_RARROW);

	/*
	 * PC Incrementer -> IF MUX
	 */
	mvwaddch(stdscr,y0+18,x0+21,ACS_VLINE);
	mvwaddch(stdscr,y0+17,x0+21,ACS_VLINE);
	mvwaddch(stdscr,y0+16,x0+21,ACS_URCORNER);
	for (i = 20; i >= 13; i--)
		mvwaddch(stdscr,y0+16,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+16,x0+12,ACS_LLCORNER);
	mvwaddch(stdscr,y0+15,x0+12,ACS_VLINE);
	mvwaddch(stdscr,y0+14,x0+12,ACS_ULCORNER);
	mvwaddch(stdscr,y0+14,x0+13,ACS_HLINE);
	mvwaddch(stdscr,y0+14,x0+14,ACS_RARROW);

	/*
	 * 40000040 -> IF MUX
	 */
	mvwaddch(stdscr,y0+13,x0+14,ACS_RARROW);
	mvwaddch(stdscr,y0+13,x0+13,ACS_HLINE);
	mvwaddch(stdscr,y0+13,x0+12,ACS_HLINE);
	mvwprintw(stdscr,y0+13,x0+4,"40000040");

	/*
	 * IF MUX -> PC
	 */
	mvwaddch(stdscr,y0+13,x0+18,ACS_LTEE);
	mvwaddch(stdscr,y0+13,x0+19,ACS_HLINE);
	mvwaddch(stdscr,y0+13,x0+20,ACS_LRCORNER);
	mvwaddch(stdscr,y0+12,x0+20,ACS_VLINE);
	mvwaddch(stdscr,y0+11,x0+20,ACS_VLINE);
	mvwaddch(stdscr,y0+10,x0+20,ACS_URCORNER);
	for (i = 19; i >= 3; i--)
		mvwaddch(stdscr,y0+10,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+10,x0+2,ACS_ULCORNER);
	for (int i = 11; i <= 26; i++)
		mvwaddch(stdscr,y0+i,x0+2,ACS_VLINE);
	mvwaddch(stdscr,y0+27,x0+2,ACS_LLCORNER);
	mvwaddch(stdscr,y0+27,x0+3,ACS_HLINE);
	mvwaddch(stdscr,y0+27,x0+4,ACS_RARROW);

	/*
	 * IF/ID Latch -> Hazard Detection Unit
	 */
	mvwaddch(stdscr,y0+6,x0+32,ACS_ULCORNER);
	for (i = 33; i <= 39; i++)
		mvwaddch(stdscr,y0+6,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+6,x0+40,ACS_RARROW);
	for (i = 7; i <= 29; i++)
		mvwaddch(stdscr,y0+i,x0+32,ACS_VLINE);

	/*
	 * IF/ID Latch -> Control Unit
	 */
	mvwaddch(stdscr,y0+14,x0+32,ACS_LTEE);
	for (i = 33; i <=38; i++)
		mvwaddch(stdscr,y0+14,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+14,x0+39,ACS_RARROW);
	mvwaddch(stdscr,y0+29,x0+32,ACS_LRCORNER);
	mvwaddch(stdscr,y0+29,x0+31,ACS_LTEE);

	/*
	 * IF/ID Latch -> Register Memory (Read Register 1)
	 */
	mvwaddch(stdscr,vmidpoint(pci)+3,x0+32,ACS_LTEE);
	for (i = 33; i <= 49; i++)
		mvwaddch(stdscr,vmidpoint(pci)+3,x0+i,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+3,x0+50,ACS_RARROW);

	/*
	 * IF/ID Latch -> Register Memory (Read Register 2)
	 */
	mvwaddch(stdscr,vmidpoint(pci)+4,x0+32,ACS_LTEE);
	for (i = 33; i <= 49; i++)
		mvwaddch(stdscr,vmidpoint(pci)+4,x0+i,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+4,x0+50,ACS_RARROW);

	/*
	 * Register Memory (Read Data 1) -> ID/EX Latch
	 */
	mvwaddch(stdscr,vmidpoint(pci)+2,x0+67,ACS_LTEE);
	for (i = 68; i <= 74; i++)
		mvwaddch(stdscr,vmidpoint(pci)+2,x0+i,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+2,x0+75,ACS_RARROW);

	/*
	 * Register Memory (Read Data 2) -> ID/EX Latch
	 */
	mvwaddch(stdscr,vmidpoint(pci)+9,x0+67,ACS_LTEE);
	for (i = 68; i <= 74; i++)
		mvwaddch(stdscr,vmidpoint(pci)+9,x0+i,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+9,x0+75,ACS_RARROW);

	/*
	 * Register Memory (Read Data 1) -> ID Equals
	 */
	mvwaddch(stdscr,vmidpoint(pci)+2,x0+71,ACS_TTEE);
	mvwaddch(stdscr,vmidpoint(pci)+3,x0+71,ACS_VLINE);
	mvwaddch(stdscr,vmidpoint(pci)+4,x0+71,ACS_DARROW);

	/*
	 * Register Memory (Read Data 2) -> ID Equals
	 */
	mvwaddch(stdscr,vmidpoint(pci)+9,x0+71,ACS_BTEE);
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+71,ACS_UARROW);

	/*
	 * IF/ID Latch -> ID/EX Latch
	 */
	mvwaddch(stdscr,vmidpoint(pci),x0+32,ACS_LTEE);
	for (i = 33; i <= 74; i++)
		mvwaddch(stdscr,vmidpoint(pci),x0+i,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci),x0+75,ACS_RARROW);

	/*
	 * IF/ID Latch -> ID/EX Latch [Instruction 15-11]
	 */
	mvwaddch(stdscr,y0+35,x0+32,ACS_LLCORNER);
	for (i = 33; i <= 75; i++)
		mvwaddch(stdscr,y0+35,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+35,x0+75,ACS_RARROW);
	mvwaddch(stdscr,y0+29,x0+32,ACS_RTEE);
	for (i = 30; i <= 34; i++)
		mvwaddch(stdscr,y0+i,x0+32,ACS_VLINE);

	/*
	 * IF/ID Latch -> ID/EX Latch [Instruction 20-16]
	 */
	mvwaddch(stdscr,y0+34,x0+32,ACS_LTEE);
	for (i = 33; i <= 74; i++)
		mvwaddch(stdscr,y0+34,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+34,x0+75,ACS_RARROW);

	/*
	 * IF/ID Latch -> ID/EX Latch [Instruction 20-16]
	 */
	mvwaddch(stdscr,vmidpoint(pci)+4,x0+34,ACS_TTEE);
	for (i = vmidpoint(pci)+5-y0; i <= 32; i++)
		mvwaddch(stdscr,y0+i,x0+34,ACS_VLINE);
	mvwaddch(stdscr,y0+33,x0+34,ACS_LLCORNER);
	for (i = 35; i <= 74; i++)
		mvwaddch(stdscr,y0+33,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+33,x0+75,ACS_RARROW);

	/*
	 * IF/ID Latch -> ID/EX Latch [Instruction 25-21]
	 */
	mvwaddch(stdscr,vmidpoint(pci)+3,x0+33,ACS_TTEE);
	for (i = vmidpoint(pci)+4-y0; i <= 31; i++)
		mvwaddch(stdscr,y0+i,x0+33,ACS_VLINE);
	mvwaddch(stdscr,y0+32,x0+33,ACS_LLCORNER);
	for (i = 34; i <= 74; i++)
		mvwaddch(stdscr,y0+32,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+32,x0+75,ACS_RARROW);

	/*
	 * IF/ID Latch -> Sign Extension
	 */
	mvwaddch(stdscr,y0+30,x0+32,ACS_LTEE);
	for (i = 33; i <= 37; i++)
		mvwaddch(stdscr,y0+30,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+30,x0+38,ACS_RARROW);

	/*
	 * Sign Extension -> ID/EX Latch
	 */
	mvwaddch(stdscr,y0+30,x0+45,ACS_LTEE);
	mvwaddch(stdscr,y0+30,x0+46,ACS_URCORNER);
	mvwaddch(stdscr,y0+31,x0+46,ACS_LLCORNER);
	for (i = 47; i <= 74; i++)
		mvwaddch(stdscr,y0+31,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+31,x0+75,ACS_RARROW);

	/*
	 * Sign Extension -> IF MUX
	 */
	mvwaddch(stdscr,y0+31,x0+47,ACS_BTEE);
	for (i = 30; i >= 18; i--)
		mvwaddch(stdscr,y0+i,x0+47,ACS_VLINE);
	mvwaddch(stdscr,y0+17,x0+47,ACS_ULCORNER);
	for (i = 48; i <= 60; i++)
		mvwaddch(stdscr,y0+17,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+17,x0+61,ACS_LRCORNER);
	for (i = 16; i >= 3; i--)
		mvwaddch(stdscr,y0+i,x0+61,ACS_VLINE);
	mvwaddch(stdscr,y0+2,x0+61,ACS_URCORNER);
	for (i = 60; i >= 13; i--)
		mvwaddch(stdscr,y0+2,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+2,x0+12,ACS_ULCORNER);
	for (i = 3; i <= 11; i++)
		mvwaddch(stdscr,y0+i,x0+12,ACS_VLINE);
	mvwaddch(stdscr,y0+12,x0+12,ACS_LLCORNER);
	mvwaddch(stdscr,y0+12,x0+13,ACS_HLINE);
	mvwaddch(stdscr,y0+12,x0+14,ACS_RARROW);

	/*
	 * ID/EX Latch -> EX MUX 4 (3)
	 */
	mvwaddch(stdscr,y0+35,x0+81,ACS_LTEE);
	for (i = 82; i <= 87; i++)
		mvwaddch(stdscr,y0+35,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+35,x0+88,ACS_RARROW);

	/*
	 * ID/EX Latch -> EX MUX 4 (2)
	 */
	mvwaddch(stdscr,y0+34,x0+81,ACS_LTEE);
	for (i = 82; i <= 87; i++)
		mvwaddch(stdscr,y0+34,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+34,x0+88,ACS_RARROW);

	/*
	 * ID/EX Latch -> EX MUX 2
	 */
	if (!VM->dp->EXmux4->get_signal1()&&!VM->dp->EXmux4->get_signal2())
		attron(A_BOLD);
	mvwaddch(stdscr,y0+28,x0+81,ACS_LTEE);
	mvwaddch(stdscr,y0+28,x0+82,ACS_LRCORNER);
	for (i = 27; i >= 25; i--)
		mvwaddch(stdscr,y0+i,x0+82,ACS_VLINE);
	mvwaddch(stdscr,y0+24,x0+82,ACS_ULCORNER);
	for (i = 83; i <= 87; i++)
		mvwaddch(stdscr,y0+24,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+24,x0+88,ACS_RARROW);
	attroff(A_BOLD);

	/*
	 * EX MUX 2 -> EX MUX 3
	 */
	if (!(VM->dp->EXmux4->get_signal1()&&VM->dp->EXmux4->get_signal2()) && VM->dp->EXmux5->get_signal())
		attron(A_BOLD);
	mvwaddch(stdscr,y0+24,x0+91,ACS_LTEE);
	mvwaddch(stdscr,y0+24,x0+92,ACS_HLINE);
	mvwaddch(stdscr,y0+24,x0+93,ACS_HLINE);
	mvwaddch(stdscr,y0+24,x0+94,ACS_RARROW);
	attroff(A_BOLD);

	/*
	 * ID/EX Latch -> ALU Control Unit
	 */
	mvwaddch(stdscr,y0+29,x0+81,ACS_LTEE);
	for (i = 82; i <= 100; i++)
		mvwaddch(stdscr,y0+29,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+29,x0+101,ACS_RARROW);

	/*
	 * ID/EX Latch -> EX MUX 3
	 */
	mvwaddch(stdscr,y0+29,x0+93,ACS_BTEE);
	mvwaddch(stdscr,y0+28,x0+93,ACS_VLINE);
	mvwaddch(stdscr,y0+27,x0+93,ACS_VLINE);
	mvwaddch(stdscr,y0+26,x0+93,ACS_ULCORNER);
	mvwaddch(stdscr,y0+26,x0+94,ACS_RARROW);

	/*
	 * EX MUX 4 -> EX/MEM Latch
	 */
	mvwaddch(stdscr,y0+35,x0+91,ACS_LTEE);
	for (i = 92; i <= 114; i++)
		mvwaddch(stdscr,y0+35,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+35,x0+115,ACS_RARROW);

	/*
	 * EX MUX 2 -> EX/MEM Latch
	 */
	if (!(VM->dp->EXmux4->get_signal1()&&VM->dp->EXmux4->get_signal2()))
		attron(A_BOLD);
	mvwaddch(stdscr,y0+24,x0+92,ACS_TTEE);
	for (i = 25; i <= 33; i++)
		mvwaddch(stdscr,y0+i,x0+92,ACS_VLINE);
	mvwaddch(stdscr,y0+34,x0+92,ACS_LLCORNER);
	for (i = 93; i <= 114; i++)
		mvwaddch(stdscr,y0+34,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+34,x0+115,ACS_RARROW);
	attroff(A_BOLD);

	/*
	 * ID/EX Latch -> Hazard Detection Unit
	 */
	mvwaddch(stdscr,y0+34,x0+82,ACS_TTEE);
	mvwaddch(stdscr,y0+35,x0+82,ACS_VLINE);
	mvwaddch(stdscr,y0+36,x0+82,ACS_VLINE);
	mvwaddch(stdscr,y0+37,x0+82,ACS_LRCORNER);
	for (i = 81; i >= 38; i--)
		mvwaddch(stdscr,y0+37,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+37,x0+37,ACS_LLCORNER);
	for (i = 36; i >= 8; i--)
		mvwaddch(stdscr,y0+i,x0+37,ACS_VLINE);
	mvwaddch(stdscr,y0+7,x0+37,ACS_ULCORNER);
	mvwaddch(stdscr,y0+7,x0+38,ACS_HLINE);
	mvwaddch(stdscr,y0+7,x0+39,ACS_HLINE);
	mvwaddch(stdscr,y0+7,x0+40,ACS_RARROW);

	/*
	 * ID/EX Latch -> Forwarding Unit (1)
	 */
	mvwaddch(stdscr,y0+33,x0+81,ACS_LTEE);
	mvwaddch(stdscr,y0+33,x0+82,ACS_HLINE);
	mvwaddch(stdscr,y0+33,x0+83,ACS_URCORNER);
	for (i = 34; i <= 37; i++)
		mvwaddch(stdscr,y0+i,x0+83,ACS_VLINE);
	mvwaddch(stdscr,y0+38,x0+83,ACS_LLCORNER);
	for (i = 84; i <= 99; i++)
		mvwaddch(stdscr,y0+38,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+38,x0+100,ACS_RARROW);

	/*
	 * ID/EX Latch -> Forwarding Unit (2)
	 */
	mvwaddch(stdscr,y0+32,x0+81,ACS_LTEE);
	mvwaddch(stdscr,y0+32,x0+82,ACS_HLINE);
	mvwaddch(stdscr,y0+32,x0+83,ACS_HLINE);
	mvwaddch(stdscr,y0+32,x0+84,ACS_URCORNER);
	for (i = 33; i <= 36; i++)
		mvwaddch(stdscr,y0+i,x0+84,ACS_VLINE);
	mvwaddch(stdscr,y0+37,x0+84,ACS_LLCORNER);
	for (i = 85; i <= 99; i++)
		mvwaddch(stdscr,y0+37,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+37,x0+100,ACS_RARROW);
	
	/*
	 * ALU -> EX/MEM Latch
	 */
	mvwaddch(stdscr,y0+22,x0+110,ACS_LTEE);
	for (i = 111; i <= 114; i++)
		mvwaddch(stdscr,y0+22,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+22,x0+115,ACS_RARROW);

	/*
	 * EX MUX 3 -> ALU
	 */
	attron(A_BOLD);
	mvwaddch(stdscr,y0+25,x0+97,ACS_LTEE);
	mvwaddch(stdscr,y0+25,x0+98,ACS_HLINE);
	mvwaddch(stdscr,y0+25,x0+99,ACS_LRCORNER);
	mvwaddch(stdscr,y0+24,x0+99,ACS_VLINE);
	mvwaddch(stdscr,y0+23,x0+99,ACS_ULCORNER);
	mvwaddch(stdscr,y0+23,x0+100,ACS_HLINE);
	mvwaddch(stdscr,y0+23,x0+101,ACS_HLINE);
	mvwaddch(stdscr,y0+23,x0+102,ACS_RARROW);
	attroff(A_BOLD);

	/*
	 * EX MUX 1 -> ALU
	 */
	if (!(VM->dp->EXmux3->get_signal1()&&VM->dp->EXmux3->get_signal2()))
		attron(A_BOLD);
	mvwaddch(stdscr,y0+19,x0+91,ACS_LTEE);
	for (i = 92; i <= 98; i++)
		mvwaddch(stdscr,y0+19,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+19,x0+99,ACS_URCORNER);
	mvwaddch(stdscr,y0+20,x0+99,ACS_VLINE);
	mvwaddch(stdscr,y0+21,x0+99,ACS_LLCORNER);
	mvwaddch(stdscr,y0+21,x0+100,ACS_HLINE);
	mvwaddch(stdscr,y0+21,x0+101,ACS_HLINE);
	mvwaddch(stdscr,y0+21,x0+102,ACS_RARROW);
	attroff(A_BOLD);

	/*
	 * EX/MEM Latch -> Data Memory (Address)
	 */
	mvwaddch(stdscr,vmidpoint(pci)+6,x0+122,ACS_LTEE);
	for (i = 123; i <= 127; i++)
		mvwaddch(stdscr,vmidpoint(pci)+6,x0+i,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+6,x0+128,ACS_RARROW);

	/*
	 * EX/MEM Latch -> Data Memory (Written Value)
	 */
	mvwaddch(stdscr,y0+34,x0+122,ACS_LTEE);
	mvwaddch(stdscr,y0+34,x0+123,ACS_HLINE);
	mvwaddch(stdscr,y0+34,x0+124,ACS_LRCORNER);
	for (i = 33; i >= 30; i--)
		mvwaddch(stdscr,y0+i,x0+124,ACS_VLINE);
	mvwaddch(stdscr,y0+29,x0+124,ACS_ULCORNER);
	mvwaddch(stdscr,y0+29,x0+125,ACS_HLINE);
	mvwaddch(stdscr,y0+29,x0+126,ACS_HLINE);
	mvwaddch(stdscr,y0+29,x0+127,ACS_HLINE);
	mvwaddch(stdscr,y0+29,x0+128,ACS_RARROW);

	/*
	 * Data Memory -> MEM/WB Latch
	 */
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+145,ACS_LTEE);
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+146,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+147,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+148,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+149,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+150,ACS_RARROW);

	/*
	 * EX/MEM Latch -> MEM/WB Latch
	 */
	mvwaddch(stdscr,y0+35,x0+122,ACS_LTEE);
	for (i = 123; i <= 149; i++)
		mvwaddch(stdscr,y0+35,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+35,x0+150,ACS_RARROW);

	/*
	 * EX/MEM Latch -> Forwarding Unit
	 */
	mvwaddch(stdscr,y0+35,x0+124,ACS_TTEE);
	mvwaddch(stdscr,y0+36,x0+124,ACS_VLINE);
	mvwaddch(stdscr,y0+37,x0+124,ACS_LRCORNER);
	for (i = 123; i >= 112; i--)
		mvwaddch(stdscr,y0+37,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+37,x0+111,ACS_LARROW);

	/*
	 * EX/MEM Latch -> EX MUX 1
	 */
	if (VM->dp->EXmux3->get_signal1()&&!VM->dp->EXmux3->get_signal2())
		attron(A_BOLD);
	mvwaddch(stdscr,vmidpoint(pci)+6,x0+126,ACS_TTEE);
	for (i = vmidpoint(pci)+7-y0; i <= 39; i++)
		mvwaddch(stdscr,y0+i,x0+126,ACS_VLINE);
	mvwaddch(stdscr,y0+40,x0+126,ACS_LRCORNER);
	for (i = 125; i >= 86; i--)
		mvwaddch(stdscr,y0+40,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+40,x0+85,ACS_LLCORNER);
	for (i = 39; i >= 21; i--)
		mvwaddch(stdscr,y0+i,x0+85,ACS_VLINE);
	mvwaddch(stdscr,y0+20,x0+85,ACS_ULCORNER);
	mvwaddch(stdscr,y0+20,x0+86,ACS_HLINE);
	mvwaddch(stdscr,y0+20,x0+87,ACS_HLINE);
	mvwaddch(stdscr,y0+20,x0+88,ACS_RARROW);
	attroff(A_BOLD);

	/*
	 * EX/MEM Latch -> MEM/WB Latch (2)
	 */
	mvwaddch(stdscr,y0+33,x0+126,ACS_LTEE);
	for (i = 127; i <= 149; i++)
		mvwaddch(stdscr,y0+33,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+33,x0+150,ACS_RARROW);

	/*
	 * MEM/WB Latch -> Forwarding Unit
	 */
	mvwaddch(stdscr,y0+35,x0+157,ACS_LTEE);
	mvwaddch(stdscr,y0+35,x0+158,ACS_URCORNER);
	mvwaddch(stdscr,y0+36,x0+158,ACS_VLINE);
	mvwaddch(stdscr,y0+37,x0+158,ACS_VLINE);
	mvwaddch(stdscr,y0+38,x0+158,ACS_LRCORNER);
	for (i = 157; i >= 112; i--)
		mvwaddch(stdscr,y0+38,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+38,x0+111,ACS_LARROW);

	/*
	 * MEM/WB Latch -> WB MUX
	 */
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+157,ACS_LTEE);
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+158,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+159,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+160,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+8,x0+161,ACS_RARROW);

	/*
	 * MEM/WB Latch -> WB MUX (2)
	 */
	mvwaddch(stdscr,y0+33,x0+157,ACS_LTEE);
	mvwaddch(stdscr,y0+33,x0+158,ACS_HLINE);
	mvwaddch(stdscr,y0+33,x0+159,ACS_LRCORNER);
	for (i = vmidpoint(pci)+10; i < y0+33; i++)
		mvwaddch(stdscr,i,x0+159,ACS_VLINE);
	mvwaddch(stdscr,vmidpoint(pci)+10,x0+159,ACS_ULCORNER);
	mvwaddch(stdscr,vmidpoint(pci)+10,x0+160,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)+10,x0+161,ACS_RARROW);

	/*
	 * WB MUX -> Register Memory (Write Data)
	 */
	mvwaddch(stdscr,y0+28,x0+164,ACS_LTEE);
	mvwaddch(stdscr,y0+28,x0+165,ACS_HLINE);
	mvwaddch(stdscr,y0+28,x0+166,ACS_URCORNER);
	for (i = 29; i <= 40; i++)
		mvwaddch(stdscr,y0+i,x0+166,ACS_VLINE);
	mvwaddch(stdscr,y0+41,x0+166,ACS_LRCORNER);
	for (i = 165; i >= 50; i--)
		mvwaddch(stdscr,y0+41,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+41,x0+49,ACS_LLCORNER);
	for (i = 40; i >= 30; i--)
		mvwaddch(stdscr,y0+i,x0+49,ACS_VLINE);
	mvwaddch(stdscr,y0+29,x0+49,ACS_ULCORNER);
	mvwaddch(stdscr,y0+29,x0+50,ACS_RARROW);

	/*
	 * MEM/WB Latch -> Register Memory (Write Register)
	 */
	mvwaddch(stdscr,y0+38,x0+140,ACS_TTEE);
	for (i = 39; i <= 41; i++)
		mvwaddch(stdscr,y0+i,x0+140,ACS_VLINE);
	mvwaddch(stdscr,y0+42,x0+140,ACS_LRCORNER);
	for (i = 139; i >= 49; i--)
		mvwaddch(stdscr,y0+42,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+42,x0+48,ACS_LLCORNER);
	for (i = 41; i >= 28; i--)
		mvwaddch(stdscr,y0+i,x0+48,ACS_VLINE);
	mvwaddch(stdscr,y0+27,x0+48,ACS_ULCORNER);
	mvwaddch(stdscr,y0+27,x0+49,ACS_HLINE);
	mvwaddch(stdscr,y0+27,x0+50,ACS_RARROW);

	/*
	 * EX/MEM Latch -> EX MUX 2
	 */
	if (VM->dp->EXmux4->get_signal1()&&!VM->dp->EXmux4->get_signal2())
		attron(A_BOLD);
	mvwaddch(stdscr,y0+26,x0+85,ACS_LTEE);
	mvwaddch(stdscr,y0+26,x0+86,ACS_HLINE);
	mvwaddch(stdscr,y0+26,x0+87,ACS_HLINE);
	mvwaddch(stdscr,y0+26,x0+88,ACS_RARROW);
	attroff(A_BOLD);

	/*
	 * WB MUX -> EX MUX 1
	 */
	if (!VM->dp->EXmux3->get_signal1()&&VM->dp->EXmux3->get_signal2())
		attron(A_BOLD);
	mvwaddch(stdscr,y0+41,x0+86,ACS_BTEE);
	for (i = 40; i >= 20; i--)
		mvwaddch(stdscr,y0+i,x0+86,ACS_VLINE);
	mvwaddch(stdscr,y0+19,x0+86,ACS_ULCORNER);
	mvwaddch(stdscr,y0+19,x0+87,ACS_HLINE);
	mvwaddch(stdscr,y0+19,x0+88,ACS_RARROW);
	attroff(A_BOLD);

	/*
	 * WB MUX -> EX MUX 2
	 */
	if (!VM->dp->EXmux4->get_signal1()&&VM->dp->EXmux4->get_signal2())
		attron(A_BOLD);
	mvwaddch(stdscr,y0+25,x0+86,ACS_LTEE);
	mvwaddch(stdscr,y0+25,x0+87,ACS_HLINE);
	mvwaddch(stdscr,y0+25,x0+88,ACS_RARROW);
	attroff(A_BOLD);

	/*
	 * ID/EX Latch -> EX MUX 1
	 */
	if (!VM->dp->EXmux3->get_signal1()&&!VM->dp->EXmux3->get_signal2())
		attron(A_BOLD);
	mvwaddch(stdscr,y0+19,x0+81,ACS_LTEE);
	mvwaddch(stdscr,y0+19,x0+82,ACS_HLINE);
	mvwaddch(stdscr,y0+19,x0+83,ACS_LRCORNER);
	mvwaddch(stdscr,y0+18,x0+83,ACS_ULCORNER);
	for (i = 84; i <= 87; i++)
		mvwaddch(stdscr,y0+18,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+18,x0+88,ACS_RARROW);
	attroff(A_BOLD);
}

void mvm::gui::gui::drawcontrolpaths()
{
	int i;
	/*
	 * IF AND -> IF MUX
	 */
	mvwaddch(stdscr,y0+6,x0+15,ACS_TTEE);
	for (i = 7; i <= 10; i++)
		mvwaddch(stdscr,y0+i,x0+15,ACS_VLINE);
	mvwaddch(stdscr,y0+11,x0+15,ACS_DARROW);

	/*
	 * Hazard Detection Unit -> IF/ID Latch
	 */
	mvwaddch(stdscr,y0+5,x0+40,ACS_RTEE);
	for (i = 39; i >= 29; i--)
		mvwaddch(stdscr,y0+5,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+5,x0+28,ACS_ULCORNER);
	for (i = 6; i <= 15; i++)
		mvwaddch(stdscr,y0+i,x0+28,ACS_VLINE);
	mvwaddch(stdscr,y0+16,x0+28,ACS_DARROW);

	/*
	 * Hazard Detection Unit -> PC
	 */
	mvwaddch(stdscr,y0+4,x0+40,ACS_RTEE);
	for (i = 39; i >= 23; i--)
		mvwaddch(stdscr,y0+4,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+4,x0+22,ACS_ULCORNER);
	mvwaddch(stdscr,y0+5,x0+22,ACS_VLINE);
	mvwaddch(stdscr,y0+6,x0+22,ACS_VLINE);
	mvwaddch(stdscr,y0+7,x0+22,ACS_LRCORNER);
	for (i = 21; i >= 4; i--)
		mvwaddch(stdscr,y0+7,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+7,x0+3,ACS_ULCORNER);
	for (i = 8; i <= 24; i++)
		mvwaddch(stdscr,y0+i,x0+3,ACS_VLINE);
	mvwaddch(stdscr,y0+25,x0+3,ACS_LLCORNER);
	mvwaddch(stdscr,y0+25,x0+4,ACS_HLINE);
	mvwaddch(stdscr,y0+25,x0+5,ACS_URCORNER);
	mvwaddch(stdscr,y0+26,x0+5,ACS_DARROW);
	
	/*
	 * Control Unit -> IF MUX
	 */
	mvwaddch(stdscr,y0+10,x0+39,ACS_RTEE);
	mvwaddch(stdscr,y0+10,x0+38,ACS_LLCORNER);
	mvwaddch(stdscr,y0+9,x0+38,ACS_URCORNER);
	for (i = 37; i >= 18; i--)
		mvwaddch(stdscr,y0+9,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+9,x0+17,ACS_ULCORNER);
	mvwaddch(stdscr,y0+10,x0+17,ACS_VLINE);
	mvwaddch(stdscr,y0+11,x0+17,ACS_DARROW);

	/*
	 * Control Unit -> IF AND (Jump)
	 */
	mvwaddch(stdscr,y0+11,x0+39,ACS_RTEE);
	for (i = 38; i >= 31; i--)
		mvwaddch(stdscr,y0+11,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+11,x0+30,ACS_LLCORNER);
	for (i = 10; i >= 4; i--)
		mvwaddch(stdscr,y0+i,x0+30,ACS_VLINE);
	mvwaddch(stdscr,y0+3,x0+30,ACS_URCORNER);
	for (i = 29; i >= 18; i--)
		mvwaddch(stdscr,y0+3,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+3,x0+17,ACS_ULCORNER);
	mvwaddch(stdscr,y0+4,x0+17,ACS_DARROW);

	/*
	 * Control Unit -> ID MUX
	 */
	mvwaddch(stdscr,y0+11,x0+47,ACS_LTEE);
	for (i = 48; i <= 66; i++)
		mvwaddch(stdscr,y0+11,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+11,x0+67,ACS_RARROW);

	/*
	 * 0 -> ID MUX
	 */
	mvwaddch(stdscr,y0+13,x0+65,'0');
	mvwaddch(stdscr,y0+13,x0+66,ACS_HLINE);
	mvwaddch(stdscr,y0+13,x0+67,ACS_RARROW);

	/*
	 * ID OR -> ID MUX
	 */
	mvwaddch(stdscr,y0+7,x0+68,ACS_TTEE);
	mvwaddch(stdscr,y0+8,x0+68,ACS_VLINE);
	mvwaddch(stdscr,y0+9,x0+68,ACS_VLINE);
	mvwaddch(stdscr,y0+10,x0+68,ACS_DARROW);

	/*
	 * Control Unit -> IF/ID Latch
	 */
	mvwaddch(stdscr,y0+10,x0+47,ACS_LTEE);
	for (i = 48; i <= 51; i++)
		mvwaddch(stdscr,y0+10,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+10,x0+52,ACS_LRCORNER);
	for (i = 9; i >= 2; i--)
		mvwaddch(stdscr,y0+i,x0+52,ACS_VLINE);
	mvwaddch(stdscr,y0+1,x0+52,ACS_URCORNER);
	for (i = 51; i >= 2; i--)
		mvwaddch(stdscr,y0+1,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+1,x0+1,ACS_ULCORNER);
	for (i = 2; i <= 34; i++)
		mvwaddch(stdscr,y0+i,x0+1,ACS_VLINE);
	mvwaddch(stdscr,y0+35,x0+1,ACS_LLCORNER);
	for (i = 2; i <= 24; i++)
		mvwaddch(stdscr,y0+35,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+35,x0+25,ACS_RARROW);

	/*
	 * Control Unit -> ID OR
	 */
	mvwaddch(stdscr,y0+12,x0+47,ACS_LTEE);
	for (i = 48; i <= 56; i++)
		mvwaddch(stdscr,y0+12,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+12,x0+57,ACS_LRCORNER);
	for (i = 11; i >= 4; i--)
		mvwaddch(stdscr,y0+i,x0+57,ACS_VLINE);
	mvwaddch(stdscr,y0+3,x0+57,ACS_ULCORNER);
	for (i = 58; i <= 67; i++)
		mvwaddch(stdscr,y0+3,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+3,x0+68,ACS_URCORNER);
	mvwaddch(stdscr,y0+4,x0+68,ACS_VLINE);
	mvwaddch(stdscr,y0+5,x0+68,ACS_DARROW);

	/*
	 * Hazard Unit -> ID OR
	 */
	mvwaddch(stdscr,y0+4,x0+50,ACS_LTEE);
	for (i = 51; i <= 66; i++)
		mvwaddch(stdscr,y0+4,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+4,x0+67,ACS_URCORNER);
	mvwaddch(stdscr,y0+5,x0+67,ACS_DARROW);
	
	/*
	 * ID MUX -> ID/EX Latch
	 */
	mvwaddch(stdscr,y0+12,x0+70,ACS_LTEE);
	mvwaddch(stdscr,y0+12,x0+71,ACS_HLINE);
	mvwaddch(stdscr,y0+12,x0+72,ACS_PLUS);
	mvwaddch(stdscr,y0+12,x0+73,ACS_HLINE);
	mvwaddch(stdscr,y0+12,x0+74,ACS_HLINE);
	mvwaddch(stdscr,y0+12,x0+75,ACS_RARROW);
	mvwaddch(stdscr,y0+11,x0+72,ACS_VLINE);
	mvwaddch(stdscr,y0+13,x0+72,ACS_VLINE);
	mvwaddch(stdscr,y0+10,x0+72,ACS_VLINE);
	mvwaddch(stdscr,y0+14,x0+72,ACS_VLINE);
	mvwaddch(stdscr,y0+9,x0+72,ACS_VLINE);
	mvwaddch(stdscr,y0+15,x0+72,ACS_VLINE);
	mvwaddch(stdscr,y0+8,x0+72,ACS_ULCORNER);
	mvwaddch(stdscr,y0+8,x0+73,ACS_HLINE);
	mvwaddch(stdscr,y0+8,x0+74,ACS_HLINE);
	mvwaddch(stdscr,y0+8,x0+75,ACS_RARROW);
	mvwaddch(stdscr,y0+16,x0+72,ACS_LLCORNER);
	mvwaddch(stdscr,y0+16,x0+73,ACS_HLINE);
	mvwaddch(stdscr,y0+16,x0+74,ACS_HLINE);
	mvwaddch(stdscr,y0+16,x0+75,ACS_RARROW);

	/*
	 * ID/EX.M -> EX MUX 5
	 */
	mvwaddch(stdscr,y0+12,x0+81,ACS_LTEE);
	for (i = 82; i <= 106; i++)
		mvwaddch(stdscr,y0+12,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+12,x0+107,ACS_RARROW);

	/*
	 * 0 -> EX MUX 5
	 */
	mvwaddch(stdscr,y0+14,x0+107,ACS_RARROW);
	mvwaddch(stdscr,y0+14,x0+106,ACS_HLINE);
	mvwaddch(stdscr,y0+14,x0+105,'0');

	/*
	 * ID/EX.M -> Register Memory
	 */
	mvwaddch(stdscr,y0+12,x0+83,ACS_BTEE);
	for (i = 11; i >= 2; i--)
		mvwaddch(stdscr,y0+i,x0+83,ACS_VLINE);
	mvwaddch(stdscr,y0+1,x0+83,ACS_URCORNER);
	for (i = 82; i >= 54; i--)
		mvwaddch(stdscr,y0+1,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+1,x0+53,ACS_ULCORNER);
	mvwaddch(stdscr,y0+2,x0+53,ACS_VLINE);
	mvwaddch(stdscr,y0+3,x0+53,ACS_VLINE);
	mvwaddch(stdscr,y0+4,x0+53,ACS_VLINE);
	mvwaddch(stdscr,y0+5,x0+53,ACS_LRCORNER);
	mvwaddch(stdscr,y0+5,x0+52,ACS_HLINE);
	mvwaddch(stdscr,y0+5,x0+51,ACS_HLINE);
	mvwaddch(stdscr,y0+5,x0+50,ACS_LARROW);

	/*
	 * EX MUX 5 -> EX/MEM.M
	 */
	mvwaddch(stdscr,y0+13,x0+110,ACS_LTEE);
	mvwaddch(stdscr,y0+13,x0+111,ACS_HLINE);
	mvwaddch(stdscr,y0+13,x0+112,ACS_URCORNER);
	mvwaddch(stdscr,y0+14,x0+112,ACS_VLINE);
	mvwaddch(stdscr,y0+15,x0+112,ACS_LLCORNER);
	mvwaddch(stdscr,y0+15,x0+113,ACS_HLINE);
	mvwaddch(stdscr,y0+15,x0+114,ACS_HLINE);
	mvwaddch(stdscr,y0+15,x0+115,ACS_RARROW);

	/*
	 * ID/EX.WB -> EX MUX 6
	 */
	mvwaddch(stdscr,y0+8,x0+81,ACS_LTEE);
	for (i = 82; i <= 101; i++)
		mvwaddch(stdscr,y0+8,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+8,x0+102,ACS_RARROW);
	
	/*
	 * 0 -> EX MUX 6
	 */
	mvwaddch(stdscr,y0+10,x0+100,'0');
	mvwaddch(stdscr,y0+10,x0+101,ACS_HLINE);
	mvwaddch(stdscr,y0+10,x0+102,ACS_RARROW);

	/*
	 * EX MUX 6 -> EX/MEM.WB
	 */
	mvwaddch(stdscr,y0+9,x0+105,ACS_LTEE);
	for (i = 106; i <= 111; i++)
		mvwaddch(stdscr,y0+9,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+9,x0+112,ACS_URCORNER);
	mvwaddch(stdscr,y0+10,x0+112,ACS_VLINE);
	mvwaddch(stdscr,y0+11,x0+112,ACS_LLCORNER);
	mvwaddch(stdscr,y0+11,x0+113,ACS_HLINE);
	mvwaddch(stdscr,y0+11,x0+114,ACS_HLINE);
	mvwaddch(stdscr,y0+11,x0+115,ACS_RARROW);

	/*
	 * Control Unit -> EX MUX 6
	 */
	mvwaddch(stdscr,y0+13,x0+47,ACS_LTEE);
	for (i = 48; i <= 54; i++)
		mvwaddch(stdscr,y0+13,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+13,x0+55,ACS_LRCORNER);
	for (i = 12; i >= 9; i--)
		mvwaddch(stdscr,y0+i,x0+55,ACS_VLINE);
	mvwaddch(stdscr,y0+8,x0+55,ACS_ULCORNER);
	for (i = 56; i <= 70; i++)
		mvwaddch(stdscr,y0+8,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+8,x0+71,ACS_LRCORNER);
	for (i = 7; i >= 4; i--)
		mvwaddch(stdscr,y0+i,x0+71,ACS_VLINE);
	mvwaddch(stdscr,y0+3,x0+71,ACS_ULCORNER);
	for (i = 72; i <= 102; i++)
		mvwaddch(stdscr,y0+3,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+3,x0+103,ACS_URCORNER);
	for (i = 4; i <= 6; i++)
		mvwaddch(stdscr,y0+i,x0+103,ACS_VLINE);
	mvwaddch(stdscr,y0+7,x0+103,ACS_DARROW);

	/*
	 * Control Unit -> EX MUX 5
	 */
	mvwaddch(stdscr,y0+5,x0+103,ACS_LTEE);
	mvwaddch(stdscr,y0+5,x0+104,ACS_HLINE);
	mvwaddch(stdscr,y0+5,x0+105,ACS_HLINE);
	mvwaddch(stdscr,y0+5,x0+106,ACS_HLINE);
	mvwaddch(stdscr,y0+5,x0+107,ACS_HLINE);
	mvwaddch(stdscr,y0+5,x0+108,ACS_URCORNER);
	for (i = 6; i <= 10; i++)
		mvwaddch(stdscr,y0+i,x0+108,ACS_VLINE);
	mvwaddch(stdscr,y0+11,x0+108,ACS_DARROW);

	/*
	 * EX/MEM.M -> Data Memory (MemWrite)
	 */
	if (VM->dp->ex_mem->M->get()&0x40000000)
		attron(A_BOLD);
	mvwaddch(stdscr,y0+15,x0+122,ACS_LTEE);
	for (i = 123; i <= 135; i++)
		mvwaddch(stdscr,y0+15,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+15,x0+136,ACS_URCORNER);
	for (i = 16; i <= 19; i++)
		mvwaddch(stdscr,y0+i,x0+136,ACS_VLINE);
	mvwaddch(stdscr,y0+20,x0+136,ACS_DARROW);
	attroff(A_BOLD);

	/*
	 * EX/MEM.M -> Data Memory (MemRead)
	 */
	if (VM->dp->ex_mem->M->get()&0x80000000)
		attron(A_BOLD);
	mvwaddch(stdscr,y0+14,x0+122,ACS_LTEE);
	for (i = 123; i <= 146; i++)
		mvwaddch(stdscr,y0+14,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+14,x0+147,ACS_URCORNER);
	for (i = 15; i <= 30; i++)
		mvwaddch(stdscr,y0+i,x0+147,ACS_VLINE);
	mvwaddch(stdscr,y0+31,x0+147,ACS_LRCORNER);
	for (i = 146; i >= 137; i--)
		mvwaddch(stdscr,y0+31,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+31,x0+136,ACS_LLCORNER);
	mvwaddch(stdscr,y0+30,x0+136,ACS_UARROW);
	attroff(A_BOLD);

	/*
	 * EX/MEM.WB -> MEM/WB.WB
	 */
	mvwaddch(stdscr,y0+11,x0+122,ACS_LTEE);
	for (i = 123; i <= 148; i++)
		mvwaddch(stdscr,y0+11,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+11,x0+149,ACS_URCORNER);
	mvwaddch(stdscr,y0+12,x0+149,ACS_VLINE);
	mvwaddch(stdscr,y0+13,x0+149,ACS_VLINE);
	mvwaddch(stdscr,y0+14,x0+149,ACS_LLCORNER);
	mvwaddch(stdscr,y0+14,x0+150,ACS_RARROW);

	/*
	 * EX/MEM.WB -> Forwarding unit
	 */
	mvwaddch(stdscr,y0+11,x0+123,ACS_TTEE);
	for (i = 12; i <= 38; i++)
		mvwaddch(stdscr,y0+i,x0+123,ACS_VLINE);
	mvwaddch(stdscr,y0+39,x0+123,ACS_LRCORNER);
	for (i = 122; i >= 115; i--)
		mvwaddch(stdscr,y0+39,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+39,x0+114,ACS_LLCORNER);
	mvwaddch(stdscr,y0+38,x0+114,ACS_VLINE);
	mvwaddch(stdscr,y0+37,x0+114,ACS_VLINE);
	mvwaddch(stdscr,y0+36,x0+114,ACS_URCORNER);
	mvwaddch(stdscr,y0+36,x0+113,ACS_HLINE);
	mvwaddch(stdscr,y0+36,x0+112,ACS_HLINE);
	mvwaddch(stdscr,y0+36,x0+111,ACS_LARROW);

	/*
	 * MEM/WB.WB -> Register Memory (RegWrite)
	 */
	if (VM->dp->mem_wb->WB->get()&0x80000000)
		attron(A_BOLD);
	mvwaddch(stdscr,y0+14,x0+157,ACS_LTEE);
	mvwaddch(stdscr,y0+14,x0+158,ACS_HLINE);
	mvwaddch(stdscr,y0+14,x0+159,ACS_HLINE);
	mvwaddch(stdscr,y0+14,x0+160,ACS_LRCORNER);
	for (i = 13; i >= 3; i--)
		mvwaddch(stdscr,y0+i,x0+160,ACS_VLINE);
	mvwaddch(stdscr,y0+2,x0+160,ACS_URCORNER);
	for (i = 159; i >= 63; i--)
		mvwaddch(stdscr,y0+2,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+2,x0+62,ACS_ULCORNER);
	for (i = 3; i <= 19; i++)
		mvwaddch(stdscr,y0+i,x0+62,ACS_VLINE);
	mvwaddch(stdscr,y0+20,x0+62,ACS_DARROW);
	attroff(A_BOLD);

	/*
	 * MEM/WB.WB -> Forwarding Unit
	 */
	mvwaddch(stdscr,y0+14,x0+160,ACS_RTEE);
	for (i = 15; i <= 42; i++)
		mvwaddch(stdscr,y0+i,x0+160,ACS_VLINE);
	mvwaddch(stdscr,y0+43,x0+160,ACS_LRCORNER);
	for (i = 159; i >= 114; i--)
		mvwaddch(stdscr,y0+43,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+43,x0+113,ACS_LLCORNER);
	for (i = 42; i >= 40; i--)
		mvwaddch(stdscr,y0+i,x0+113,ACS_VLINE);
	mvwaddch(stdscr,y0+39,x0+113,ACS_URCORNER);
	mvwaddch(stdscr,y0+39,x0+112,ACS_HLINE);
	mvwaddch(stdscr,y0+39,x0+111,ACS_LARROW);

	/*
	 * MEM/WB.WB -> WB MUX
	 */
	mvwaddch(stdscr,y0+15,x0+157,ACS_LTEE);
	for (i = 158; i <= 161; i++)
		mvwaddch(stdscr,y0+15,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+15,x0+162,ACS_URCORNER);
	for (i = 16; i <= 25; i++)
		mvwaddch(stdscr,y0+i,x0+162,ACS_VLINE);
	mvwaddch(stdscr,y0+26,x0+162,ACS_DARROW);

	/*
	 * ALU Control Unit -> ALU
	 */
	mvwaddch(stdscr,y0+26,x0+106,ACS_BTEE);
	mvwaddch(stdscr,y0+25,x0+106,ACS_VLINE);
	mvwaddch(stdscr,y0+24,x0+106,ACS_UARROW);

	/*
	 * ID/EX.EX -> EX MUX 4
	 */
	mvwaddch(stdscr,y0+17,x0+81,ACS_LTEE);
	mvwaddch(stdscr,y0+17,x0+82,ACS_HLINE);
	mvwaddch(stdscr,y0+17,x0+83,ACS_HLINE);
	mvwaddch(stdscr,y0+17,x0+84,ACS_URCORNER);
	for (i = 18; i <= 30; i++)
		mvwaddch(stdscr,y0+i,x0+84,ACS_VLINE);
	mvwaddch(stdscr,y0+31,x0+84,ACS_LLCORNER);
	for (i = 85; i <= 88; i++)
		mvwaddch(stdscr,y0+31,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+31,x0+89,ACS_URCORNER);
	mvwaddch(stdscr,y0+32,x0+89,ACS_DARROW);

	/*
	 * ID/EX.EX -> ALU Control Unit
	 */
	mvwaddch(stdscr,y0+15,x0+81,ACS_LTEE);
	for (i = 82; i <= 99; i++)
		mvwaddch(stdscr,y0+15,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+15,x0+100,ACS_URCORNER);
	for (i = 16; i <= 26; i++)
		mvwaddch(stdscr,y0+i,x0+100,ACS_VLINE);
	mvwaddch(stdscr,y0+27,x0+100,ACS_LLCORNER);
	mvwaddch(stdscr,y0+27,x0+101,ACS_RARROW);

	/*
	 * ID/EX.EX -> EX MUX 3
	 */
	if (!VM->dp->EXmux5->get_signal())
		attron(A_BOLD);
	mvwaddch(stdscr,y0+16,x0+81,ACS_LTEE);
	for (i = 82; i <= 94; i++)
		mvwaddch(stdscr,y0+16,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+16,x0+95,ACS_URCORNER);
	for (i = 17; i <= 22; i++)
		mvwaddch(stdscr,y0+i,x0+95,ACS_VLINE);
	mvwaddch(stdscr,y0+23,x0+95,ACS_DARROW);
	attroff(A_BOLD);

	/*
	 * Forwarding Unit -> EX MUX 2
	 */
	mvwaddch(stdscr,y0+36,x0+100,ACS_TTEE);
	for (i = 99; i >= 95; i--)
		mvwaddch(stdscr,y0+36,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+36,x0+94,ACS_LLCORNER);
	for (i = 35; i >= 31; i--)
		mvwaddch(stdscr,y0+i,x0+94,ACS_VLINE);
	mvwaddch(stdscr,y0+30,x0+94,ACS_URCORNER);
	for (i = 93; i >= 90; i--)
		mvwaddch(stdscr,y0+30,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+30,x0+89,ACS_LLCORNER);
	mvwaddch(stdscr,y0+29,x0+89,ACS_VLINE);
	mvwaddch(stdscr,y0+28,x0+89,ACS_VLINE);
	mvwaddch(stdscr,y0+27,x0+89,ACS_UARROW);

	/*
	 * Forwarding Unit -> EX MUX 1
	 */
	mvwaddch(stdscr,y0+39,x0+100,ACS_BTEE);
	mvwaddch(stdscr,y0+39,x0+99,ACS_HLINE);
	mvwaddch(stdscr,y0+39,x0+98,ACS_LLCORNER);
	for (i = 38; i >= 23; i--)
		mvwaddch(stdscr,y0+i,x0+98,ACS_VLINE);
	mvwaddch(stdscr,y0+22,x0+98,ACS_URCORNER);
	for (i = 97; i >= 90; i--)
		mvwaddch(stdscr,y0+22,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+22,x0+89,ACS_LLCORNER);
	mvwaddch(stdscr,y0+21,x0+89,ACS_UARROW);

	/*
	 * ID Equals -> ID AND
	 */
	mvwaddch(stdscr,vmidpoint(pci)+6,x0+72,ACS_LTEE);
	mvwaddch(stdscr,vmidpoint(pci)+6,x0+73,ACS_LRCORNER);
	for (i = vmidpoint(pci)+5; i >= vmidpoint(pci); i--)
		mvwaddch(stdscr,i,x0+73,ACS_VLINE);
	mvwaddch(stdscr,vmidpoint(pci)-1,x0+73,ACS_URCORNER);
	for (i = 72; i >= 34; i--)
		mvwaddch(stdscr,vmidpoint(pci)-1,x0+i,ACS_HLINE);
	mvwaddch(stdscr,vmidpoint(pci)-1,x0+33,ACS_LLCORNER);
	mvwaddch(stdscr,vmidpoint(pci)-2,x0+33,ACS_VLINE);
	mvwaddch(stdscr,vmidpoint(pci)-3,x0+33,ACS_VLINE);
	mvwaddch(stdscr,vmidpoint(pci)-4,x0+33,ACS_VLINE);
	mvwaddch(stdscr,y0+14,x0+33,ACS_VLINE);
	mvwaddch(stdscr,y0+13,x0+33,ACS_URCORNER);
	for (i = 32; i >= 26; i--)
		mvwaddch(stdscr,y0+13,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+13,x0+25,ACS_LLCORNER);
	for (i = y0+12; i >= y0+9; i--)
		mvwaddch(stdscr,i,x0+25,ACS_VLINE);
	mvwaddch(stdscr,y0+8,x0+25,ACS_URCORNER);
	for (i = 24; i >= 10; i--)
		mvwaddch(stdscr,y0+8,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+8,x0+9,ACS_LLCORNER);
	for (i = 7; i >= 4; i--)
		mvwaddch(stdscr,y0+i,x0+9,ACS_VLINE);
	mvwaddch(stdscr,y0+3,x0+9,ACS_ULCORNER);
	for (i = 10; i <= 14; i++)
		mvwaddch(stdscr,y0+3,x0+i,ACS_HLINE);
	mvwaddch(stdscr,y0+3,x0+15,ACS_URCORNER);
	mvwaddch(stdscr,y0+4,x0+15,ACS_DARROW);
}
