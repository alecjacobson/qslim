/************************************************************************

  PropSlim

  $Id: propslim.cxx,v 1.2 1998/10/13 21:47:16 garland Exp $

 ************************************************************************/

#include <stdmix.h>
#include <mixio.h>
#include <MxTimer.h>
#include <MxSMF.h>
#include <MxPropSlim.h>

static MxStdModel *m;
static uint face_target;

static
void startup_and_input(int argc, char **argv)
{
    MxSMFReader smf;
    m = smf.read(cin);

    face_target = atoi(argv[1]);
}

static
void output_final_model()
{
    m->compact_vertices();
    MxSMFWriter smfout;
    smfout.write(cout, *m);
}

main(int argc, char **argv)
{
    double input_time, init_time, slim_time, output_time;


    MXTIME(input_time, startup_and_input(argc, argv));
    MxPropSlim slim(m);

    MXTIME(init_time, slim.initialize());
    MXTIME(slim_time, slim.decimate(face_target));
    MXTIME(output_time, output_final_model());

    cerr << "+ Running time" << endl;
    cerr << "    Setup       : " << input_time << " sec" << endl;
    cerr << "    PSlim init  : " << init_time << " sec" << endl;
    cerr << "    PSlim run   : " << slim_time << " sec" << endl;
    cerr << "    Output      : " << output_time << " sec" << endl;
    cerr << endl;
    cerr << "    PSlim Total : " << init_time+slim_time << endl;
    cerr << "    Total       : "
         << input_time+init_time+slim_time+output_time <<endl;
}
