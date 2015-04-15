/************************************************************************

  smf2ldmesh

  Copyright (C) 1998 Michael Garland, All Rights Reserved.
  
  $Id: smf2ldmesh.cxx,v 1.2 1998/04/20 16:13:28 garland Exp $

 ************************************************************************/

#include <stdmix.h>
#include "cmdline.h"

static
void output_ldmesh(MxStdModel *m, ostream& out)
{
    out << "LASER DESIGN MESH FILE" << endl;
    out << "VERTICES      " << m->vert_count() << endl;
    out << "POLYGONS      " << m->face_count() << endl;
    out << "MIN -1000000.000000 -1000000.000000 -1000000.000000" << endl;
    out << "MAX  1000000.000000  1000000.000000  1000000.000000" << endl;

    uint i;

    out.unsetf(ios::scientific);
    out.setf(ios::fixed);
    out.precision(6);

    for(i=0; i<m->vert_count(); i++)
    {
	float *v = m->vertex(i);
	out << "X" << v[X] << "Y" << v[Y] << "Z" << v[Z] << endl;
    }

    for(i=0; i<m->face_count(); i++)
    {
	MxFace& f = m->face(i);
	out << f[0] << " " << f[1] << " " << f[2] << endl;
    }
}

main(int argc, char *argv[])
{
    MxStdModel *m = process_cmdline(argc, argv);
    if( !m ) return 1;

    output_ldmesh(m, cout);
    delete m;
    return 0;
}
