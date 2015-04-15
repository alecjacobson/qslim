/************************************************************************

  MxEdgeFilter

  Copyright (C) 1998 Michael Garland.  See "COPYING.txt" for details.
  
  $Id: MxEdgeFilter.cxx,v 1.3 1998/10/26 21:08:49 garland Exp $

 ************************************************************************/

#include "stdmix.h"
#include "MxEdgeFilter.h"
#include "MxVector.h"

MxEdgeFilter::MxEdgeFilter(MxStdModel *m0)
    : heap(3*m0->vert_count()),
      update_list(8)
{
    m = m0;

    current_edge_count = original_edge_count = 0;
}

void MxEdgeFilter::rank_and_update_edge(MxRankedEdge *edge)
{
    float rank = compute_edge_rank(edge);

    edge->heap_key(rank);

    if( edge->is_in_heap() )
	heap.update(edge);
    else
	heap.insert(edge);
}

MxRankedEdge *MxEdgeFilter::create_edge(MxVertexID v1, MxVertexID v2,
					bool will_rank)
{
    MxRankedEdge *edge = new MxRankedEdge(v1, v2);
    current_edge_count++;
    if( will_rank )
	rank_and_update_edge(edge);
    return edge;
}

void MxEdgeFilter::collect_star_for_update(MxVertexID v)
{
    MxVertexList star;
    m->collect_vertex_star(v, star);
    for(uint i=0; i<star.length(); i++)
	update_list.add(create_edge(v, star[i], false));
}

void MxEdgeFilter::collect_edges()
{
    MxVertexList star;

    for(MxVertexID i=0; i<m->vert_count(); i++)
    {
	star.reset();
	m->collect_vertex_star(i, star);

	for(uint j=0; j<star.length(); j++)
	    if( i<star[j] )
	    {
		create_edge(i, star[j]);
		original_edge_count++;
	    }
    }
}

void MxEdgeFilter::initialize()
{
    collect_edges();
}

MxVertexID MxEdgeFilter::split_edge(MxRankedEdge *edge)
{
    MxVertexID vnew = m->split_edge(edge->v1, edge->v2);

    collect_star_for_update(vnew);

    return vnew;
}

bool MxEdgeFilter::filter1()
{
    MxRankedEdge *edge = (MxRankedEdge *)heap.extract();
    if( !edge ) return false;

    update_list.reset();

    filter_target_edge(edge);

    for(uint i=0; i<update_list.length(); i++)
	rank_and_update_edge(update_list[i]);

	// Allow for the possibility that this edge will be modified
	// and placed back in the heap with a new rank.
	//
    if( !edge->is_in_heap() )
	delete edge;

    return true;
}

bool MxEdgeFilter::filter(uint target)
{
    while( current_edge_count < target )
    {
	if( !filter1() )
	    return false;
    }

    return true;
}

bool MxEdgeFilter::filter_above_rank(float rank)
{
    while( heap.top() && heap.top()->heap_key() > rank )
    {
	if( !filter1() )
	    return false;
    }

    return true;
}

////////////////////////////////////////////////////////////////////////
//
// Default implementations of rank & filter virtual functions.  The
// effect of the defaults is to split edges based on squared length.
//
float MxEdgeFilter::compute_edge_rank(MxRankedEdge *edge)
{
    return mxv_L2(m->vertex(edge->v1), m->vertex(edge->v2), 3);
}

void MxEdgeFilter::filter_target_edge(MxRankedEdge *edge)
{
    split_edge(edge);
}
