#ifndef MXEDGEFILTER_INCLUDED // -*- C++ -*-
#define MXEDGEFILTER_INCLUDED

/************************************************************************

  MxEdgeFilter

  Copyright (C) 1998 Michael Garland.  See "COPYING.txt" for details.
  
  $Id: MxEdgeFilter.h,v 1.2 1998/10/26 21:08:50 garland Exp $

 ************************************************************************/

#include "MxStdModel.h"
#include "MxHeap.h"

class MxRankedEdge : public MxEdge, public MxHeapable
{
public:
    MxRankedEdge(MxVertexID v1, MxVertexID v2) : MxEdge(v1,v2) { }
};

class MxEdgeFilter
{
private:
    MxHeap heap;
    MxDynBlock<MxRankedEdge *> update_list;

    bool filter1();

protected:
    MxStdModel *m;

    MxRankedEdge *create_edge(MxVertexID, MxVertexID, bool will_rank=true);
    void collect_edges();
    void collect_star_for_update(MxVertexID);
    void rank_and_update_edge(MxRankedEdge *);

    MxVertexID split_edge(MxRankedEdge *);

    virtual float compute_edge_rank(MxRankedEdge *);
    virtual void filter_target_edge(MxRankedEdge *);

public:
    uint original_edge_count;
    uint current_edge_count;

public:
    MxEdgeFilter(MxStdModel *m0);

    void initialize();
    bool filter(uint target);
    bool filter_above_rank(float);
};

// MXEDGEFILTER_INCLUDED
#endif
