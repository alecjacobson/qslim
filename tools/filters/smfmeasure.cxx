/************************************************************************

  smfmeasure

  This filter makes various measurements on the model, and outputs
  the results.  It does *not* output a new model, only the model
  measurements.

  Copyright (C) 1998 Michael Garland, All Rights Reserved.
  
  $Id: smfmeasure.cxx,v 1.3 1998/06/18 12:11:44 garland Exp $

 ************************************************************************/

#include <stdmix.h>
#include <MxVector.h>
#include <MxGeom3D.h>
#include "cmdline.h"


static uint edge_count = 0;
static double min_area = HUGE;
static double max_area = 0;
static double total_area = 0;
static double min_edge = HUGE;
static double max_edge = 0;
static MxBounds bounds;

static
void measure_model(MxStdModel *m)
{
    uint i, j;

    // Compute [min,max] face areas
    for(i=0; i<m->face_count(); i++)
    {
	double a = m->compute_face_area(i);
	if( a<min_area ) min_area = a;
	if( a>max_area ) max_area = a;
	total_area += a;
    }

    // Compute [min,max] edge length
    MxVertexList star;

    for(i=0; i<m->vert_count(); i++)
    {
	star.reset();
	m->collect_vertex_star(i, star);

	for(j=0; j<star.length(); j++)
	    if( i < star(j) )
	    {
		edge_count++;
		double e2 = mxv_L2(m->vertex(i), m->vertex(star[j]), 3);
		if( e2<min_edge ) min_edge = e2;
		if( e2>max_edge ) max_edge = e2;
	    }
    }
    min_edge = sqrt(min_edge);
    max_edge = sqrt(max_edge);

    // Compute bounding box
    for(i=0; i<m->vert_count(); i++)
	bounds.add_point(m->vertex(i));
    bounds.complete();
}

static
void report_measurements(MxStdModel *m)
{
    cout << endl;
    cout << "vertices = " << m->vert_count() << endl;
    cout << "faces    = " << m->face_count()
	 << "\t\t["
	 << (float)m->face_count() / (float)m->vert_count()
	 << "v]" << endl;
    cout << "edges    = " << edge_count
	 << "\t\t["
	 << (float)edge_count / (float)m->vert_count()
	 << "v]" << endl;

    cout << endl;
    cout << "BB min = " << bounds.min << endl;
    cout << "BB max = " << bounds.max << endl;
    cout << "BB ctr = " << (bounds.max+bounds.min)/2 << endl;
    cout << "BS ctr = " << bounds.center << endl;
    cout << "BS rad = " << bounds.radius << endl;

    cout << endl;
    cout << "min area = " << min_area << endl;
    cout << "max area = " << max_area << endl;
    cout << "tot area = " << total_area << endl;
    cout << "min edge = " << min_edge << endl;
    cout << "max edge = " << max_edge << endl;
}

int main(int argc, char *argv[])
{
    MxStdModel *m = process_cmdline(argc, argv);
    if( !m ) return 0;

    measure_model(m);
    report_measurements(m);

    delete m;
    return 0;
}
