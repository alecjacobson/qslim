/************************************************************************

  smfboundary

  Copyright (C) 1998 Michael Garland, All Rights Reserved.
  
  $Id: smfboundary.cxx,v 1.1 1998/10/27 01:24:18 garland Exp $

 ************************************************************************/

#include <stdmix.h>
#include <MxVector.h>

#include "cmdline.h"

static double threshold = 0;

static char *options = "t:h";
static char *usage_string =
"-t <n>		Set proximity threshold\n"
"\n";

static
void process_options(int opt, char *optarg)
{
    switch( opt )
    {
    case 't':  threshold = atof(optarg); break;
    case 'h':
	cerr << endl << usage_string << endl;
	break;
    }
}

static
bool vertex_is_open(MxStdModel *m, uint v)
{
    static MxVertexList star;

    star.reset();
    m->collect_vertex_star(v, star);

    return (star.length() - m->neighbors(v).length()) > 0;
}

static
bool is_nonedge_pair(MxStdModel *m, uint i, uint j)
{
    static MxFaceList edges;

    edges.reset();
    m->collect_edge_neighbors(i, j, edges);
    return edges.length() == 0;
}

void output_boundary_verts(MxStdModel *m, ostream& out)
{
    MxVertexID i,j;

    for(i=0; i<m->vert_count(); i++)
	m->vertex_mark(i, vertex_is_open(m,i));


    for(i = 0; i<m->vert_count(); i++)
    {
	if( !m->vertex_mark(i) ) continue;

	for(j=i+1; j<m->vert_count(); j++)
	{
	    if( !m->vertex_mark(j) ) continue;
	    if( !is_nonedge_pair(m, i, j) ) continue;

	    if( mxv_L2(m->vertex(i), m->vertex(j), 3) < threshold )
		out << "e " << i+1 << " " << j+1 << endl;
	}
    }
}

main(int argc, char *argv[])
{
    MxStdModel *m = process_cmdline(argc, argv, options, process_options);
    if( !m ) return 0;


    threshold *= threshold;

    output_final_model(m);
    output_boundary_verts(m, cout);

    delete m;
    return 0;
}
