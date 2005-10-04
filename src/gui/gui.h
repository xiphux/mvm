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
 */
#ifndef _MVM_GUI_H
#define _MVM_GUI_H

#include "base.h"

namespace mvm
{
	namespace gui
	{

		class gui
		{
		public:
			gui(unsigned int sy, unsigned int sx, unsigned int my, unsigned int mx);
			virtual ~gui();
			void keypressed(char ch);
			void draw();
			void resize(unsigned int my, unsigned int mx);
			bool complete;
		private:
			WINDOW *dpwin;
			unsigned int x0,y0,x1,y1;
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
			struct win_s ifidlatch;
			struct win_s im;
			struct win_s pc;
			struct win_s bbox;
			struct win_s pci;
			struct win_s ifmux;
		};

	}
}

#endif /* _MVM_GUI_H */
