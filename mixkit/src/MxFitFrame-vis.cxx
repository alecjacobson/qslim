/************************************************************************

  Frame visualization functions.

  This code requires OpenGL.  It is included here, separately from the
  other MxFitFrame code, so that command line programs do not need to
  link OpenGL libraries.

  Copyright (C) 1998 Michael Garland.  See "COPYING.txt" for details.
  
  $Id: MxFitFrame-vis.cxx,v 1.3 2000/11/27 19:19:19 garland Exp $

 ************************************************************************/

#include "stdmix.h"
#include "MxGL.h"
#include "MxFitFrame.h"

static
void draw_box(const double *min, const double *max)
{
    glBegin(GL_LINE_LOOP);
    glV(min[X],min[Y],min[Z]); glV(min[X],max[Y],min[Z]);
    glV(max[X],max[Y],min[Z]); glV(max[X],min[Y],min[Z]);
    glEnd();

    glBegin(GL_LINE_LOOP);
    glV(min[X],min[Y],max[Z]); glV(min[X],max[Y],max[Z]);
    glV(max[X],max[Y],max[Z]); glV(max[X],min[Y],max[Z]);
    glEnd();

    glBegin(GL_LINES);
    glV(min[X],min[Y],min[Z]); glV(min[X],min[Y],max[Z]);
    glV(min[X],max[Y],min[Z]); glV(min[X],max[Y],max[Z]);
    glV(max[X],max[Y],min[Z]); glV(max[X],max[Y],max[Z]);
    glV(max[X],min[Y],min[Z]); glV(max[X],min[Y],max[Z]);
    glEnd();
}

static
void draw_base_plane(const double *min, const double *max)
{
    glBegin(GL_LINES);
//       glV(0.0f, 0.0f, 0.0f);  glV(0.0f, 0.0f, 0.2f);
//       glV(0.0f, 0.0f, 0.0f);  glV(0.1f, 0.0f, 0.0f);
//       glV(0.0f, 0.0f, 0.0f);  glV(0.0f, 0.1f, 0.0f);
      glV(0.0f, 0.0f, 0.0f);  glVertex2d(min[X], min[Y]);
      glV(0.0f, 0.0f, 0.0f);  glVertex2d(max[X], min[Y]);
      glV(0.0f, 0.0f, 0.0f);  glVertex2d(max[X], max[Y]);
      glV(0.0f, 0.0f, 0.0f);  glVertex2d(min[X], max[Y]);
    glEnd();

    glBegin(GL_LINE_LOOP);
      glVertex2d(min[X], min[Y]);
      glVertex2d(max[X], min[Y]);
      glVertex2d(max[X], max[Y]);
      glVertex2d(min[X], max[Y]);
    glEnd();
}

void mx_draw_fitframe(const MxFitFrame& n, float rgbscale)
{
    glC(0.2*rgbscale, 0.8*rgbscale, 0.2*rgbscale);

    glPushAttrib(GL_LIGHTING_BIT | GL_LINE_BIT | GL_ENABLE_BIT);
    glEnable(GL_LINE_SMOOTH);
    glDisable(GL_LIGHTING);
    glLineWidth(1.2);

    const Vec4 r1(Vec3(n.axis(0)), 0);
    const Vec4 r2(Vec3(n.axis(1)), 0);
    const Vec4 r3(Vec3(n.axis(2)), 0);
    const Vec4 r4(Vec3(n.origin()), 1);
    Mat4 R(r1, r2, r3, r4);

    R = transpose(R);


    glPushMatrix();
    glMultMatrix(R);
      draw_base_plane(n.min(), n.max());
      draw_box(n.min(), n.max());
    glPopMatrix();

//     glBegin(GL_LINES);
//       glC(0.8*rgbscale, 0.8*rgbscale, 0.2*rgbscale);
//       glV3(n.origin());
//       glV(Vec3(n.origin()) + 0.2*Vec3(n.normal()));
//     glEnd();

    glPopAttrib();
}
