# Include the 'gfx-config' file to get all the correct build settings
include ../gfx-config

SRCS = t-vec.cxx t-img.cxx t-gui.cxx t-glimg.cxx t-script.cxx t-glext.cxx
ALL = $(SRCS:.cxx=)

all: $(ALL)

t-vec: t-vec.cxx
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) -lgfx -lm

t-script: t-script.cxx
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) -lgfx -lm

t-img: t-img.cxx
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) -lgfx $(IMG_LIBS) -lm

#
# GUI programs should make the appropriate post-build call to
# $(FLTKCONFIG).  On most platforms, this does nothing, but under
# Mac OS X, it is essential to make GUI programs launch correctly.
#

t-gui: t-gui.cxx
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) -lgfx $(GUI_LIBS) -lm
	$(FLTKCONFIG) --post $@

t-glext: t-glext.cxx
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) -lgfx $(GUI_LIBS) -lm
	$(FLTKCONFIG) --post $@

t-glimg: t-glimg.cxx
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) -lgfx $(GUI_LIBS) -lm
	$(FLTKCONFIG) --post $@

# This is just a standard mechanism to correctly track the dependencies
# of the source files.
#
depend:
	$(CXX_DEPEND) $(SRCS) > Makefile.dep

-include Makefile.dep
