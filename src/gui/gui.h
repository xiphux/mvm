/*
 *  gui.h
 *  GUI class definition
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
 *
 *  $Id: gui.h 210 2005-10-15 04:18:35Z xiphux $
 */
#ifndef _MVM_GUI_H
#define _MVM_GUI_H

#include "base.h"
#include "gcollect.h"

namespace mvm
{
	namespace gui
	{

		class gui
		{
		public:
			gui(const int sy, const int sx, const int my, const int mx);
			virtual ~gui();
			void keypressed(int ch);
			void draw();
			void resize(const int my, const int mx);
			void refresh();
			bool complete;
			bool automate;
		private:
			WINDOW *dpwin;
			int x0,y0,x1,y1;
			struct win_border_s {
				chtype ls;
				chtype rs;
				chtype ts;
				chtype bs;
				chtype tl;
				chtype tr;
				chtype bl;
				chtype br;
			};
			struct win_s {
				int startx,starty;
				int width,height;
				struct win_border_s border;
			};
			void drawprimitive(struct win_s *w, bool border = true);
			void drawcomponents();
			void drawdatapaths();
			void drawcontrolpaths();
			void drawbackground();
			struct win_s bgbox;
			struct win_s ifidlatch;
			struct win_s idexlatch;
			struct win_s im;
			struct win_s pc;
			struct win_s pci;
			struct win_s ifmux;
			struct win_s ifand;
			struct win_s hdu;
			struct win_s cu;
			struct win_s rm;
			struct win_s ideq;
			struct win_s se;
			struct win_s exmux6;
			struct win_s exmux5;
			struct win_s exmux4;
			struct win_s exmux3;
			struct win_s exmux2;
			struct win_s exmux1;
			struct win_s acu;
			struct win_s alu;
			struct win_s dm;
			struct win_s fwd;
			struct win_s memwblatch;
			struct win_s wbmux;
			struct win_s idmux;
			struct win_s idor;
		};

	}
}

#endif /* _MVM_GUI_H */
