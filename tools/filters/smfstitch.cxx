/************************************************************************

  smfstitch

  This program will attempt to stitch together vertices which coincide
  in space but which are topologically distinct.  It uses a heuristic
  based on the minimum edge length.

  Copyright (C) 1998 Michael Garland, All Rights Reserved.
  
  $Id: smfstitch.cxx,v 1.8 2000/11/20 20:58:59 garland Exp $

 ************************************************************************/

#include <stdmix.h>
#include <MxVector.h>
#include "cmdline.h"

static double min_edge_length = HUGE;
static double max_edge_length = -HUGE;
static double avg_edge_length = 0.0;
static uint edge_count = 0;
static uint stitch_count = 0;

static double threshold = -1;

static char *options = "xt:ch";
static char *usage_string =
"-t <n>		Set stitching threshold [default=0.75 * min. edge length]\n"
"\n";

static
void process_options(int opt, char *optarg)
{
    switch( opt )
    {
    case 't':  threshold = atof(optarg); break;
    case 'h':
	cerr << endl;
	cerr << "smfstitch  Version 1.0 "
	     << "[Built " << __DATE__ << "]." << endl
	     << "Copyright (C) 1998 Michael Garland, All Rights Reserved."
	     << endl;
	cerr << endl << usage_string << endl; exit(0); break;
    }
}

static
void measure_edges(MxStdModel *m)
{
    //
    // Examine edge lengths in the model
    MxVertexList star;
    for(MxVertexID i=0; i<m->vert_count(); i++)
    {
	star.reset();
	m->collect_vertex_star(i, star);

	for(uint j=0; j<star.length(); j++)
	    if( i<star(j) )
	    {
		float *v1 = m->vertex(i);
		float *v2 = m->vertex(star(j));

		float len = sqrt(mxv_L2(v1, v2, 3));

		if( len < min_edge_length ) min_edge_length = len;
		if( len > max_edge_length ) max_edge_length = len;

		avg_edge_length += len;
		edge_count++;
	    }
    }

    avg_edge_length /= (double)edge_count;
}

static
void exhaustive_search(MxStdModel *m)
{
    MxPairContraction conx;
    for(MxVertexID i=0; i<m->vert_count(); i++)
	if( m->vertex_is_valid(i) )
	{
	    for(MxVertexID j=i+1; j<m->vert_count(); j++)
		if( m->vertex_is_valid(j) )
		{
		    float *v1 = m->vertex(i);
		    float *v2 = m->vertex(j);

		    float d2 = mxv_L2(v1, v2, 3);
		    if( d2 < threshold )
		    {
			m->contract(i, j, m->vertex(i), &conx);
			stitch_count++;
		    }
		}
	}
}

int main(int argc, char *argv[])
{
    MxStdModel *m = process_cmdline(argc, argv, options, process_options);
    if( !m ) return 0;

    if( threshold < 0 )
    {
	measure_edges(m);

	cerr << "Measured edges:" << endl;
	cerr << "   min = " << min_edge_length << endl;
	cerr << "   max = " << max_edge_length << endl;
	cerr << "   avg = " << avg_edge_length << endl;

        threshold = min_edge_length * 0.75;
    }

    cerr << "Target threshold = " << threshold << endl;
    threshold *= threshold;	// Will compare with squared edge lengths

    double stitch_time;

    TIMING(stitch_time, exhaustive_search(m));

    cerr << "Stitched " << stitch_count
	 << (stitch_count>1 ? " pairs":" pair")
	 << " together in "
	 << stitch_time << " sec" << endl;

    output_final_model(m, true);
    delete m;
    return 0;
}
