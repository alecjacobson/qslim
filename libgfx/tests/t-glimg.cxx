/************************************************************************

  This is a very simplistic image viewer.  It uses libgfx routines to
  read a set of image files specified on the command line.  These images
  are then displayed in a window using OpenGL image operations.

  by Michael Garland, 2000.
  
  $Id: t-glimg.cxx,v 1.4 2003/02/03 20:59:01 garland Exp $

 ************************************************************************/

#include <gfx/gfx.h>
#include <gfx/gui.h>
#include <gfx/raster.h>

#include <string>
#include <vector>
#include <FL/filename.H>

class GUI : public MxGUI
{
public:
    std::vector<ByteRaster *> images;
    std::vector<std::string> image_names;
    int current_image;

    virtual ~GUI();

    virtual void update_animation();
    virtual void cmdline_file(const char *file);
    virtual void setup_for_drawing();
    virtual void draw_contents();

    void set_image(int i);
};

GUI gui;

GUI::~GUI()
{
    for(int i=0; i<images.size(); i++)
	if( images[i] )
	    delete images[i];
}

static void cb_image(Fl_Widget *, long i)
	{ gui.set_image(i); gui.canvas->redraw(); }

void GUI::set_image(int i)
{
    current_image = i;

    if(current_image<0 || current_image>=images.size()) return;
    ByteRaster *img = images[current_image];

    int width = img->width();
    int height = img->height();

    gui.status(image_names[current_image].c_str());

    if( width!=canvas->w() || height!=canvas->h() )
    {
	unlock_size();
	resize_canvas(width, height);
	lock_size();
    }
}

void GUI::cmdline_file(const char *namestring)
{
    if(!namestring) return;	// Don't support reading from stdin

    static std::string img_menu("&Images/");
    std::string filename(fl_filename_name(namestring)); // Strip directories

    ByteRaster *img = read_image(namestring);
    if( img )
    {
	int id = images.size();
	images.push_back(img);
	image_names.push_back(namestring);

	int key = id<9 ? FL_CTRL+'1'+id : 0;


	gui.menu_bar->add((img_menu+filename).c_str(), key,
			  (Fl_Callback *)cb_image, (void *)id, FL_MENU_RADIO);
    }
}

void GUI::update_animation()
{
    set_image((current_image+1) % images.size());
}

void GUI::setup_for_drawing()
{
    glClearColor(0.9f, 0.0f, 0.0f, 0.0f);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glPixelZoom(1.0f, -1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void draw_image(const ByteRaster *img)
{
    GLenum format;
    if(img->channels()==1)       format = GL_LUMINANCE;
    else if(img->channels()==3)  format = GL_RGB;
    else if(img->channels()==4)  format = GL_RGBA;
    else                         return; // Don't draw unsupported formats

    glPushAttrib(GL_PIXEL_MODE_BIT);
      glRasterPos2f(0, img->height());
      glDrawPixels(img->width(), img->height(),
		   format, GL_UNSIGNED_BYTE, img->head());
    glPopAttrib();

}

void GUI::draw_contents()
{
    glClear(GL_COLOR_BUFFER_BIT);

    if(current_image<0 || current_image>=images.size()) return;
    ByteRaster *img = images[current_image];

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, img->width(), 0, img->height());

    draw_image(img);
}

main(int argc, char **argv)
{
    gui.initialize(argc, argv);
    if(gui.images.size() == 0)  return 0; // Exit if no images read

    gui.title("OpenGL Image Viewer");

    gui.default_fps = 1.0f;
    gui.set_image(0);

    return gui.run();
}
