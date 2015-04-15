#ifndef GFXWINTOOLS_INCLUDED // -*- C++ -*-
#define GFXWINTOOLS_INCLUDED
#if !defined(__GNUC__)
#  pragma once
#endif

/************************************************************************

  Support code for handling various tasks under Win32

  $Id: wintools.h,v 1.1 2002/03/19 20:46:55 garland Exp $

 ************************************************************************/

#include <windows.h>

extern HGLRC create_glcontext(HDC dc);
extern int set_pixel_format(HDC dc);

// GFXWINTOOLS_INCLUDED
#endif
