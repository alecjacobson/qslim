@echo off

REM This script writes an appropriate gfx-config file for VC++
REM development systems.  At this point, the configuration process is
REM trivial.  Eventually, it would probably be good to actually look at
REM the state of the machine.

set LOCAL=c:\usr\local
if NOT "%1"=="" set LOCAL=%1

echo LIBGFX = \> gfxloc
chdir >> gfxloc

echo LOCAL = %LOCAL% >> gfxloc
rem echo e:\local >> gfxloc

copy gfxloc+vc-config.in vc-config
del gfxloc

copy gfx-config.vc gfx-config
