#ifndef MXTIMER_INCLUDED // -*- C++ -*-
#define MXTIMER_INCLUDED
#if !defined(__GNUC__)
#  pragma once
#endif

/************************************************************************

  MxTimer

  Copyright (C) 1998 Michael Garland.  See "COPYING.txt" for details.
  
  $Id: MxTimer.h,v 1.4.8.1 2002/01/31 18:38:37 garland Exp $

 ************************************************************************/

#define MXTIME(t, cmd) { t=get_cpu_time(); cmd; t=get_cpu_time() - t; }

// MXTIMER_INCLUDED
#endif
