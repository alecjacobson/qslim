#ifndef MXFEATUREFILTER_INCLUDED // -*- C++ -*-
#define MXFEATUREFILTER_INCLUDED
#if !defined(__GNUC__)
#  pragma once
#endif

/************************************************************************

  MxFeatureFilter

  Michael Garland, 1999

  $Id: MxFeatureFilter.h,v 1.1 1999/07/14 19:40:53 garland Exp $

 ************************************************************************/

#include "MxGeom3D.h"
#include "MxStdModel.h"
#include "MxDualModel.h"

class MxFeatureFilter 
{
protected:
    MxStdModel *m;
    MxDualModel *dual;

    MxBlock<uint> flabel;
    MxFaceList splitter;
    MxDynBlock<MxPlane3> planes;

protected:
    void clear_labels();

    uint split_edge_with_plane(uint i, uint j, float *p);
    void slice_model(MxPlane3& p);
    uint classify_point(float *v);
    uint classify_face(uint f);

    void compute_contour_target(uint f, float *vnew, MxEdgeList& contour);
    void contract_contour(MxEdgeList& contour, float *vnew);

public:
    MxFeatureFilter(MxStdModel *m0);

    uint splitter_count() const { return splitter.length(); }
    void clear_splitters() { splitter.reset(); planes.reset(); }
    uint add_splitter(uint i);

    MxDualModel *extract_features();
    void remove_feature(uint f, MxEdgeList& contour);
};

// MXFEATUREFILTER_INCLUDED
#endif
