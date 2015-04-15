include ../../mixkit/mix-config

COMMON_SRCS = cmdline.cxx
COMMON_OBJS = $(COMMON_SRCS:.cxx=.o)
ALL_SRCS = $(COMMON_SRCS) smfclean.cxx smfstitch.cxx smfcat.cxx \
           smfmeasure.cxx smfedgelist.cxx \
           smf2ply.cxx smf2ldmesh.cxx smf2c.cxx smfsphere.cxx smfrefine.cxx \
           smfquadric.cxx smfboundary.cxx smferror.cxx ply2smf.cxx \
           smf2iv.cxx smf2flat.cxx
PROGS = smfclean smfstitch smfcat smfmeasure smfedgelist \
        smf2ply smf2ldmesh smf2c smfsphere smfrefine smfquadric \
        smfboundary smferror ply2smf smf2iv smf2flat

all: $(PROGS)

qsmooth: qsmooth.o $(COMMON_OBJS)
	$(CXX) -o qsmooth qsmooth.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smfclean: smfclean.o $(COMMON_OBJS)
	$(CXX) -o smfclean smfclean.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smfstitch: smfstitch.o $(COMMON_OBJS)
	$(CXX) -o smfstitch smfstitch.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smfcat: smfcat.o $(COMMON_OBJS)
	$(CXX) -o smfcat smfcat.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smfmeasure: smfmeasure.o $(COMMON_OBJS)
	$(CXX) -o smfmeasure smfmeasure.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smfedgelist: smfedgelist.o $(COMMON_OBJS)
	$(CXX) -o smfedgelist smfedgelist.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smf2ply: smf2ply.o $(COMMON_OBJS)
	$(CXX) -o smf2ply smf2ply.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smf2ldmesh: smf2ldmesh.o $(COMMON_OBJS)
	$(CXX) -o smf2ldmesh smf2ldmesh.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smf2c: smf2c.o $(COMMON_OBJS)
	$(CXX) -o smf2c smf2c.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smf2iv: smf2iv.o $(COMMON_OBJS)
	$(CXX) -o smf2iv smf2iv.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smf2flat: smf2flat.o $(COMMON_OBJS)
	$(CXX) -o smf2flat smf2flat.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smfsphere: smfsphere.o $(COMMON_OBJS)
	$(CXX) -o smfsphere smfsphere.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smfrefine: smfrefine.o $(COMMON_OBJS)
	$(CXX) -o smfrefine smfrefine.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smfquadric: smfquadric.o $(COMMON_OBJS)
	$(CXX) -o smfquadric smfquadric.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smfboundary: smfboundary.o $(COMMON_OBJS)
	$(CXX) -o smfboundary smfboundary.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

smferror: smferror.o $(COMMON_OBJS)
	$(CXX) -o smferror smferror.o $(COMMON_OBJS) $(LDFLAGS) $(LIBMIX) -lm

ply2smf: ply2smf.o plyfile.o
	$(CXX) -o ply2smf ply2smf.o plyfile.o $(LDFLAGS) $(LIBMIX) -lm

strip:
	strip $(PROGS)

clean:
	-$(RM) -f $(ALL_SRCS:.cxx=.o) $(PROGS)

depend:
	$(CXX_DEPEND) $(ALL_SRCS) > Makefile.dep

-include Makefile.dep
