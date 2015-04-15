# Microsoft Developer Studio Project File - Name="libgfxmfc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=libgfxmfc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libgfx.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libgfx.mak" CFG="libgfxmfc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libgfxmfc - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "libgfxmfc - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libgfxmfc - Win32 Release"

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
# ADD CPP /nologo /MD /W3 /GX /O2 /I "../../include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "libgfxmfc - Win32 Debug"

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
# ADD CPP /nologo /MDd /W3 /GX /Z7 /Od /I "../../include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
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

# Name "libgfxmfc - Win32 Release"
# Name "libgfxmfc - Win32 Debug"
# Begin Group "Header Files"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\..\include\gfx\arcball.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\array.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\baseball.h
# End Source File
# Begin Source File

SOURCE="..\..\include\gfx\config-vc.h"
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\geom3d.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\gfx.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\gl.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\gltools.h
# End Source File
# Begin Source File

SOURCE="..\..\include\gfx\gui-mfc.h"
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\gui.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\intvec.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\mat2.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\mat3.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\mat4.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\mfc.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\quat.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\raster.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\script.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\trackball.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\vec2.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\vec3.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\vec4.h
# End Source File
# Begin Source File

SOURCE=..\..\include\gfx\wintools.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\..\src\arcball.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\baseball.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\geom3d.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\gltools.cxx
# End Source File
# Begin Source File

SOURCE="..\..\src\gui-mfc.cxx"
# End Source File
# Begin Source File

SOURCE=..\..\src\mat2.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\mat3.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\mat4.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\quat.cxx
# End Source File
# Begin Source File

SOURCE="..\..\src\raster-jpeg.cxx"
# End Source File
# Begin Source File

SOURCE="..\..\src\raster-png.cxx"
# End Source File
# Begin Source File

SOURCE="..\..\src\raster-pnm.cxx"
# End Source File
# Begin Source File

SOURCE="..\..\src\raster-tiff.cxx"
# End Source File
# Begin Source File

SOURCE=..\..\src\raster.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\script.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\time.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\trackball.cxx
# End Source File
# Begin Source File

SOURCE=..\..\src\wintools.cxx
# End Source File
# End Target
# End Project
