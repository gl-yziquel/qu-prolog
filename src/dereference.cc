// dereference.cc - A few versions of dereference.  
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
// $Id: dereference.cc,v 1.3 2000/12/13 23:10:01 qp Exp $

#include "heap_qp.h"

//extern AtomTable* atoms;

//
// Dereference a substituted term returning the dereferenced object with
// substitutions evaluated as far as possible.
//
Object*
Heap::subDereference(Object* o)
{
  DEBUG_ASSERT(o->isSubstitution());
  DEBUG_ASSERT(o->hasLegalSub());
  Substitution *osub = OBJECT_CAST(Substitution *, o);
  Object* term = osub->getTerm();
  Object* sub  = osub->getSubstitutionBlockList();
  substitutionDereference(sub, term);
  if (osub->getTerm() == term && osub->getSubstitutionBlockList() == sub)
    {
      // nothing is achieved so return original term.
      return (o);
    }
  else
    {
      if (sub->isNil())
	{
	  // no substitution left
	  return (term);
	}
      else
	{
	  return(newSubstitution(sub,term));
	}
    }
}


//
// substitutionDereference dereferences substitution,term pairs.  All the
// top-level substitutions are collected into a single list of
// substitutions and any possible substitution evaluations are carried
// out.  
//
void
Heap::substitutionDereference(Object *& sublist, Object *& term)
{
  while (true)
    {
      term = term->variableDereference(); 
      
      while(term->isSubstitution()) 
	{
	  Substitution *substitution = OBJECT_CAST(Substitution *, term);

	  sublist = appendSubstitutionBlockLists(substitution->getSubstitutionBlockList(), sublist);
	  term = substitution->getTerm()->variableDereference(); 
	} 

      // 
      // At this point all the top-level substitutions have been moved out 
      // of term and into sublist
      //
      DEBUG_ASSERT(! term->isSubstitution()); // implied by while(...)

      if (term->isObjectVariable())
	{
	  if (sublist->isNil())
	    {
	      return;
	    }
          DEBUG_ASSERT(OBJECT_CAST(Cons*, sublist)->getHead()->isSubstitutionBlock());
	  SubstitutionBlock* subblock =
	    OBJECT_CAST(SubstitutionBlock*, 
			OBJECT_CAST(Cons*, sublist)->getHead());

	  DEBUG_ASSERT(subblock->getSize() > 0);

	  if (term->isLocalObjectVariable()) 
	    {
	      if (subblock->getDomain(1)->isLocalObjectVariable())
		{
		  for (size_t i = 1; i <= subblock->getSize(); i++)
		    {
		      if (term == subblock->getDomain(i))
			{
			  //
			  // [t1/v1, ... tk/vk, ... tn/vn] vk => tk
			  //
			  term = subblock->getRange(i);
			  break;
			}
		    }
		}

	      sublist = OBJECT_CAST(Cons*, sublist)->getTail();
	    }
	  else
	    {
	      //
	      // Term is ordinary object variable.
	      // Evaluate substitution.
	      //
	      bool saved = false;
              bool derefed = false;
	      Object* save;
	      for (size_t i = 1; i <= subblock->getSize(); i++)
		{
		  Object* domain = subblock->getDomain(i);
 		  domain = domain->variableDereference();
                  Object* range = subblock->getRange(i)->variableDereference();
		  if (term == domain && (!saved || save == range))
		    {
		      //
		      // [t1/x1, ... tk/xk, ... tn/xn] xk => tk
		      //
		      term = range;
                      derefed = true;
		      break;
		    }
		  else if (term->distinctFrom(domain))
		    {
                      if (!saved)
                        {
                          derefed = true;
                        }
		      continue;
		    }
		  else
		    {
                      derefed = false;
                      if (!saved)
                        {
                           saved = true;
			   save = range;
                        }
                      else
                        {
                           if (save == range)
                             {
                               continue;
                             }
                           else
                             {
		               // 
		               // No (more) substitution evaluation possible
		               //
		               return;
                              }
                         }
		    }
		}
              if (!derefed)
                {
                  return;
                }
	      // 
	      // this subblock didn't do anything, so move on 
	      //
	      sublist = OBJECT_CAST(Cons*, sublist)->getTail();
	    }
	}
      else if (term->isAtom() || term->isNumber())
	{
	  sublist = AtomTable::nil;
	  return; // can't be altered by subst
	}
      else
	{
	  return;
	}
    }
  return;
}










