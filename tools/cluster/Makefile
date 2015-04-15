include ../../mixkit/mix-config

SRCS = qcluster.cxx
OBJS = $(SRCS:.cxx=.o)

qcluster : qcluster.o ../../mixkit/src/libmix.a
	$(CXX) -o qcluster qcluster.o $(LDFLAGS) $(LIBMIX) -lm

depend:
	$(CXX_DEPEND) $(SRCS) > Makefile.dep

clean:
	-$(RM) -f qcluster $(OBJS)
	-cat /dev/null > Makefile.dep

-include Makefile.dep
