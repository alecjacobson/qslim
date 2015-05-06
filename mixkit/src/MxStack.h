#ifndef MXSTACK_INCLUDED // -*- C++ -*-
#define MXSTACK_INCLUDED
#if !defined(__GNUC__)
#  pragma once
#endif

/************************************************************************

  This provides a very simple typed-access stack class.  It's really
  just a convenience wrapper for the underlying MxDynBlock class.

  Copyright (C) 1998 Michael Garland.  See "COPYING.txt" for details.
  
  $Id: MxStack.h,v 1.6 2000/11/20 20:36:38 garland Exp $

 ************************************************************************/

#include "MxDynBlock.h"

template<class T>
class MxStack : private MxDynBlock<T>
{
public:
    MxStack(unsigned int n) : MxDynBlock<T>(n)
	{ }
    MxStack(const T& val, unsigned int n) : MxDynBlock<T>(n)
	{ push(val); }

    T&       top()       { return this->last(); }
    const T& top() const { return this->last(); }

    bool is_empty() { return this->length()==0; }

    T& pop() { return this->drop(); }

    void push(const T& val) { this->add(val); }
    //
    // NOTE: In this code, it is *crucial* that we do the add() and
    //       assignment in separate steps.  The obvious alternative
    //       is something like { add(top()); }.  But this is subtly
    //       broken!  The top() will grab a pointer into the block,
    //       but the add() may reallocate the block before doing the
    //       assignment.  Thus, the pointer will become invalid.
    void push() { this->add(); this->top() = (*this)[this->length()-2]; }
};

// MXSTACK_INCLUDED
#endif
