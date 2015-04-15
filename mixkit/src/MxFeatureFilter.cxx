/************************************************************************

  MxFeatureFilter

  This code is designed to support the automatic removal of surface
  features.

  Michael Garland, 1999

  $Id: MxFeatureFilter.cxx,v 1.4.2.1 2004/07/01 18:47:32 garland Exp $

 ************************************************************************/

#include "stdmix.h"
#include "MxVector.h"
#include "MxFeatureFilter.h"

#include "MxQMetric3.h"

MxFeatureFilter::MxFeatureFilter(MxStdModel *m0)
    : flabel(m0->face_count())
{
    m = m0;
    dual = NULL;
    clear_labels();
}

void MxFeatureFilter::clear_labels()
{
    memset(flabel, 0, flabel.length()*sizeof(uint));
}

uint MxFeatureFilter::add_splitter(uint i)
{
    if( i==MXID_NIL ) return MXID_NIL;

    if( splitter.length() >= sizeof(uint)/2 )
	mxmsg_signalf(MXMSG_WARN,
		      "Maximum of %d split planes exceeded."
		      "Will ignore all planes above limit.",
		      sizeof(uint)/2);

    MxPlane3 p;
    m->compute_face_plane(i, p);
    planes.add(p);

    splitter.add(i);
    return splitter.last_id();
}


////////////////////////////////////////////////////////////////////////
//
// Phase 1: Feature extraction
//
// The first phase of feature removal is to segment the surface into
// proposed features.  See the extract_features() method.


uint MxFeatureFilter::split_edge_with_plane(uint i, uint j, float *p)
{
    const float *v1 = m->vertex(i);
    const float *v2 = m->vertex(j);

    // Compute inner products of plane normal with vertices
    float n_v1 = mxv_dot(v1, p, 3);
    float n_v2 = mxv_dot(v2, p, 3);

    // Compute intersection of:  t*v1 + (1-t)*v2  with plane
    float t = -(n_v2 + p[3]) / (n_v1 - n_v2);

    if( t>FEQ_EPS && t<(1-FEQ_EPS) )
    {
	float vnew[3];
	mxv_lerp(vnew, v1, v2, t, 3);
	return m->split_edge(i, j, vnew[0], vnew[1], vnew[2]);
    }
    else
	return MXID_NIL;
}

// slice_model(p) --  Test every edge in the model against plane p.  If the
//   edge crosses the plane, split it.  Otherwise, leave it alone.
//
void MxFeatureFilter::slice_model(MxPlane3& p)
{
    MxVertexList star;
    uint limit = m->vert_count(); // Don't want to traverse newly added verts
    uint i;

    for(i=0; i<limit; i++)
    {
        star.reset();
        m->collect_vertex_star(i, star);

        for(uint j=0; j<star.length(); j++)
            if( i < star[j] )
		split_edge_with_plane(i, star[j], p);
    }

    // Synthesize normals for newly created faces
    m->synthesize_normals(m->normal_count());
}


enum { ON_PLANE = 0, BELOW_PLANE = 1, ABOVE_PLANE = 2 };

// classify_point(v) -- Compute a label for the given point.  Labels
//   are constructed by testing the point against each splitting plane.
//   For a given plane, the point is either ON, ABOVE, or BELOW.  It
//   takes 2 bits to represent these possible values.  The label value
//   is the concatentation of these 2 bit values.
//
uint MxFeatureFilter::classify_point(float *v)
{
    uint label = 0;

    for(uint i=0; i<planes.length(); i++)
    {
	float *p = planes[i];
	float d = mxv_dot(v, p, 3) + p[3];
	uint k;

	if( d>FEQ_EPS )        k = ABOVE_PLANE;
	else if( d<-FEQ_EPS )  k = BELOW_PLANE;
	else                   k = ON_PLANE;

	label = (label << 2) | k;
    }

    return label;
}

// classify_face(f) -- Compute a unique label for the face f based on what
//   cell it lies within.  Since we split all edges which crossed any of
//   the planes, all the vertices of f are in the same cell (or on the
//   planes which form the boundary of the cell).  Since each cell is
//   convex, the barycenter of the triangle must be in the interior of the
//   cell.  Thus, the label of this point determines the label of the face.
//
uint MxFeatureFilter::classify_face(uint f)
{
    uint i;

    // Compute the barycenter of f
    float ctr[3];
    mxv_set(ctr, 0.0f, 3);
    for(i=0; i<3; i++) mxv_addinto(ctr, m->corner(f, i), 3);
    mxv_invscale(ctr, 3.0f, 3);

    return classify_point(ctr);
}

