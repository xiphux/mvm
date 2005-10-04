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

#define vmidpoint(b)	((b).starty+(b).height/2)
#define hmidpoint(b)	((b).startx+(b).width/2)

mvm::gui::gui::gui(unsigned int sy, unsigned int sx, unsigned int my, unsigned int mx): complete(false)
{
	x0 = sx;
	y0 = sy;
	x1 = mx;
	y1 = my;
}

mvm::gui::gui::~gui()
{
}

void mvm::gui::gui::keypressed(char ch)
{
	switch (ch) {
		case 27:
			complete = true;
			break;
	}
}

void mvm::gui::gui::draw()
{
	drawcomponents();
	drawdatapaths();
	drawcontrolpaths();
	touchwin(stdscr);
}

void mvm::gui::gui::drawcomponents()
{
	/*
	 * Bounding box
	 */
	bbox.height = 25;
	bbox.width = 80;
	bbox.starty = y0+1;
	bbox.startx = x0+1;
	bbox.border.ls = ACS_VLINE;
	bbox.border.rs = ACS_VLINE;
	bbox.border.ts = ACS_HLINE;
	bbox.border.bs = ACS_HLINE;
	bbox.border.tl = ACS_ULCORNER;
	bbox.border.tr = ACS_URCORNER;
	bbox.border.bl = ACS_LLCORNER;
	bbox.border.br = ACS_LRCORNER;
	drawprimitive(&bbox,false);
	drawprimitive(&bbox);
	
	/*
	 * PC
	 */
	pc.height = 2;
	pc.width = 3;
	pc.starty = bbox.starty+bbox.height*2/3+3;
	pc.startx = bbox.startx+3;
	pc.border.ls = ACS_VLINE;
	pc.border.rs = ACS_VLINE;
	pc.border.ts = ACS_HLINE;
	pc.border.bs = ACS_HLINE;
	pc.border.tl = ACS_ULCORNER;
	pc.border.tr = ACS_URCORNER;
	pc.border.bl = ACS_LLCORNER;
	pc.border.br = ACS_LRCORNER;
	drawprimitive(&pc);
	mvprintw(vmidpoint(pc),hmidpoint(pc),"PC");

	/*
	 * PC Incrementer
	 */
	pci.height = 4;
	pci.width = 6;
	pci.starty = bbox.starty+bbox.height/2-pci.height+3;
	pci.startx = bbox.startx+11;
	pci.border.ls = ACS_VLINE;
	pci.border.rs = ACS_VLINE;
	pci.border.ts = ACS_HLINE;
	pci.border.bs = ACS_HLINE;
	pci.border.tl = ACS_ULCORNER;
	pci.border.tr = ACS_URCORNER;
	pci.border.bl = ACS_LLCORNER;
	pci.border.br = ACS_LRCORNER;
	drawprimitive(&pci);
	mvprintw(vmidpoint(pci),hmidpoint(pci),"+");

	/*
	 * IF MUX
	 */
	ifmux.height = 4;
	ifmux.width = 4;
	ifmux.starty = bbox.starty+ifmux.height+1;
	ifmux.startx = bbox.startx+11;
	ifmux.border.ls = ACS_VLINE;
	ifmux.border.rs = ACS_VLINE;
	ifmux.border.ts = ACS_HLINE;
	ifmux.border.bs = ACS_HLINE;
	ifmux.border.tl = ACS_ULCORNER;
	ifmux.border.tr = ACS_URCORNER;
	ifmux.border.bl = ACS_LLCORNER;
	ifmux.border.br = ACS_LRCORNER;
	drawprimitive(&ifmux);
	mvprintw(ifmux.starty+1,hmidpoint(ifmux),"M");
	mvprintw(ifmux.starty+2,hmidpoint(ifmux),"U");
	mvprintw(ifmux.starty+3,hmidpoint(ifmux),"X");

	/*
	 * Instruction Memory
	 */
	im.height = 7;
	im.width = 12;
	im.starty = bbox.starty+bbox.height*2/3-im.height/3+2;
	im.startx = bbox.startx+8;
	im.border.ls = ACS_VLINE;
	im.border.rs = ACS_VLINE;
	im.border.ts = ACS_HLINE;
	im.border.bs = ACS_HLINE;
	im.border.tl = ACS_ULCORNER;
	im.border.tr = ACS_URCORNER;
	im.border.bl = ACS_LLCORNER;
	im.border.br = ACS_LRCORNER;
	drawprimitive(&im);
	mvprintw(im.starty+1,im.startx+1,"Instruction");
	mvprintw(im.starty+2,im.startx+3,"Memory");
	mvprintw(im.starty+4,im.startx+1,"Address");
	mvprintw(im.starty+6,im.startx+2,"Data Value");

	/*
	 * IF/ID Latch
	 */
	ifidlatch.height = 15;
	ifidlatch.width = 7;
	ifidlatch.starty = bbox.starty+bbox.height/3;
	ifidlatch.startx = bbox.startx+21;
	ifidlatch.border.ls = ACS_VLINE;
	ifidlatch.border.rs = ACS_VLINE;
	ifidlatch.border.ts = ACS_HLINE;
	ifidlatch.border.bs = ACS_HLINE;
	ifidlatch.border.tl = ACS_ULCORNER;
	ifidlatch.border.tr = ACS_URCORNER;
	ifidlatch.border.bl = ACS_LLCORNER;
	ifidlatch.border.br = ACS_LRCORNER;
	drawprimitive(&ifidlatch);
	mvprintw(ifidlatch.starty+ifidlatch.height-1,ifidlatch.startx+1,"IF/ID");
}

