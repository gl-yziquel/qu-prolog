// trail.cc - The various trails used bu QuProlog.
//
// ##Copyright##
// 
// Copyright (C) 2000, 20001
// Software Verification Research Centre
// The University of Queensland
// Australia 4072
// 
// email: svrc@it.uq.edu.au
// 
// The Qu-Prolog 6.0 System and Documentation  
// 
// COPYRIGHT NOTICE, LICENCE AND DISCLAIMER.
// 
// Copyright 2000,2001 by The University of Queensland, 
// Queensland 4072 Australia
// 
// Permission to use, copy and distribute this software and associated
// documentation for any non-commercial purpose and without fee is hereby 
// granted, subject to the following conditions:
// 
// 1. 	that the above copyright notice and this permission notice and 
// 	warranty disclaimer appear in all copies and in supporting 
// 	documentation; 
// 
// 2.	that the name of the University of Queensland not be used in 
// 	advertising or publicity pertaining to distribution of the software 
// 	without specific, written prior permission; 
// 
// 3.	that users of this software should be responsible for determining the 
// 	fitness of the software for the purposes for which the software is 
// 	employed by them; 
// 
// 4. 	that no changes to the system or documentation are subsequently 
// 	made available to third parties or redistributed without prior 
// 	written consent from the SVRC; and
// 
// The University of Queensland disclaims all warranties with regard to this
// software, including all implied warranties of merchantability and fitness
// to the extent permitted by law. In no event shall the University of 
// Queensland be liable for any special, indirect or consequential damages or 
// any damages whatsoever resulting from loss of use, data or profits, whether 
// in an action of contract, negligence or other tortious action, arising out 
// of or in connection with the use or performance of this software.
// 
// THE UNIVERSITY OF QUEENSLAND MAKES NO REPRESENTATIONS ABOUT THE ACCURACY OR
// SUITABILITY OF THIS MATERIAL FOR ANY PURPOSE.  IT IS PROVIDED "AS IS",
// WITHOUT ANY EXPRESSED OR IMPLIED WARRANTIES.
// 
// 
// For information on commercial use of this software contact the SVRC.
// 
// ##Copyright##
//
// $Id: trail.cc,v 1.5 2001/12/10 03:56:40 qp Exp $

#include "area_offsets.h"
#include "heap_qp.h"
#include "stack_qp.h"
#include "trail.h"
#include "dynamic_code.h"


//
// Attempt to decement reference to clause block - only possible if
// no choice point was created in body of clause.
//
void
RefTrail::tryDecRef(const TrailLoc loc)
{
#if 0
  cerr << "tryDecRef loc = " << (word32)loc << endl;
  for (TrailLoc i = 0; i < getTop(); i++)
    {
      cerr << (word32)i << " : ";
      RefObject* ptr = fetchAddr(i);
      if (ptr->isEmpty())
	{
	  cerr << "Empty" << endl;
	}
      else if (ptr->isAlt())
	{
	  cerr << "Alt - pred = " << (word32)(ptr->getPred()) << endl;
	}
      else if (ptr->isClause())
	{
	  cerr << "Cla - pred = " << (word32)(ptr->getPred()) << endl;
	}
      else
	{
	  cerr << "Link - ent = " << (word32)(ptr->getLink()) << endl;
	}
    }
#endif

  TrailLoc iter = getTop() - 1;
  RefObject* ptr = fetchAddr(iter);
  DEBUG_ASSERT(ptr != NULL);

  while (!ptr->isClause())
    {
      DEBUG_ASSERT(!ptr->isEmpty());
      if (ptr->isAlt())
	{
	  iter--;
	}
      else
	{
	  DEBUG_ASSERT(ptr->isEndLink());
	  iter = ptr->getLink() - 1;
	}
      ptr = fetchAddr(iter);
      DEBUG_ASSERT(ptr != NULL);
    }
  if ((loc < getTop()) && (iter == getTop() - 1))
    {
      DynamicPredicate* pred = ptr->getPred();
      DEBUG_ASSERT(pred != NULL);
      pred->release();
      setTopOfStack(iter);
    }
  else
    {
      RefObject r(REF_ENDCL, iter);
      trail(r);
    }
}

