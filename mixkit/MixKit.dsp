# Microsoft Developer Studio Project File - Name="MixKit" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=MixKit - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "MixKit.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "MixKit.mak" CFG="MixKit - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "MixKit - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "MixKit - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "MixKit - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /I "../mixkit/src" /I "../libgfx/include" /D "NDEBUG" /D SAFETY=0 /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "MixKit - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /W3 /GX /Z7 /Od /I "../mixkit/src" /I "../libgfx/include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "MixKit - Win32 Release"
# Name "MixKit - Win32 Debug"
# Begin Group "Math"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\mixmops.cxx
# End Source File
# Begin Source File

SOURCE=.\src\mixmops.h
# End Source File
# Begin Source File

SOURCE=.\src\mixvops.h
# End Source File
# Begin Source File

SOURCE=.\src\MxFrame.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxFrame.h
# End Source File
# Begin Source File

SOURCE=".\src\MxMat3-jacobi.cxx"
# End Source File
# Begin Source File

SOURCE=".\src\MxMat4-jacobi.cxx"
# End Source File
# Begin Source File

SOURCE=.\src\MxMatrix.h
# End Source File
# Begin Source File

SOURCE=.\src\MxVector.h
# End Source File
# End Group
# Begin Group "Basic Types"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\MxBlock.h
# End Source File
# Begin Source File

SOURCE=.\src\MxBlock2.h
# End Source File
# Begin Source File

SOURCE=.\src\MxBlock3.h
# End Source File
# Begin Source File

SOURCE=.\src\MxDynBlock.h
# End Source File
# Begin Source File

SOURCE=.\src\MxHeap.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxHeap.h
# End Source File
# Begin Source File

SOURCE=.\src\MxStack.h
# End Source File
# Begin Source File

SOURCE=.\src\MxString.h
# End Source File
# End Group
# Begin Group "3D Modeling"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\MxBlockModel.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxBlockModel.h
# End Source File
# Begin Source File

SOURCE=.\src\MxGeom3D.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxGeom3D.h
# End Source File
# Begin Source File

SOURCE=.\src\MxGeoPrims.h
# End Source File
# Begin Source File

SOURCE=.\src\MxPropSlim.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxPropSlim.h
# End Source File
# Begin Source File

SOURCE=.\src\MxQMetric.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxQMetric.h
# End Source File
# Begin Source File

SOURCE=.\src\MxQMetric3.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxQMetric3.h
# End Source File
# Begin Source File

SOURCE=.\src\MxQSlim.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxQSlim.h
# End Source File
# Begin Source File

SOURCE=.\src\MxSMF.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxSMF.h
# End Source File
# Begin Source File

SOURCE=.\src\MxStdModel.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxStdModel.h
# End Source File
# Begin Source File

SOURCE=.\src\MxStdSlim.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxStdSlim.h
# End Source File
# Begin Source File

SOURCE=.\src\MxTriProject.cxx
# End Source File
# End Group
# Begin Group "GL-GUI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\MxCamera.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxCamera.h
# End Source File
# Begin Source File

SOURCE=.\src\MxGL.h
# End Source File
# Begin Source File

SOURCE=.\src\MxGLDebug.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxGLUtils.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxGLUtils.h
# End Source File
# Begin Source File

SOURCE=.\src\MxManipulator.h
# End Source File
# Begin Source File

SOURCE=.\src\MxQVis3.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxStdRender.cxx
# End Source File
# End Group
# Begin Group "Misc Services"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\mixmsg.cxx
# End Source File
# Begin Source File

SOURCE=.\src\mixmsg.h
# End Source File
# Begin Source File

SOURCE=.\src\MxAsp.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxAsp.h
# End Source File
# Begin Source File

SOURCE=.\src\MxCmdParser.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxCmdParser.h
# End Source File
# End Group
# Begin Group "Surface Clustering"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\MxDualModel.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxDualModel.h
# End Source File
# Begin Source File

SOURCE=.\src\MxDualSlim.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxDualSlim.h
# End Source File
# Begin Source File

SOURCE=".\src\MxFaceTree-2.cxx"
# End Source File
# Begin Source File

SOURCE=.\src\MxFaceTree.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxFaceTree.h
# End Source File
# Begin Source File

SOURCE=".\src\MxFitFrame-2.cxx"
# End Source File
# Begin Source File

SOURCE=.\src\MxFitFrame.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxFitFrame.h
# End Source File
# End Group
# Begin Group "GNU getopt"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\getopt.c
# End Source File
# Begin Source File

SOURCE=.\src\getopt.h
# End Source File
# Begin Source File

SOURCE=.\src\getopt1.c
# End Source File
# End Group
# Begin Group "FLTK-based GUI"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\src\MxStdGUI.cxx
# End Source File
# Begin Source File

SOURCE=.\src\MxStdGUI.h
# End Source File
# End Group
# Begin Group "Documentation"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\COPYING.txt
# End Source File
# Begin Source File

SOURCE=.\LGPL.txt
# End Source File
# Begin Source File

SOURCE=.\README.txt
# End Source File
# End Group
# Begin Source File

SOURCE=.\src\mixio.h
# End Source File
# Begin Source File

SOURCE=.\src\stdmix.h
# End Source File
# End Target
# End Project
