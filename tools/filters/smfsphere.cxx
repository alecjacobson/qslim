/************************************************************************

  smfsphere

  The idea of this filter is to generate spheres.  First, you give it a
  base model.  Something like a cube or tetrahedron would be a good
  example.  The edges of the model are iteratively split to approximate
  the sphere.

  Copyright (C) 1998 Michael Garland, All Rights Reserved.
  
  $Id: smfsphere.cxx,v 1.2 1998/10/27 01:21:43 garland Exp $

 ************************************************************************/

#include <stdmix.h>

#include <MxSMF.h>
#include <MxEdgeFilter.h>
#include <MxVector.h>

#include "cmdline.h"

static float max_sqrlen = HUGE;
static uint edge_target = 0;
static bool will_skew = false;

static char *options = "t:l:kh";
static char *usage_string =
"-l <n>		Set the maximum allowable edge length.\n"
"-t <n>		Set the desired edge target.\n"
"-k		Skew the triangle density towards the poles.\n"
"\n";

static
void process_options(int opt, char *optarg)
{
    switch( opt )
    {
    case 'l':  max_sqrlen = atof(optarg); max_sqrlen*=max_sqrlen; break;
    case 't':  edge_target = atoi(optarg); break;
    case 'k':  will_skew = true; break;
    case 'h':
	cerr << endl << usage_string << endl; exit(0); break;    
    }
}

class SphereFilter : public MxEdgeFilter
{
public:
    SphereFilter(MxStdModel *m) : MxEdgeFilter(m) { }

    void filter_target_edge(MxRankedEdge *);
    float compute_edge_rank(MxRankedEdge *);
};

float SphereFilter::compute_edge_rank(MxRankedEdge *edge)
{
    float vmid[3];
    const MxVertex& v1 = m->vertex(edge->v1);
    const MxVertex& v2 = m->vertex(edge->v2);

    // Compute midpoint of edge
    mxv_scale(mxv_add(vmid, v1, v2, 3), 0.5, 3);

    if( will_skew )
	return mxv_L2(v1, v2, 3) + vmid[Z] * vmid[Z];
    else
	return mxv_L2(v1, v2, 3);
}

void SphereFilter::filter_target_edge(MxRankedEdge *edge)
{
    uint vnew = split_edge(edge);
    mxv_unitize(m->vertex(vnew), 3);
}

static
MxStdModel *create_sphere_base()
{
    static float v[8][3] = {
	{0, 0, 0}, {1, 0, 0}, {0, 1, 0}, {1, 1, 0},
	{0, 0, 1}, {1, 0, 1}, {0, 1, 1}, {1, 1, 1},
    };

    static unsigned int f[12][3] = {
	    {0, 3, 1}, {0, 2, 3}, {4, 5, 7}, {4, 7, 6},
	    {0, 1, 5}, {0, 5, 4}, {1, 3, 7}, {1, 7, 5},
	    {3, 2, 6}, {3, 6, 7}, {2, 0, 4}, {2, 4, 6},
    };

    MxStdModel *m = new MxStdModel(8, 12);
    for(uint i=0; i<8; i++)  m->add_vertex(v[i][0], v[i][1], v[i][2]);
    for(uint j=0; j<12; j++) m->add_face(f[j][0], f[j][1], f[j][2]);

    return m;
}

main(int argc, char *argv[])
{
    process_cmdline_only(argc, argv, options, process_options);
    MxStdModel *m = create_sphere_base();

    uint i;
    float ctr[3];

    // Compute the center of the input model and translate the geometry
    // to be centered around the origin.
    //
    mxv_set(ctr, 0.0f, 3);
    for(i=0; i<m->vert_count(); i++) mxv_addinto(ctr, m->vertex(i), 3);
    mxv_invscale(ctr, (float)m->vert_count(), 3);
    for(i=0; i<m->vert_count(); i++) mxv_subfrom(m->vertex(i), ctr, 3);

    // Map the geometry onto the unit sphere
    //
    for(i=0; i<m->vert_count(); i++)
	mxv_unitize(m->vertex(i), 3);

    SphereFilter filter(m);
    filter.initialize();
    if( edge_target > 0 )
	filter.filter(edge_target);
    else
	filter.filter_above_rank(max_sqrlen);

    output_final_model(m, true);
    delete m;
    return 0;
}
