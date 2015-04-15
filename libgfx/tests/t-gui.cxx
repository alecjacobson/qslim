/************************************************************************

  This is a simple program which demonstrates the use of the MxGUI
  minimalist GUI framework.  The application presents a window with a
  rotating square that can be moved around with the mouse.

  by Michael Garland, 1999.
  
  $Id: t-gui.cxx,v 1.4 2002/02/06 20:19:20 garland Exp $

 ************************************************************************/

#include <gfx/gfx.h>
#include <gfx/gui.h>
#include <gfx/gltools.h>

class GUI : public MxGUI
{
public:
    float angle, opt_theta, center[2];
    bool dragging;

public:
    virtual void setup_for_drawing();
    virtual void draw_contents();
    virtual void update_animation();

    virtual bool mouse_down(int *where, int which);
    virtual bool mouse_up(int *where, int which);
    virtual bool mouse_drag(int *where, int *last, int which);
};

GUI gui;

void GUI::setup_for_drawing()
{
    glClearColor(0.65f, 0.65f, 0.65f, 0.0f);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);
}

void GUI::draw_contents()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_LINES);
      glVertex2f(-1.0, 0.0);
      glVertex2f(1.0, 0.0);
      glVertex2f(0.0, -1.0);
      glVertex2f(0.0, 1.0);
    glEnd();
    
    glTranslatef(center[0], center[1], 0);
    glRotatef(angle, 0, 0, 1);

    glEnable(GL_BLEND);
    glColor4d(0.8, 0.15, 0.15, 0.85);
    glBegin(dragging?GL_LINE_LOOP:GL_POLYGON);
    glBegin(GL_POLYGON);
      glVertex2f(-0.5, -0.5);
      glVertex2f(-0.5, 0.5);
      glVertex2f(0.5, 0.5);
      glVertex2f(0.5, -0.5);
    glEnd();
    glDisable(GL_BLEND);

    glPopMatrix();
}

void GUI::update_animation()
{
    angle += opt_theta;
}

static
bool center_on_click(float *ctr, int *where)
{
    double world[3];

    unproject_pixel(where, world);
    ctr[0] = (float)world[0];
    ctr[1] = (float)world[1];

    return true;
}

bool GUI::mouse_down(int *where, int which)
{
    status("Clicked mouse %d at %d,%d", which, where[0], where[1]);
    if( which==1 )
    {
	dragging = true;
	return center_on_click(center, where);
    }
    else return false;
}

bool GUI::mouse_up(int *where, int which)
{
    status("Released mouse %d at %d,%d", which, where[0], where[1]);
    dragging = false;
    return (which==1);
}

bool GUI::mouse_drag(int *where, int *last, int which)
{
    if( which==1 )
	return center_on_click(center, where);
    else
	return false;
}

main(int argc, char **argv)
{
    gui.opt_theta = 10.0f;
    gui.angle = 0.0f;
    gui.dragging = false;
    gui.center[0] = gui.center[1] = 0.0f;

    gui.initialize(argc, argv);
    gui.toplevel->label("Simple GUI Example");
    return gui.run();
}
