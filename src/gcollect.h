/*
 *  gcollect.h
 *  Header file to enable/disable garbage collection
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
#ifndef _MVM_GCOLLECT_H
#define _MVM_GCOLLECT_H

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#ifdef USE_GCOLLECT
#include "gc.h"
inline void *operator new(size_t n) throw (std::bad_alloc) {return GC_malloc(n);}
inline void operator delete(void *) throw () {}
inline void *operator new[](size_t n) throw (std::bad_alloc) {return GC_malloc(n);}
inline void operator delete[](void *) throw () {}
#endif

#endif /* _MVM_GCOLLECT_H */
