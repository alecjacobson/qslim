# QSlim ported to compile on Mac OS X

This is a port of the wonderful
[QSlim](http://www.cs.cmu.edu/~./garland/quadrics/qslim.html) software by
Michael Garland. I've [patched](http://www.alecjacobson.com/weblog/?p=3244) it
to compile on mac os x.

> Original README.txt

------------------------------------------------------------------------
		    SlimKit Surface Modeling Tools
			     Version 1.1
			     July 4, 2004

		 Michael Garland <garland@cs.uiuc.edu>


 Copyright (C) 1998-2002 Michael Garland.  See "COPYING.txt" for details.


 For the latest version and up-to-date information, please visit
 http://www.uiuc.edu/~garland/software/qslim.html


 Michael Garland
 Department of Computer Science
 University of Illinois at Urbana-Champaign
 201 North Goodwin Avenue
 Urbana, IL 61801

------------------------------------------------------------------------

## OVERVIEW

This is the SlimKit collection of surface modeling tools.  Most of the
programs in this collection simply provide an interface to the
underlying functionality of the MixKit library (see mixkit/README.txt).

The primary component of this package is the QSlim 2.1 surface
simplification tool located in the tools/qslim directory.  Please
consult tools/qslim/QSlim.txt for further information.  There are also
several useful programs in tools/filters/ for manipulating SMF model
files.

New in this release is the QCluster software package in tools/cluster.


## BUILDING & INSTALLATION

To build on a Unix machine:

```bash
cd libgfx
./configure
cd src; make
cd ../../mixkit
./configure
cd src; make
cd ../../tools/qslim
make all
```

I have tested this process on both Linux (Debian) and Mac OS X (10.3)
machines.  Compilation on other Unix platforms should probably work as
well.

I no longer use Windows on a regular basis, and have not updated the
Windows build files.  The Unix directions given above should work
correctly with Cygwin.  Some slightly out-of-date project files for
compiling under MS Visual C++ 6.0 can be found in SlimKit workspace in
the "win32" directory.  You can probably get them working without too
much effort.

Finally:

	 o  Read tools/qslim/QSlim.txt



## FUTURE PLANS

None.  This software package has changed relatively little since its
initial public release in March 1999.  The only substantial changes were
switching to an FLTK-based GUI and repackaging some of the common code
in the new libgfx library.  I ceased active development on the
simplification-related MixKit code several years ago.  At this point, I
do not have plans for any further releases of this software.
