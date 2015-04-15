include ../mixkit/mix-config

PROGS = propslim
GUI_PROGS = smfview propvis

all: $(PROGS) $(GUI_PROGS)

propslim: propslim.o ../mixkit/src/libmix.a
	$(CXX) -o propslim propslim.o $(LDFLAGS) $(LIBMIX) -lm

smfview : smfview.o ../mixkit/src/libmix.a
	$(CXX) -o smfview smfview.o $(LDFLAGS) $(LIBMIX) $(GUI_LIBS) -lm
	$(FLTKCONFIG) --post smfview

propvis : propvis.o ../mixkit/src/libmix.a
	$(CXX) -o propvis propvis.o $(LDFLAGS) $(LIBMIX) $(GUI_LIBS) -lm
	$(FLTKCONFIG) --post propvis

-include Makefile.dep