void mvm::gui::gui::drawprimitive(struct win_s *p, bool border)
{
	int x, y, w, h;

	x = p->startx;
	y = p->starty;
	w = p->width;
	h = p->height;

	if (border == TRUE) {
		mvaddch(y, x, p->border.tl);
		mvaddch(y, x + w, p->border.tr);
		mvaddch(y + h, x, p->border.bl);
		mvaddch(y + h, x + w, p->border.br);
		mvhline(y, x + 1, p->border.ts, w - 1);
		mvhline(y + h, x + 1, p->border.bs, w - 1);
		mvvline(y + 1, x, p->border.ls, h - 1);
		mvvline(y + 1, x + w, p->border.rs, h - 1);
	} else {
		for(int j = y; j <= y + h; ++j)
			for(int i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
	}
}

void mvm::gui::gui::resize(unsigned int my, unsigned int mx)
{
	x1 = mx;
	y1 = my;
}

void mvm::gui::gui::drawdatapaths()
{
	mvaddch(vmidpoint(pc),pc.startx+3,ACS_LTEE);
	mvaddch(vmidpoint(pc),pc.startx+4,ACS_BTEE);
	mvaddch(vmidpoint(pc),pc.startx+5,ACS_RARROW);
	mvaddch(im.starty+6,im.startx+12,ACS_LTEE);
	mvaddch(im.starty+6,im.startx+13,ACS_RARROW);
	mvaddch(pci.starty+1,pc.startx+4,ACS_ULCORNER);
	mvaddch(pci.starty+2,pc.startx+4,ACS_VLINE);
	mvaddch(pci.starty+3,pc.startx+4,ACS_VLINE);
	mvaddch(pci.starty+4,pc.startx+4,ACS_VLINE);
	mvaddch(pci.starty+5,pc.startx+4,ACS_VLINE);
	mvaddch(pci.starty+6,pc.startx+4,ACS_VLINE);
	mvaddch(pci.starty+7,pc.startx+4,ACS_VLINE);
	mvaddch(pci.starty+8,pc.startx+4,ACS_VLINE);
	mvaddch(pci.starty+1,pc.startx+5,ACS_HLINE);
	mvaddch(pci.starty+1,pc.startx+6,ACS_HLINE);
	mvaddch(pci.starty+1,pc.startx+7,ACS_HLINE);
	mvaddch(pci.starty+1,pc.startx+8,ACS_RARROW);
	mvaddch(pci.starty+3,pc.startx+8,ACS_RARROW);
	mvaddch(pci.starty+3,pc.startx+7,ACS_HLINE);
	mvaddch(pci.starty+3,pc.startx+6,'4');
	mvaddch(vmidpoint(pci),pci.startx+6,ACS_LTEE);
	mvaddch(vmidpoint(pci),pci.startx+7,ACS_BTEE);
	mvaddch(vmidpoint(pci),pci.startx+8,ACS_HLINE);
	mvaddch(vmidpoint(pci),pci.startx+9,ACS_HLINE);
	mvaddch(vmidpoint(pci),pci.startx+10,ACS_RARROW);
	mvaddch(vmidpoint(pci)-1,pci.startx+7,ACS_VLINE);
	mvaddch(pci.starty,pci.startx+7,ACS_VLINE);
	mvaddch(pci.starty-1,pci.startx+7,ACS_URCORNER);
	mvaddch(pci.starty-1,pci.startx+6,ACS_HLINE);
	mvaddch(pci.starty-1,pci.startx+5,ACS_HLINE);
	mvaddch(pci.starty-1,pci.startx+4,ACS_HLINE);
	mvaddch(pci.starty-1,pci.startx+3,ACS_HLINE);
	mvaddch(pci.starty-1,pci.startx+2,ACS_HLINE);
	mvaddch(pci.starty-1,pci.startx+1,ACS_HLINE);
	mvaddch(pci.starty-1,pci.startx,ACS_HLINE);
	mvaddch(pci.starty-1,pci.startx-1,ACS_LLCORNER);
	mvaddch(ifmux.starty+4,pci.startx-1,ACS_VLINE);
	mvaddch(ifmux.starty+3,pci.startx-1,ACS_ULCORNER);
	mvaddch(ifmux.starty+3,pci.startx,ACS_RARROW);
	mvaddch(ifmux.starty+2,pci.startx,ACS_RARROW);
	mvaddch(ifmux.starty+2,pci.startx-1,ACS_HLINE);
	mvprintw(ifmux.starty+2,pci.startx-9,"40000040");
	mvaddch(ifmux.starty+2,pci.startx+pci.width/2+1,ACS_LTEE);
	mvaddch(ifmux.starty+2,pci.startx+pci.width/2+2,ACS_LRCORNER);
	mvaddch(ifmux.starty+1,pci.startx+pci.width/2+2,ACS_VLINE);
	mvaddch(ifmux.starty,pci.startx+pci.width/2+2,ACS_VLINE);
	mvaddch(ifmux.starty-1,pci.startx+pci.width/2+2,ACS_URCORNER);
	mvaddch(ifmux.starty-1,pci.startx+pci.width/2+1,ACS_HLINE);
	mvaddch(ifmux.starty-1,pci.startx+pci.width/2,ACS_HLINE);
	mvaddch(ifmux.starty-1,pci.startx+pci.width-3,ACS_HLINE);
	mvaddch(ifmux.starty-1,pci.startx+2,ACS_HLINE);
	mvaddch(ifmux.starty-1,pci.startx+1,ACS_HLINE);
	mvaddch(ifmux.starty-1,pci.startx,ACS_HLINE);
	mvaddch(ifmux.starty-1,pc.startx+pc.width+4,ACS_HLINE);
	mvaddch(ifmux.starty-1,pc.startx+pc.width+3,ACS_HLINE);
	mvaddch(ifmux.starty-1,pc.startx+pc.width+2,ACS_HLINE);
	mvaddch(ifmux.starty-1,pc.startx+pc.width+1,ACS_HLINE);
	mvaddch(ifmux.starty-1,pc.startx+pc.width,ACS_HLINE);
	mvaddch(ifmux.starty-1,pc.startx+pc.width-1,ACS_HLINE);
	mvaddch(ifmux.starty-1,pc.startx+1,ACS_HLINE);
	mvaddch(ifmux.starty-1,pc.startx,ACS_HLINE);
	mvaddch(ifmux.starty-1,pc.startx-1,ACS_HLINE);
	mvaddch(ifmux.starty-1,pc.startx-2,ACS_ULCORNER);
	for (int i = ifmux.starty; i <= pc.starty; i++)
		mvaddch(i,pc.startx-2,ACS_VLINE);
	mvaddch(pc.starty+1,pc.startx-2,ACS_LLCORNER);
	mvaddch(pc.starty+1,pc.startx-1,ACS_HLINE);
	mvaddch(pc.starty+1,pc.startx,ACS_RARROW);
}

void mvm::gui::gui::drawcontrolpaths()
{
}
