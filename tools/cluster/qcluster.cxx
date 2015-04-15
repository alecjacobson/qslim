/************************************************************************

  Command line program for hierarchical face clustering.  Currently,
  this is more of an example than a really useful program.  It provides
  a particularly simple interface to the underlying clustering mechanism.
  It doesn't even allow any customization right now.

  Copyright (C) 1998 Michael Garland, All Rights Reserved.
  
  $Id: qcluster.cxx,v 1.4 2000/06/09 17:30:53 garland Exp $

 ************************************************************************/

#include <stdmix.h>
#include <MxTimer.h>
#include <MxSMF.h>
#include <MxDualSlim.h>

MxStdModel *m=NULL;
MxDualSlim *dslim = NULL;
MxFaceTree *tree = NULL;
MxDualModel *dual = NULL;
MxBlock<uint> *fmap_id2pos = NULL;
MxBlock<uint> *fmap_pos2id = NULL;


#define CLEANUP(x)  if(x) { delete x; x=NULL; }

void cluster_init(MxStdModel *m)
{
    dual = new MxDualModel(m);
    tree = new MxFaceTree(m);
    dslim = new MxDualSlim(m, dual, tree);

    dslim->shape_policy = MX_SHAPE_REGULAR;
    dslim->initialize();
}

void cluster_cleanup()
{
    CLEANUP(dual);
    CLEANUP(tree);
    CLEANUP(dslim);
    CLEANUP(m);
    CLEANUP(fmap_id2pos);
    CLEANUP(fmap_pos2id);
}

void cluster_construct(MxStdModel *m)
{
    dslim->aggregate(1);
}

void startup_and_input(int argc, char **argv)
{
    MxSMFReader smf;
    m = smf.read(cin);
    
}

static
void write_fmap(uint id, uint first_slot)
{
    const MxFaceCluster& current = tree->cluster(id);

    if( tree->cluster_is_leaf(id) )
    {
	// Terminate at leaves by writing into the face map
	(*fmap_pos2id)(first_slot) = id;
	(*fmap_id2pos)(id) = first_slot;
    }
    else
    {
	const MxFaceCluster& left = tree->cluster(current.child[0]);
	const MxFaceCluster& right = tree->cluster(current.child[1]);

	write_fmap(current.child[0], first_slot);
	write_fmap(current.child[1], first_slot + left.nfaces);
    }
}


void output_geometry(MxStdModel *m)
{
    uint i;

    // output vertices
    for(i=0; i<m->vert_count(); i++)  cout << m->vertex(i) << endl;

    // output faces
    for(i=0; i<m->face_count(); i++)
	cout << m->face(fmap_pos2id?(*fmap_pos2id)[i]:i) << endl;
}

void output_face_tree(MxStdModel *m, MxFaceTree *tree)
{
    uint i;

    for(i=0; i<tree->cluster_count(); i++)
    {
	MxFaceCluster& c = tree->cluster(i);
	if( !tree->cluster_is_leaf(i) )
	{
	    if(fmap_id2pos) c.write(cout, *fmap_id2pos, fmap_id2pos->length());
	    else            c.write(cout);
	}
    }
}

main(int argc, char **argv)
{
    double input_time, init_time, cluster_time, bbox_time, output_time;

    MXTIME(input_time, startup_and_input(argc, argv));
    cerr << "+ Initial model    " << "(" << m->vert_count() << "v/"
	 << m->face_count() << "f)" << endl;

    MXTIME(init_time, cluster_init(m));
    MXTIME(cluster_time, cluster_construct(m));
    cerr << "+ Dual clustering complete; "
	 << dslim->root_cluster_count
	 << (dslim->root_cluster_count>1 ? " clusters":" cluster")
	 << " remaining." << endl;

    MXTIME(bbox_time, tree->compute_bboxes());
    cerr << "+ BBox hierarchy complete" << endl;

#ifndef NO_REMAP_FACES
    fmap_id2pos = new MxBlock<uint>(m->face_count());
    fmap_pos2id = new MxBlock<uint>(m->face_count());

    write_fmap(tree->find_root_cluster(0), 0);
#endif
    MXTIME(output_time, output_geometry(m);output_face_tree(m, tree));

    cluster_cleanup();


    cerr << endl << endl;
    cerr << "+ Running time" << endl;
    cerr << "    Setup         : " << input_time << " sec" << endl;
    cerr << "    QCluster init : " << init_time << " sec" << endl;
    cerr << "    QCluster run  : " << cluster_time << " sec" << endl;
    cerr << "    QCluster bbox : " << bbox_time << " sec" << endl;
    cerr << "    Output        : " << output_time << " sec" << endl;
    cerr << endl;
    cerr << "    Total         : "
	 << input_time+init_time+cluster_time+output_time << " sec" << endl;
}
