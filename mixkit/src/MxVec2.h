#ifndef MXVEC2_INCLUDED // -*- C++ -*-
#define MXVEC2_INCLUDED
#if !defined(__GNUC__)
#  pragma once
#endif

/************************************************************************

  2D Vector class

  Copyright (C) 1998 Michael Garland.  See "COPYING.txt" for details.
  
  $Id: MxVec2.h,v 1.11 2000/11/20 20:36:38 garland Exp $

 ************************************************************************/

#include <gfx/vec2.h>

#ifdef MXGL_INCLUDED
inline void glV(const Vec2& v) { glVertex2d(v[X], v[Y]); }
#endif

// MXVEC2_INCLUDED
#endif
