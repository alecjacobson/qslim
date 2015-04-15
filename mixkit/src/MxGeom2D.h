#ifndef MXGEOM2D_INCLUDED // -*- C++ -*-
#define MXGEOM2D_INCLUDED
#if !defined(__GNUC__)
#  pragma once
#endif

/************************************************************************

  Handy 2D geometrical primitives

  Copyright (C) 1999 Michael Garland.  See "COPYING.txt" for details.
  
  $Id: MxGeom2D.h,v 1.1 1999/05/12 17:58:12 garland Exp $

 ************************************************************************/

extern float *mx2d_segment_normal(float *n, const float *v1, const float *v2);
extern float *mx2d_segment_line(float *p, const float *v1, const float *v2);

extern float mx2d_triangle_area(const float *, const float *,const float *);
extern bool mx2d_is_ccw(const float *a, const float *b, const float *c);

inline bool mx2d_is_rightof(const float *x, const float *a, const float *b)
	{ return mx2d_is_ccw(x, b, a); }
inline bool mx2d_is_leftof(const float *x, const float *a, const float *b)
	{ return mx2d_is_ccw(x, a, b); }

extern bool mx2d_in_circle(const float *, const float *,
			   const float *, const float *);


// MXGEOM2D_INCLUDED
#endif
