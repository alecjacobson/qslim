/************************************************************************

  smfedgelist

  This filter takes models and builds lists of edges for them.  There are
  currently two different kinds of edge lists that can be generated

     (1) All the edges
     (2) A spanning tree [or a fattened version thereof]

  The spanning tree generation is by far the most interesting part right
  now.  Currently, there is only one heuristic available for selecting
  edges in the spanning tree: dihedral angle.

  Copyright (C) 1998 Michael Garland, All Rights Reserved.
  
  $Id: smfedgelist.cxx,v 1.4 2000/11/20 20:58:59 garland Exp $

 ************************************************************************/

#include <stdmix.h>
#include <MxHeap.h>
#include <MxVector.h>

#include "cmdline.h"

inline void SET(bool& o) { o=true; }
inline void UNSET(bool& o) { o=false; }
inline void TOGGLE(bool& o) { o=!o; }

static bool generate_all_edges = false;
static bool will_output_model = true;
static int nontree_target = 0;

static char *options = "aet:";
static char *usage_string =
"-a		Generate all edges in the model\n"
"-e		Output edges only (exclude the model\n"
"-t n		Output n% of non-tree edges\n"
"\n";

class edge_info: public MxEdge, public MxHeapable
{
};

class ModelSpan
{
private:
    MxStdModel *m;
    MxHeap heap;
    MxBlock<uint> labels;
    MxDynBlock<MxEdge> tree_edges;
    MxDynBlock<edge_info*> *nontree_edges;

protected:
    uint vertex_label(uint i);
    uint group_vertices(uint i, uint j);

    void select_edge(uint v1, uint v2);

public:
    ModelSpan(MxStdModel *m0);


    void compute_edge_info(edge_info *);
    void collect_edges();
    void construct();
    void output(ostream&);
};

static
void output_all_edges(MxStdModel *m)
{
    MxVertexList star;

    for(MxVertexID i=0; i<m->vert_count(); i++)
    {
	star.reset();
	m->collect_vertex_star(i, star);

	for(uint j=0; j<star.length(); j++)
	    if( i < star[j] )
		cout << "e " << i+1 << " " << star[j]+1 << endl;
    }
}

static
void output_spanning_tree(MxStdModel *m)
{
    // ASSUME: The original model has already been written out (if wanted).
    //         Therefore, we're free to nuke whatever normals there might
    //         have been.
    //
    m->normal_binding(MX_PERFACE);
    m->synthesize_normals();

    ModelSpan spanner(m);
    spanner.collect_edges();
    spanner.construct();
    spanner.output(cout);
}

static
void process_options(int opt, char *optarg)
{
    switch( opt )
    {
    case 'a':  SET(generate_all_edges);  break;
    case 'e':  UNSET(will_output_model);  break;
    case 't':  nontree_target = atoi(optarg); break;
    }
}



main(int argc, char *argv[])
{
    MxStdModel *m = process_cmdline(argc, argv, options, process_options);

    if( !m )  return 0;

    if( will_output_model )
	output_final_model(m);

    if( generate_all_edges )
	output_all_edges(m);
    else
	output_spanning_tree(m);

    delete m;
    return 0;
}

////////////////////////////////////////////////////////////////////////
//
//
//

ModelSpan::ModelSpan(MxStdModel *m0)
    : heap(3*m0->vert_count()),
      labels(m0->vert_count()),
      tree_edges(m0->vert_count())
{
    m = m0;

    for(uint i=0; i<labels.length(); i++)
	labels[i] = i;

    nontree_edges = NULL;
}

#define PATH_COMPRESSION 1

uint ModelSpan::vertex_label(uint i)
{
#ifdef PATH_COMPRESSION

    if( i == labels[i] )
	return i;
    else
	return (labels[i] = vertex_label(labels[i]));

#else
    SanityCheck(i<m->vert_count());

    while( i != labels[i] )
	i = labels[i];

    return i;
#endif
}

uint ModelSpan::group_vertices(uint i, uint j)
{
    SanityCheck(i<m->vert_count());
    SanityCheck(j<m->vert_count());

    labels[vertex_label(j)] = vertex_label(i);

    return labels[j];
}

void ModelSpan::select_edge(uint v1, uint v2)
{
    MxEdge& e = tree_edges.add();

    e.v1 = v1;
    e.v2 = v2;

    group_vertices(v1, v2);
}

void ModelSpan::compute_edge_info(edge_info *info)
{
    MxFaceList faces;

    m->collect_edge_neighbors(info->v1, info->v2, faces);

    float e;

    if( faces.length() == 2 )
    {
	float n1[3], n2[3];

	n1[0] = m->normal(faces[0])[0];
	n1[1] = m->normal(faces[0])[1];
	n1[2] = m->normal(faces[0])[2];
	n2[0] = m->normal(faces[1])[0];
	n2[1] = m->normal(faces[1])[1];
	n2[2] = m->normal(faces[1])[2];

	e = 1 + mxv_dot(n1, n2, 3);
	e *= e;

    }
    else /*if( faces.length() == 1 )*/
    {
	e = 0;
    }

    info->heap_key(-e);
    heap.insert(info);
}

void ModelSpan::collect_edges()
{
    MxVertexList star;
    uint edge_count = 0;

    for(VID i=0; i<m->vert_count(); i++)
    {
	star.reset();
	m->collect_vertex_star(i, star);

	for(VID j=0; j<star.length(); j++)
	    if( i<star[j] )
	    {
		edge_info *info = new edge_info;
		info->v1 = i;
		info->v2 = star[j];

		compute_edge_info(info);
		edge_count++;
	    }
    }

    if( nontree_target )
    {
	// convert from percentage to actual count
	nontree_target = ((edge_count-m->vert_count()+1)
			     * nontree_target) / 100;
	//
	// and allocate space
	nontree_edges = new MxDynBlock<edge_info*>(nontree_target);
    }
}

void ModelSpan::construct()
{
    uint c=0;

    while( c<m->vert_count()-1 )
    {
	edge_info *info = (edge_info*)heap.extract();
	if( !info ) break;

	uint l1 =  vertex_label(info->v1);
	uint l2 =  vertex_label(info->v2);

	if( l1 != l2 )
	{
	    select_edge(info->v1, info->v2);
	    c++;
	    delete info;
	}
	else if( nontree_target>0 )
	{
	    nontree_edges->add(info);
	    nontree_target--;
	}
	else
	    delete info;
    }
}

void ModelSpan::output(ostream& out)
{
    uint i;

    for(i=0; i<tree_edges.length(); i++)
	out << "e " << tree_edges[i].v1+1 << " " << tree_edges[i].v2+1 << endl;

    if( nontree_edges )
	for(i=0; i<nontree_edges->length(); i++)
	    out << "e "
		<< (*nontree_edges)[i]->v1+1
		<< " "
		<< (*nontree_edges)[i]->v2+1 << endl;
}
