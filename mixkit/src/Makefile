#
# Makefile for building the MixKit library
# $Id: Makefile,v 1.50.2.1 2001/09/21 16:18:23 garland Exp $
#

include ../../libgfx/gfx-config

CORE_SRCS = mixmsg.cxx MxCmdParser.cxx MxAsp.cxx

MATH_SRCS = MxMat3-jacobi.cxx MxMat4-jacobi.cxx \
	    MxGeom3D.cxx MxTriProject.cxx MxFrame.cxx MxFitFrame.cxx \
	    MxFitFrame-2.cxx MxGeom2D.cxx mixmops.cxx

MODEL_SRCS = MxBlockModel.cxx MxStdModel.cxx MxSMF.cxx MxQMetric3.cxx \
             MxQSlim.cxx MxStdSlim.cxx MxQMetric.cxx MxPropSlim.cxx \
             MxDualModel.cxx MxFaceTree.cxx MxFaceTree-2.cxx MxDualSlim.cxx \
             MxEdgeFilter.cxx MxFeatureFilter.cxx

DATA_SRCS = MxHeap.cxx 

# These modules require OpenGL or Mesa
GL_SRCS = MxCamera.cxx MxQVis3.cxx \
          MxStdRender.cxx MxGLDebug.cxx MxGLUtils.cxx MxFitFrame-vis.cxx

# These modules require the FLTK toolkit <http://www.fltk.org/>
GUI_SRCS =  MxStdGUI.cxx

SRCS = $(CORE_SRCS) $(MATH_SRCS) $(MODEL_SRCS) $(DATA_SRCS) \
       $(GL_SRCS) $(GUI_SRCS)

OBJS = $(SRCS:.cxx=.o)

########################################################################

libmix.a: $(OBJS)
	$(AR) cru libmix.a $(OBJS)
	$(RANLIB) libmix.a

clean:
	-$(RM) -f $(OBJS) libmix.a

depend:
	$(CXX_DEPEND) $(SRCS) > Makefile.dep


-include Makefile.dep
#sinclude Makefile.dep     # Alternative syntax for some makes
