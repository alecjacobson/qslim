/************************************************************************

  Support code for handling various tasks under Win32

  $Id: wintools.cxx,v 1.1 2002/03/19 20:47:22 garland Exp $

 ************************************************************************/

#include <gfx/wintools.h>

HGLRC create_glcontext(HDC dc)
{
    HGLRC context = wglCreateContext(dc);
    if( context )
    {
	if( !wglMakeCurrent(dc, context) )
	{
	    // Destroy context if it fails to bind
	    wglDeleteContext(context);
	    context = NULL;
	}
    }

    return context;
}

int set_pixel_format(HDC dc)
{
    PIXELFORMATDESCRIPTOR pixelDesc;

    //
    // These are the important fields of the PFD
    //
    pixelDesc.nSize = sizeof(PIXELFORMATDESCRIPTOR);
    pixelDesc.nVersion = 1;

    pixelDesc.dwFlags =
	PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL |
	PFD_DOUBLEBUFFER | PFD_STEREO_DONTCARE;  
    pixelDesc.iPixelType = PFD_TYPE_RGBA;
    pixelDesc.cColorBits = 24;
    pixelDesc.iLayerType = PFD_MAIN_PLANE;

    //
    // According to the docs, these can be/are ignored.
    //
    pixelDesc.cRedBits = 8;
    pixelDesc.cRedShift = 16;
    pixelDesc.cGreenBits = 8;
    pixelDesc.cGreenShift = 8;
    pixelDesc.cBlueBits = 8;
    pixelDesc.cBlueShift = 0;
    pixelDesc.cAlphaBits = 0;
    pixelDesc.cAlphaShift = 0;
    pixelDesc.cAccumBits = 0;	
    pixelDesc.cAccumRedBits = 0;
    pixelDesc.cAccumGreenBits = 0;
    pixelDesc.cAccumBlueBits = 0;
    pixelDesc.cAccumAlphaBits = 0;
    pixelDesc.cDepthBits = 32;
    pixelDesc.cStencilBits = 0;
    pixelDesc.cAuxBuffers = 0;
    pixelDesc.bReserved = 0;
    pixelDesc.dwLayerMask = 0;
    pixelDesc.dwVisibleMask = 0;
    pixelDesc.dwDamageMask = 0;


    int pixel_format = ChoosePixelFormat(dc, &pixelDesc);
    if( !pixel_format )
    {
	// Try and guess a decent default pixel format
	pixel_format = 1;
	if( !DescribePixelFormat(dc, pixel_format,
				 sizeof(PIXELFORMATDESCRIPTOR), &pixelDesc) )
	    return NULL;
    }

    if( !SetPixelFormat(dc, pixel_format, &pixelDesc) )
	return NULL;

    return pixel_format;
}
