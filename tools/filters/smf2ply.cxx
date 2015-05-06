/************************************************************************

  smf2ply

  Copyright (C) 1998 Michael Garland, All Rights Reserved.
  
  $Id: smf2ply.cxx,v 1.2 1998/04/20 16:13:29 garland Exp $

 ************************************************************************/

#include <stdmix.h>
#include "cmdline.h"

static
void output_ply(MxStdModel *m)
{
    cout << "ply" << endl;
    cout << "format ascii 1.0" << endl;
    cout << "comment Generated from SMF model by smf2ply" << endl;

    cout << "element vertex " << m->vert_count() << endl;
    cout << "property float x" << endl;
    cout << "property float y" << endl;
    cout << "property float z" << endl;
    cout << "element face " << m->face_count() << endl;
    cout << "property list uchar int vertex_indices" << endl;
    cout << "end_header" << endl;

    uint i;

    for(i=0; i<m->vert_count(); i++)
	cout << m->vertex(i)[0] << " "
	     << m->vertex(i)[1] << " "
	     << m->vertex(i)[2] << endl;

    for(i=0; i<m->face_count(); i++)
	cout << "3 "
	     << m->face(i)[0] << " "
	     << m->face(i)[1] << " "
	     << m->face(i)[2] << endl;
}

int main(int argc, char *argv[])
{
    MxStdModel *m = process_cmdline(argc, argv);
    if( !m ) return 0;

    output_ply(m);
    delete m;
    return 0;
}