MxDualModel *MxFeatureFilter::extract_features()
{
    uint i;

    if( dual ) { delete dual; dual = NULL; }

    // All edges which cross a splitting plane must be split by that plane.
    //
    for(i=0; i<planes.length(); i++)
	slice_model(planes[i]);
    flabel.resize(m->face_count()); // may have added new faces by splitting

    // Each face is now contained within a single cell, and can be
    // assigned a unique label based on that cell.
    //
    for(i=0; i<m->face_count(); i++)
	flabel[i] = classify_face(i);
    
    // Now that all the faces are labeled, we form the dual graph of the
    // model.  We'll contract any edge in the dual graph which connects
    // two nodes with the same label.  When this process is complete, there
    // will be exactly 1 node per "feature" and the arcs in the graph will
    // indicate the connections between them.
    //
    dual = new MxDualModel(m);
    MxDualContraction conx;

    for(i=0; i<dual->edge_count(); i++)
    {
	const MxDualEdge& e = dual->edge(i);

	// Edge may have been invalidated by an earlier contraction
	if( e.v1==MXID_NIL || e.v2==MXID_NIL ) continue;

	if( flabel(e.v1) == flabel(e.v2) )
	{
	    conx.n1 = e.v1;
	    conx.n2 = e.v2;
	    dual->contract(conx);
	}
    }

    return dual;
}

////////////////////////////////////////////////////////////////////////
//
// Phase 2: Feature removal
//
// Once the surface has been segmented into multiple feature clusters,
// one of those features may be removed.
//
// BUG: This current code is based on the principle of finding the contour
// separating the feature from the rest of the model and contracting
// this contour to a single point.  In many cases, this works acceptably.
// However, for cases such as a box with a ridge or groove all the
// way along the box, contour contraction will not work correctly.  A more
// general solution would be to slice the feature off and to retriangulate
// the resulting holes in the surface.

void MxFeatureFilter::compute_contour_target(uint inside,
					     float *vnew,
					     MxEdgeList& contour)
{
    MxFaceList faces;
    MxQuadric3 Q_total;
    uint i;

    inside = dual->node_ancestor(inside);
    Q_total.clear();

    for(i=0; i<contour.length(); i++)
    {
	const MxEdge& e=contour[i];

	faces.reset();
	m->collect_edge_neighbors(e.v1, e.v2, faces);

	for(uint j=0; j<faces.length(); j++)
	    if( dual->node_ancestor(faces[j]) != inside )
	    {
		MxFace& f = m->face(faces[j]);
		Vec3 v1(m->vertex(f(0)));
		Vec3 v2(m->vertex(f(1)));
		Vec3 v3(m->vertex(f(2)));
		Vec4 p = triangle_plane<Vec3,Vec4>(v1, v2, v3);

		MxQuadric3 Q(p[X], p[Y], p[Z], p[W], m->compute_face_area(i));
		Q *= Q.area();

		Q_total += Q;
	    }
    }

    if( !Q_total.optimize(&vnew[X], &vnew[Y], &vnew[Z]) )
    {
	// Fallback to average of all vertices
	//
	float nverts=0.0f;
	mxv_set(vnew, 0.0, 3);
	for(i=0; i<contour.length(); i++)
	{
	    mxv_addinto(vnew, m->vertex(contour[i].v1), 3);  nverts += 1.0f;
	    mxv_addinto(vnew, m->vertex(contour[i].v2), 3);  nverts += 1.0f;
	}
	mxv_invscale(vnew, nverts, 3);
    }
}

void MxFeatureFilter::contract_contour(MxEdgeList& contour, float *vnew)
{
    MxVertexList verts;
    uint i;

    // Compute the list of vertices on the boundary
    //
    for(i=0; i<contour.length(); i++)
    {
        m->vertex_mark(contour[i].v1, 0);
        m->vertex_mark(contour[i].v2, 0);
    }

    for(i=0; i<contour.length(); i++)
    {
        if( !m->vertex_mark(contour[i].v1) )
        {
            verts.add(contour[i].v1);
            m->vertex_mark(contour[i].v1, 1);
        }

        if( !m->vertex_mark(contour[i].v2) )
        {
            verts.add(contour[i].v2);
            m->vertex_mark(contour[i].v2, 1);
        }
    }

    // Now, contract the boundary into a single point
    //
    MxFaceList changed;
    uint v1 = verts.drop();
    m->contract(v1, verts, vnew, changed);
}

void MxFeatureFilter::remove_feature(uint f, MxEdgeList& contour)
{
    float vnew[3];

    compute_contour_target(f, vnew, contour);
    contract_contour(contour, vnew);

    // Mark all faces in the feature as "invalid".
    //
    uint root = dual->node_ancestor(f);

    for(uint i=0; i<m->face_count(); i++)
	if( dual->node_ancestor(i) == root )
	    m->face_mark_invalid(i);


    // Cleanup data structures that are no longer valid once the
    // model has been altered.
    //
    delete dual;
    dual = NULL;
    contour.reset();
    clear_splitters();
}
