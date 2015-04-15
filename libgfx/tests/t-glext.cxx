/************************************************************************

  Test the availability of various OpenGL extensions

  by Michael Garland, 2001.
  
  $Id: t-glext.cxx,v 1.1 2001/10/16 14:23:14 garland Exp $

 ************************************************************************/

#include <gfx/gui.h>
#include <gfx/glext.h>
#include <string>
#include <fstream>

using namespace std;

class GUI : public MxGUI
{
public:

    virtual void setup_for_drawing();
};

GUI gui;

static void dump_string(ostream &out, const string& str)
{
    const char *ws = " \t\n\r";
    string::size_type start, end;

    start = 0;
    end = str.find_first_of(ws, start);

    while( end!=string::npos )
    {
	out << "    " << str.substr(start, end-start) << endl;
	start = str.find_first_not_of(ws, end);
	end = str.find_first_of(ws, start);
    }
}

void GUI::setup_for_drawing()
{
    ofstream log("glext.txt");

    string gl_extensions = (char *)glGetString(GL_EXTENSIONS);
    
    log << "OpenGL extensions" << endl
	<< "-----------------" << endl;
    dump_string(log, gl_extensions);
    log << endl << endl;


#ifdef HAVE_GL_WGLEXT_H
    PFNWGLGETEXTENSIONSSTRINGARBPROC wglGetExtensionsStringARB =
	(PFNWGLGETEXTENSIONSSTRINGARBPROC)
	wglGetProcAddress("wglGetExtensionsStringARB");

    if( !wglGetExtensionsStringARB )
    {
	log << "Couldn't find wglGetExtensionsStringARB." << endl;
	exit(-1);
    }
    else
    {
	string wgl_extensions = wglGetExtensionsStringARB(wglGetCurrentDC());

	log << "WGL extensions" << endl
	    << "--------------" << endl;
	dump_string(log, wgl_extensions);
    }
#endif

    exit(0);
}

main(int argc, char **argv)
{
    gui.initialize(argc, argv);
    return gui.run();
}
