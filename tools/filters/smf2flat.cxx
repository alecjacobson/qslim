/************************************************************************

  smf2flat

  A conversion filter which outputs models in a FLAT SMF format:

     (1) Only 'v' and 'f' commands are allowed
     (2) The first line of the file looks like:
             #FLAT <nvert> <nface>

  This restricted form of SMF is much easier to parse.  It's intended for
  use in systems where you want to hack in support for SMF tools, but don't
  want to support the full format.

  Copyright (C) 1998 Michael Garland, All Rights Reserved.
  
  $Id: smf2flat.cxx,v 1.1 1999/03/24 15:20:21 garland Exp $

 ************************************************************************/

#include <stdmix.h>
#include "cmdline.h"

static
void output_flat(MxStdModel *m)
{
    cout << "#FLAT " << m->vert_count() <<  " " << m->face_count() << endl;

    for(uint i=0; i<m->vert_count(); i++)
	cout << m->vertex(i) << endl;
    for(uint j=0; j<m->face_count(); j++)
	cout << m->face(j) << endl;
}

int main(int argc, char *argv[])
{
    MxStdModel *m = process_cmdline(argc, argv);
    if( !m ) return 0;

    output_flat(m);
    delete m;
    return 0;
}
