/************************************************************************

  PropVis

  $Id: propvis.cxx,v 1.2.6.1 2002/01/31 18:36:27 garland Exp $

 ************************************************************************/

#include <stdmix.h>
#include <mixio.h>

#include <MxStdGUI.h>
#include <MxPropSlim.h>

class GUI : public MxStdGUI
{
public:
    MxPropSlim *slim;

    GUI() { slim=NULL; }

    virtual bool key_press(int key);
    virtual void draw_custom_contents();
};

GUI gui;

bool GUI::key_press(int c)
{
    switch( c )
    {
    case 'g':  slim->decimate(slim->valid_faces - 100); break;
    case 'G':  slim->decimate(slim->valid_faces - 1000); break;
    case 'h':  slim->decimate(1000); break;

    default: return false;
    }

    canvas->redraw();
    return true;
}

void GUI::draw_custom_contents()
{
    MxStdModel *m = model();

    status("%uv : %uf",
	    slim?slim->valid_verts:m->vert_count(),
	    slim?slim->valid_faces:m->face_count());
}

main(int argc, char **argv)
{
    gui.initialize(argc, argv);

    MxStdModel *m = gui.model();

    cerr << "+ Initializing decimator ...";
    cerr.flush();
    gui.slim = new MxPropSlim(m);
    gui.slim->boundary_weight = 1000;
    gui.slim->initialize();
    cerr << " done" << endl;
    cerr << "+ Quadric dimension: " << gui.slim->dim() << endl;

    return gui.run();
}

