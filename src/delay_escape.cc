// delay_escape.cc - General delay mechanism.
//
// ##Copyright##
// 
// Copyright (C) 2000-2004
// School of Information Technology and Electrical Engineering
// The University of Queensland
// Australia 4072
// 
// email: pjr@itee.uq.edu.au
// 
// The Qu-Prolog System and Documentation  
// 
// COPYRIGHT NOTICE, LICENCE AND DISCLAIMER.
// 
// Copyright 2000-2004 by The University of Queensland, 
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
// 	written consent from the ITEE; and
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
// For information on commercial use of this software contact ITEE.
// 
// ##Copyright##
//
// $Id: delay_escape.cc,v 1.6 2005/11/26 23:34:29 qp Exp $

//#include "atom_table.h"
#include "global.h"
#include "thread_qp.h"

//
// psi_delay(variable, term)
// Delay the call to term and associate the problem with variable.
// mode(in,in)
//
Thread::ReturnValue
Thread::psi_delay(Object *& object1, Object *& object2)
{
  assert(object1->variableDereference()->hasLegalSub());
  assert(object2->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  Object* val2 = heap.dereference(object2);
  
  assert(val1->isAnyVariable());
  
  //
  // Delay the problem.
  //
  delayProblem(val2, val1);
  
  //
  // Complete operation.
  //
  return(RV_SUCCESS);
}

//
// psi_delayed_problems_for_var(variable, term)
// Return the list of delayed problems associated with the given variable.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_delayed_problems_for_var(Object *& object1, Object *& object2)
{
  Object* o = object1;
  Object* delays = AtomTable::nil;

  assert(o != NULL);
  
  while (o->isAnyVariable()) 
    {
      delays = OBJECT_CAST(Reference*, o)->getDelays();
      Object* n = OBJECT_CAST(Reference*, o)->getReference();
      if ((n == o) || !delays->isNil())
	{
	  object2 = delays;
	  return(RV_SUCCESS);
	}
      o = n;
    }
  object2 = delays;
  return(RV_SUCCESS);
}

//
// psi_get_bound_structure(variable, variable)
// Return the dereferenced variable as the argument of a "bound" structure.
// mode(in,out)
//
Thread::ReturnValue
Thread::psi_get_bound_structure(Object *& object1, Object *& object2)
{

  assert(object1->variableDereference()->hasLegalSub());
  Object* val1 = heap.dereference(object1);
  
  assert(val1->isAnyVariable());
  if (val1->isVariable())
    {
      val1 = addExtraInfo(OBJECT_CAST(Variable*, val1));
    }
  Structure* newstruct = heap.newStructure(1);
  newstruct->setFunctor(atoms->add("bound"));
  newstruct->setArgument(1,val1);
  Structure* boundstruct = heap.newStructure(1);
  boundstruct->setFunctor(atoms->add("$bound"));
  boundstruct->setArgument(1,newstruct);

  object2 = boundstruct;
  return(RV_SUCCESS);
}

//
// psi_psidelay_resume
// Restore the thread state after a retry delay from a pseudo instruction
// mode()
//
Thread::ReturnValue
Thread::psi_psidelay_resume(void)
{
  assert(false);
  status.resetNeckCutRetry();
  RestoreXRegisters();
  programCounter = savedPC;
  return(RV_SUCCESS);
}


//
// psi_get_delays(delays,type,avoid)
// Return the list of delayed problems of given type
// type is 'all' or 'unify' other than those in avoid.
// mode(out,in,in)
// 

Thread::ReturnValue
Thread::psi_get_delays(Object *& delaylist, Object*& type, Object*& avoid)
{
  bool unify_only = (type->variableDereference() == atoms->add("unify"));
  Object *delays = AtomTable::nil;
  Object *avoid_list = avoid->variableDereference();


  for (Object *global_delays = 
	 ipTable.getImplicitPara(AtomTable::delays)->variableDereference();
       global_delays->isCons();
       global_delays = OBJECT_CAST(Cons *, global_delays)->getTail()->variableDereference())
    {
      assert(OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference()->isStructure());

      Structure *delay
	= OBJECT_CAST(Structure*, OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference());

      assert(delay->getArity() == 2);
      Object* status = delay->getArgument(1)->variableDereference();
      if (!status->isVariable() || !OBJECT_CAST(Variable*,status)->isFrozen())
	{
	  continue;
	}
      Object* var = delay->getArgument(2);
      Object* vdelays;
      (void)psi_delayed_problems_for_var(var, vdelays);
      for (; vdelays->isCons(); 
	   vdelays = OBJECT_CAST(Cons*, 
				 vdelays)->getTail()->variableDereference())
	{
	  Object* vd = 
	    OBJECT_CAST(Cons*, vdelays)->getHead()->variableDereference();
	  assert(vd->isStructure());
	  Structure* vdstruct = OBJECT_CAST(Structure *, vd);
	  assert(vdstruct->getArity() == 2);
	  Object* vdstatus = vdstruct->getArgument(1)->variableDereference();
	  assert(vdstatus->isVariable());
	  if (!OBJECT_CAST(Variable*,vdstatus)->isFrozen())
	    {
	      continue;
	    }
	  Object* problem = vdstruct->getArgument(2)->variableDereference();
          if (avoid_list->inList(problem))
	    {
	      continue;
	    }
	  if (unify_only)
	    {
	      if (!problem->isStructure())
		{
		  continue;
		}
	      Structure* pstruct = OBJECT_CAST(Structure*, problem);
	      if (pstruct->getArity() == 2 && 
		  pstruct->getFunctor() == AtomTable::equal)
		{
		  delays = heap.newCons(problem, delays);
		}
	    }
	  else
	    {
	      if (!problem->isStructure())
		{
		  delays = heap.newCons(problem, delays);
		}
	      else
		{
		  Structure* pstruct = OBJECT_CAST(Structure*, problem);
		  if (pstruct->getArity() == 2 &&
		      pstruct->getFunctor() == atoms->add("delay_until") &&
		      pstruct->getArgument(1)->variableDereference()->isStructure())
		    {
		      Structure* arg1struct = OBJECT_CAST(Structure*, pstruct->getArgument(1)->variableDereference());
		      if (arg1struct->getArity() == 1 &&
			  arg1struct->getFunctor() == atoms->add("$bound"))
			{
			  Structure* newpstruct = heap.newStructure(2);
			  newpstruct->setFunctor(pstruct->getFunctor());
			  newpstruct->setArgument(1,arg1struct->getArgument(1));
			  newpstruct->setArgument(2,pstruct->getArgument(2));
			  delays = heap.newCons(newpstruct, delays);
			  continue;
			}
		    }		      
		  delays = heap.newCons(problem, delays);
		}
	    }
	}
    }
  delaylist = delays;
  return RV_SUCCESS;
} 



//
// psi_bound(term)
// test if term is bound to something
// mode(in)
//
Thread::ReturnValue
Thread::psi_bound(Object *& object1)
{  
    Object* deref = object1->variableDereference();
    return BOOL_TO_RV(deref != object1);
}

//
// Remove any solved problems associated with any variables.
//
Thread::ReturnValue
Thread::psi_compress_var_delays()
{
  for (Object *global_delays = 
	 ipTable.getImplicitPara(AtomTable::delays)->variableDereference();
       global_delays->isCons();
       global_delays = OBJECT_CAST(Cons *, global_delays)->getTail()->variableDereference())
    {
      assert(OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference()->isStructure());
      
      Structure *delay = OBJECT_CAST(Structure*, OBJECT_CAST(Cons *, global_delays)->getHead()->variableDereference());
      
      assert(delay->getArity() == 2);
      Object* status = delay->getArgument(1)->variableDereference();
      if (!status->isVariable() || !OBJECT_CAST(Variable*,status)->isFrozen())
	{
	  continue;
	}
      // Get the variable with delays
      Reference* var = OBJECT_CAST(Reference*, delay->getArgument(2)->variableDereference());

      bool solved_found = false;
      Object* var_delays = var->getDelays();
      if (!var_delays->isNil())
	{
	  // Compress delay list
	  // Find the first delay to keep
	  for ( ; var_delays->isCons();
		var_delays = OBJECT_CAST(Cons *, var_delays)->getTail())
	    {
	      Structure *delay = 
		OBJECT_CAST(Structure *, 
			    OBJECT_CAST(Cons *, var_delays)->getHead());
	      Variable *delay_status = OBJECT_CAST(Variable*, 
					       delay->getArgument(1));
	      if (delay_status->isThawed())
		{
		  // Solved problem
		  solved_found = true;
		}
	      else
		{
		  break;
		}
	    }
	  if (solved_found)
	    {
	       updateAndTrailObject(reinterpret_cast<heapobject*>(var), 
				    var_delays, 
				    Reference::DelaysOffset);
	    }
	  // Scan the rest of the delay list
	  if (var_delays->isNil())
	    {
	      if (solved_found)
		{
		  updateAndTrailObject(reinterpret_cast<heapobject*>(var), 
				       var_delays, 
				       Reference::DelaysOffset);
		}
	      // Nothing to do
	      continue;
	    }
	  solved_found = false;
	  Object* look_ahead = OBJECT_CAST(Cons *, var_delays)->getTail();
	  for ( ; look_ahead->isCons();
		look_ahead = OBJECT_CAST(Cons *, look_ahead)->getTail())
	    {
	      Structure *delay = 
		OBJECT_CAST(Structure *, 
			    OBJECT_CAST(Cons *, look_ahead)->getHead());
	      Variable *delay_status = OBJECT_CAST(Variable*, 
					       delay->getArgument(1));
	      if (delay_status->isThawed())
		{
		  solved_found = true;
		}
	      else
		{
		  if (solved_found)
		    {
		      solved_found = false;
		      // point var_delays at next unsolved problem
		      updateAndTrailObject(reinterpret_cast<heapobject*>(var_delays), look_ahead, Cons::TailOffset);
		    }
		  var_delays = look_ahead;
		}
	    }
	  if (solved_found)
	    {
	      solved_found = false;
	      // point var_delays at next unsolved problem
	      updateAndTrailObject(reinterpret_cast<heapobject*>(var_delays), look_ahead, Cons::TailOffset);
	    }
	}
    }
  return RV_SUCCESS;
}

//
// Retry the delayed nfi problems.
//
Thread::ReturnValue
Thread::psi_retry_ov_delays(void)
{
  return BOOL_TO_RV(retry_delays(NFI));
}
//
// Retry the delayed nfi and = problems.
//
Thread::ReturnValue
Thread::psi_retry_ov_eq_delays(void)
{
  bool result = retry_delays(BOTH);
  if (result)
    {
       (void)psi_compress_var_delays();
       return RV_SUCCESS;
    }
  else
    {
       return RV_FAIL;
    }
}



