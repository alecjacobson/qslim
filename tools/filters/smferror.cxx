/************************************************************************

  smferror

  This filter measures the error between two models.

  Copyright (C) 1998 Michael Garland, All Rights Reserved.
  
  $Id: smferror.cxx,v 1.3 1998/11/17 22:05:43 garland Exp $

 ************************************************************************/

#include <stdmix.h>

#include <MxSMF.h>
#include <MxGeom3D.h>
#include <MxVector.h>

#include "cmdline.h"

static double err_sample_count = 0;
static double err_sum = 0;
static double err_max = 0;

static uint sample_count = 0;

static char *options = "s:h";
static char *usage_string =
"-s <n>		Make <n> additional random samples on each face.\n"
"\n";

static
void process_options(int opt, char *optarg)
{
    switch( opt )
    {
    case 's':  sample_count = atoi(optarg); break;
    case 'h':
	cerr << endl << usage_string << endl; exit(0); break;
    }
}

static
void random_barycentric(float *v)
{
    float a = 1 - sqrt(1-random1());
    v[0] = a;

    float b = (1-a) * random1();
    v[1] = b;

    float c = 1 - a - b;
    v[2] = c;
}

static
float *random_point(float *v, float *p1, float *p2, float *p3)
{
    float b[3];
    random_barycentric(b);

    v[0] = b[0]*p1[0] + b[1]*p2[0] + b[2]*p3[0];
    v[1] = b[0]*p1[1] + b[1]*p2[1] + b[2]*p3[1];
    v[2] = b[0]*p1[2] + b[1]*p2[2] + b[2]*p3[2];

    return v;
}

static
double compute_distances(MxStdModel *m, const float *v)
{
    double min_d2 = HUGE;

    for(uint i=0; i<m->face_count(); i++)
    {
	float *v1 = m->corner(i, 0);
	float *v2 = m->corner(i, 1);
	float *v3 = m->corner(i, 2);

	float plane_dist =
	    m->normal(i)[0] * (v[0] - v1[0]) +
	    m->normal(i)[1] * (v[1] - v1[1]) +
	    m->normal(i)[2] * (v[2] - v1[2]);

	if( plane_dist*plane_dist < min_d2 )
	{
	    double d2 = triangle_project_point(Vec3(v1), Vec3(v2),
					       Vec3(v3), Vec3(v));
	    
	    if( d2 < min_d2 )
		min_d2 = d2;
	}
    }

    if( err_max < min_d2 )
	err_max = min_d2;

    err_sum += min_d2;
    err_sample_count++;

    return min_d2;
}

static
void compute_error(MxStdModel *m0, MxStdModel *m1)
{
    m1->normal_binding(MX_PERFACE);
    m1->synthesize_normals();


    cerr << "Scanning " << m0->vert_count() << " vertices." << endl;
    for(uint i=0; i<m0->vert_count(); i++)
    {
	cerr << "   " << i << "\r";  cerr.flush();
	compute_distances(m1, m0->vertex(i));
    }

    if( sample_count )
    {
	cerr << "Sampling " << m0->face_count() << " faces"
	     << "  [" << sample_count << "x]" << endl;

	for(uint j=0; j<m0->face_count(); j++)
	{
	    cerr << "   " << j << "\r"; cerr.flush();
	    for(uint k=0; k<sample_count; k++)
	    {
		float v[3];
		random_point(v, m0->corner(j,0),
			        m0->corner(j,1),
			        m0->corner(j,2));
		compute_distances(m1, v);
	    }

	}
    }
}

static
void report(MxStdModel *m0, MxStdModel *m1)
{
    cout << m0->face_count() << " "
	 << m1->face_count() << " "
	 << err_max << " "
	 << err_sum / err_sample_count << " "
	 << err_sample_count
	 << endl;
}


int main(int argc, char *argv[])
{
    process_cmdline_only(argc, argv, options, process_options);


    MxStdModel *m0 = read_model_from_file(argv[optind++]);
    MxStdModel *m1 = read_model_from_file(argv[optind++]);

    compute_error(m0, m1);
    compute_error(m1, m0);
    report(m0, m1);

    return 1;
}
