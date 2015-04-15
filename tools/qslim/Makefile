include ../../mixkit/mix-config

SRCS = cmdline.cxx main.cxx output.cxx qslim.cxx
QVIS_SRCS = cmdline.cxx main.cxx output.cxx qvis.cxx
OBJS = $(SRCS:.cxx=.o)
QVIS_OBJS = $(QVIS_SRCS:.cxx=.o)

all: qslim qvis

qslim : $(OBJS) ../../mixkit/src/libmix.a
	$(CXX) -o qslim $(OBJS) $(LDFLAGS) $(LIBMIX) -lm -lfltk_gl
# Alec ^

qvis : $(QVIS_OBJS) ../../mixkit/src/libmix.a
	$(CXX) -o qvis $(QVIS_OBJS) $(LDFLAGS) $(LIBMIX) $(GUI_LIBS) -lm -lfltk_gl
# Alec ^
	$(FLTKCONFIG) --post qvis

clean:
	-$(RM) -f $(OBJS) qslim qvis
	-cat /dev/null > Makefile.dep


depend:
	$(CXX_DEPEND) $(SRCS) $(QVIS_SRCS) > Makefile.dep

-include Makefile.dep
