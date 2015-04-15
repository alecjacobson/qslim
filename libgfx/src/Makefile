include ../gfx-config

VEC_SRCS = mat2.cxx mat3.cxx mat4.cxx quat.cxx symmat3.cxx
GEO_SRCS = geom3d.cxx
IMG_SRCS = raster.cxx raster-pnm.cxx raster-tiff.cxx raster-jpeg.cxx \
		raster-png.cxx
MISC_SRCS = time.cxx script.cxx
GUI_SRCS = gui.cxx gltools.cxx baseball.cxx trackball.cxx arcball.cxx

SRCS = $(VEC_SRCS) $(GEO_SRCS) $(IMG_SRCS) $(MISC_SRCS) $(GUI_SRCS)
OBJS = $(SRCS:.cxx=.o)

libgfx.a: $(OBJS)
	$(AR) cru libgfx.a $(OBJS)
	$(RANLIB) libgfx.a

tags: $(SRCS) ../include/gfx/*.h
	ctags $(SRCS) ../include/gfx/*.h

clean:
	-$(RM) $(OBJS) libgfx.a

depend:
	$(CXX_DEPEND) $(SRCS) > Makefile.dep

-include Makefile.dep
