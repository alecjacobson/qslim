/************************************************************************

  smf2iv

  This filter converts SMF files to OpenInventor files.  Currently, only
  the geometry is emitted.  Any surface attributes are lost.

  Copyright (C) 1998 Michael Garland, All Rights Reserved.
  
  $Id: smf2iv.cxx,v 1.1 1998/11/06 19:42:44 garland Exp $

 ************************************************************************/

#include <stdmix.h>
#include "cmdline.h"

static
void output_iv(MxStdModel *m)
{
    uint i;

    cout << "#Inventor V2.0 ascii" << endl;

    cout << "Separator {" << endl
	 << "Coordinate3 {" << endl
	 << "point [" << endl;

    for(i=0; i<m->vert_count(); i++)
	cout << "   " << m->vertex(i)[0] << " "
	     << m->vertex(i)[1] << " "
	     << m->vertex(i)[2] << "," << endl;

    cout << "]"<< endl << "}" << endl;
    cout << "IndexedFaceSet {" << endl
	 << "coordIndex [" << endl;

    for(i=0; i<m->face_count(); i++)
	cout << "   "
	     << m->face(i)[0] << ", "
	     << m->face(i)[1] << ", "
	     << m->face(i)[2] << ", "
	     << "-1," << endl;

    cout << "]}}" << endl;
}

main(int argc, char *argv[])
{
    MxStdModel *m = process_cmdline(argc, argv);
    if( !m ) return 0;

    output_iv(m);
    delete m;
    return 0;
}
