/************************************************************************

  Handy 2D geometrical primitives

  Copyright (C) 1999 Michael Garland.  See "COPYING.txt" for details.
  
  $Id: MxGeom2D.cxx,v 1.1 1999/05/12 17:58:13 garland Exp $

 ************************************************************************/

#include "stdmix.h"
#include "MxMath.h"
#include "MxGeom2D.h"
#include "MxVector.h"

// Returns TWICE the signed area of triangle ABC
static
inline float triArea(const float *a, const float *b, const float *c)
{
    return (b[X] - a[X])*(c[Y] - a[Y]) - (b[Y] - a[Y])*(c[X] - a[X]);
}

// This computes the signed area of the oriented triangle ABC.
// The area is positive when ABC is oriented counterclockwise.
//
float mx2d_triangle_area(const float *a, const float *b, const float *c)
{
    return 0.5*triArea(a,b,c);
}

bool mx2d_is_ccw(const float *a, const float *b, const float *c)
{
    return triArea(a, b, c) > 0;
}

// This returns true if the d lies within the circle defined by a,b,c.
// See Delaunay triangulator by Lischinski in Graphics Gems IV and
// Guibas & Stolfi paper in ACM Trans. on Graphics 1985.
//
bool mx2d_in_circle(const float *a, const float *b,
		    const float *c, const float *d)
{
    return (a[0]*a[0] + a[1]*a[1]) * triArea(b, c, d) -
           (b[0]*b[0] + b[1]*b[1]) * triArea(a, c, d) +
           (c[0]*c[0] + c[1]*c[1]) * triArea(a, b, d) -
           (d[0]*d[0] + d[1]*d[1]) * triArea(a, b, c) > FEQ_EPS;
}

float *mx2d_segment_normal(float *n, const float *v1, const float *v2)
{
    n[X] = v1[Y] - v2[Y];
    n[Y] = v2[X] - v1[X];
    mxv_unitize(n, 2);
    return n;
}

float *mx2d_segment_line(float *p, const float *v1, const float *v2)
{
    mx2d_segment_normal(p, v1, v2);
    p[2] = -p[X]*v1[X] -p[Y]*v1[Y];
    return p;
}
