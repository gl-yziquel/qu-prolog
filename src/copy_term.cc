// copy_term.cc - Functions for copy terms from heap to heap.
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
// $Id: copy_term.cc,v 1.6 2002/11/08 00:44:15 qp Exp $

#include "heap_qp.h"

#include <list>

Object*
Heap::copy_var(Object* source_var,
	       Heap& target_heap, 
	       list<VarRec *>& var_rec_list)
{
  // Determine if we've seen this variable before.
  heapobject* target_loc = NULL;
  // Scan down the list of variable records.
  for (list<VarRec *>::iterator iter = var_rec_list.begin();
       iter != var_rec_list.end();
       iter++)
    {
      if ((*iter)->sourceLoc() == reinterpret_cast<heapobject*>(source_var))
	{
	  target_loc = (*iter)->targetLoc();
	  break;
	}
    }

  // If we haven't seen this variable before...
  if (target_loc == NULL)
    {
      // Record its location in the target heap.
      VarRec *var_rec = new VarRec(reinterpret_cast<heapobject*>(source_var),
				   target_heap.getTop());
      
      var_rec_list.push_back(var_rec);

      Variable* target_var = target_heap.newVariable();
      if (OBJECT_CAST(Variable*, source_var)->isOccursChecked())
	{
	  target_var->setOccursCheck();
	}
      return(target_var);
    }
  else
    {
      DEBUG_ASSERT(reinterpret_cast<Object*>(target_loc)->isVariable());
      return(reinterpret_cast<Object*>(target_loc));
    }
}

Object*
Heap::copy_object_variable(Object* source_object_variable,
			   Heap& target_heap,
			   list<VarRec *>& object_variable_rec_list)
{
  // Determine if we've seen this variable before.
  heapobject* target_loc = NULL;

  // Scan down the list of variable records.
  for (list<VarRec *>::iterator iter = object_variable_rec_list.begin();
       iter != object_variable_rec_list.end();
       iter++)
    {
      if ((*iter)->sourceLoc() == reinterpret_cast<heapobject*>(source_object_variable))
	{
	  target_loc = (*iter)->targetLoc();
	  break;
	}
    }

  // If we haven't seen this variable before...
  if (target_loc == NULL)
    {
      // Record its location in the target heap.
      VarRec *object_variable_rec 
	= new VarRec(reinterpret_cast<heapobject*>(source_object_variable),
		     target_heap.getTop());
      
      object_variable_rec_list.push_back(object_variable_rec);

      return(target_heap.newObjectVariable());

    }
  else
    {
      DEBUG_ASSERT(reinterpret_cast<Object*>(target_loc)->isObjectVariable());
      return(reinterpret_cast<Object*>(target_loc));
    }
}


Object*
Heap::copy_subblock(Object* source_term, Heap& target_heap,
		    list<VarRec *>& var_rec_list,
		    list<VarRec *>& object_variable_rec_list)
{
  DEBUG_ASSERT(source_term->isSubstitutionBlock());
  
  SubstitutionBlock* source_block = OBJECT_CAST(SubstitutionBlock*,
						source_term);
  SubstitutionBlock* target_block
    = target_heap.newSubstitutionBlock(source_block->getSize());

  for (size_t i = 1; i <= source_block->getSize(); i++)
    {
      Object* domain = source_block->getDomain(i)->variableDereference();
      target_block->setDomain(i,
			      copy_object_variable(domain,
						   target_heap,
						   object_variable_rec_list));
      target_block->setRange(i, copy_term(source_block->getRange(i),
					  target_heap,
					  var_rec_list,
					  object_variable_rec_list));
    }
  return(target_block);
}


Object*
Heap::copy_term(Object* source_term, Heap& target_heap,
		list<VarRec *>& var_rec_list,
		list<VarRec *>& object_variable_rec_list)
{

  DEBUG_ASSERT(source_term->variableDereference()->hasLegalSub());
  source_term = dereference(source_term);

  switch(source_term->utag())
    {
    case Object::uVar:
      return(copy_var(source_term, target_heap, var_rec_list));
      break;

    case Object::uObjVar:
      return(copy_object_variable(source_term, target_heap,
				  object_variable_rec_list));
      break;

    case Object::uCons:
      {
	if (OBJECT_CAST(Cons*, source_term)->isSubstitutionBlockList())
	  {
	    //
	    // The list is a substitution block list so make a copy
	    //
	    Cons* target_term = target_heap.newCons();
	    Object** tail_ref = target_term->getTailAddress();
	    target_term->makeSubstitutionBlockList();
	    target_term->setHead(copy_subblock(OBJECT_CAST(Cons*,  source_term)->getHead(),
					       target_heap,
					       var_rec_list,
					       object_variable_rec_list));
	    for (source_term 
		   = dereference(OBJECT_CAST(Cons*, source_term)->getTail());
		 source_term->isCons();
		 source_term 
		   = dereference(OBJECT_CAST(Cons*, source_term)->getTail()))
	      {
		
		Cons* cons = target_heap.newCons();
		cons->makeSubstitutionBlockList();
		cons->setHead(copy_subblock(OBJECT_CAST(Cons*, source_term)->getHead(),
					target_heap,
					var_rec_list, 
					object_variable_rec_list));
		*tail_ref = cons;
		tail_ref = cons->getTailAddress();
	      }
	    DEBUG_ASSERT(source_term == AtomTable::nil);
	    *tail_ref = AtomTable::nil;
	    return(target_term);
	  }
	//
	// A list that is not a substitution block list
	//
	Cons* target_term = target_heap.newCons();
	Object** tail_ref = target_term->getTailAddress();
	target_term->setHead(copy_term(OBJECT_CAST(Cons*, source_term)->getHead(), 
				       target_heap,
				       var_rec_list,
				       object_variable_rec_list));

	
	for (source_term 
	       = dereference(OBJECT_CAST(Cons*, source_term)->getTail());
	     source_term->isCons();
	     source_term 
	       = dereference(OBJECT_CAST(Cons*, source_term)->getTail()))
	  {

	    Cons* cons = target_heap.newCons();
	    cons->setHead(copy_term(OBJECT_CAST(Cons*, source_term)->getHead(),
				    target_heap,
				    var_rec_list, object_variable_rec_list));
	    *tail_ref = cons;
	    tail_ref = cons->getTailAddress();
	  }
	
	*tail_ref = copy_term(source_term,  target_heap,
			      var_rec_list, object_variable_rec_list);
	return(target_term);
	break;
      }

    case Object::uStruct:
      {
	Structure* source_struct = OBJECT_CAST(Structure*, source_term);
	Structure* target_term
	  = target_heap.newStructure(source_struct->getArity());
	
	heapobject* source_storage = source_term->storage();
	heapobject* target_storage = target_term->storage();

	for (size_t i = 0; i <= source_struct->getArity(); i++)
	  {
	    *target_storage =  reinterpret_cast<heapobject>
	      (copy_term(reinterpret_cast<Object*>(*source_storage),
			 target_heap, 
			 var_rec_list,
			 object_variable_rec_list));
	    target_storage++;
	    source_storage++;
	  }
	return(target_term);
	break;
      }

    case Object::uQuant:
      {
	QuantifiedTerm* source_quant 
	  = OBJECT_CAST(QuantifiedTerm*, source_term);

	QuantifiedTerm* target_quant = target_heap.newQuantifiedTerm();

	target_quant->setQuantifier(copy_term(source_quant->getQuantifier(),
					      target_heap,
					      var_rec_list,
					      object_variable_rec_list));
	target_quant->setBoundVars(copy_term(source_quant->getBoundVars(),
					     target_heap,
					     var_rec_list,
					     object_variable_rec_list));
	target_quant->setBody(copy_term(source_quant->getBody(),
					target_heap,
					var_rec_list,
					object_variable_rec_list));
	return(target_quant);
	break;
      }

    case Object::uConst:
      {
	if (source_term->isAtom())
	  {
	    return(source_term);
	  }
	else
	  {
	    DEBUG_ASSERT(source_term->isNumber());
	    return(target_heap.newNumber(source_term->getNumber()));
	  }
	break;
      }

    case Object::uSubst:
      {
	Substitution* source_sub = OBJECT_CAST(Substitution*, source_term);
	
	Substitution* target_term = target_heap.newSubstitution();
	target_term->setTerm(copy_term(source_sub->getTerm(),
				       target_heap, var_rec_list,
				       object_variable_rec_list));
	Object* temp = copy_term(source_sub->getSubstitutionBlockList(), 
				 target_heap,
				 var_rec_list,
				 object_variable_rec_list);
        DEBUG_ASSERT(temp->isCons());
	target_term->setSubstitutionBlockList(temp);

	return(target_term);
	break;
      }

    default:
      DEBUG_ASSERT(false);
      return source_term;
      break;
    }
}


Object*
Heap::copy_share_subblock(Object* source_term, Heap& target_heap,
		    const heapobject* low, const heapobject* high)
{
  DEBUG_ASSERT(source_term->isSubstitutionBlock());
  
  SubstitutionBlock* source_block = OBJECT_CAST(SubstitutionBlock*,
						source_term);
  SubstitutionBlock* target_block
    = target_heap.newSubstitutionBlock(source_block->getSize());

  for (size_t i = 1; i <= source_block->getSize(); i++)
    {
      Object* domain = source_block->getDomain(i)->variableDereference();
      target_block->setDomain(i, domain);
      target_block->setRange(i, copy_share_term(source_block->getRange(i),
						target_heap,
						low, high));
    }
  return(target_block);
}

 
//
// Copy a term to a heap. This function is used by simplify_term to copy
// substitutions from one heap to another. Terms between low and high
// are shared. It is assumed that if a term is between low and high then 
// all its subterms that are either between low and high or do not point
// to any heap (e.g.atoms).
// Low will be set to the base of the heap in which simplification is being
// done. High is set to the top of the heap at the time when simplification
// is called.
//
Object*
Heap::copy_share_term(Object* source_term, Heap& target_heap,
		      const heapobject* low, const heapobject* high)
{

  DEBUG_ASSERT(source_term->variableDereference()->hasLegalSub());
  source_term = dereference(source_term);

#ifndef DEBUG
  if (reinterpret_cast<heapobject*>(source_term) < high &&
      reinterpret_cast<heapobject*>(source_term) >= low)
    {
      return(source_term);
    }
#endif // DEBUG

  //
  // some copying required
  //
  switch(source_term->utag())
    {
    case Object::uVar:
    case Object::uObjVar:
      DEBUG_ASSERT(reinterpret_cast<heapobject*>(source_term) < high &&
                   reinterpret_cast<heapobject*>(source_term) >= low);
      return(source_term);
      break;
    case Object::uConst:
      return(source_term);
      break;

    case Object::uCons:
      {
	
	if (OBJECT_CAST(Cons*, source_term)->isSubstitutionBlockList())
	  {
	    //
	    // The list is a substitution block list so make a copy
	    //
	    // There should only be one substitution.
	    //
	    Cons* target_term = target_heap.newCons();
	    target_term->makeSubstitutionBlockList();
	    target_term->setHead(copy_share_subblock(OBJECT_CAST(Cons*,  source_term)->getHead(),
					       target_heap,
					       low, high));
  DEBUG_ASSERT(OBJECT_CAST(Cons*, source_term)->getTail()->variableDereference()->hasLegalSub());
	    source_term 
		   = dereference(OBJECT_CAST(Cons*, source_term)->getTail());
		
	    DEBUG_ASSERT(source_term == AtomTable::nil);
	    target_term->setTail(AtomTable::nil);
	    return(target_term);
	  }
	//
	// A list that is not a substitution block list
	//
	Cons* target_term = target_heap.newCons();
	Object** tail_ref = target_term->getTailAddress();
	target_term->setHead(copy_share_term(OBJECT_CAST(Cons*, source_term)->getHead(), 
				       target_heap, low, high));
	
	for (source_term 
	       = dereference(OBJECT_CAST(Cons*, source_term)->getTail());
	     source_term->isCons();
	     source_term 
	       = dereference(OBJECT_CAST(Cons*, source_term)->getTail()))
	  {

	    Cons* cons = target_heap.newCons();
	    cons->setHead(copy_share_term(OBJECT_CAST(Cons*, source_term)->getHead(),
				    target_heap, low, high));
	    *tail_ref = cons;
	    tail_ref = cons->getTailAddress();
	  }
	
	*tail_ref = copy_share_term(source_term,  target_heap, low, high);
	return(target_term);
	break;
      }

    case Object::uStruct:
      {
	Structure* source_struct = OBJECT_CAST(Structure*, source_term);
	Structure* target_term
	  = target_heap.newStructure(source_struct->getArity());
	
	heapobject* source_storage = source_term->storage();
	heapobject* target_storage = target_term->storage();

	for (size_t i = 0; i <= source_struct->getArity(); i++)
	  {
	    *target_storage =  reinterpret_cast<heapobject>
	      (copy_share_term(reinterpret_cast<Object*>(*source_storage),
			       target_heap, low, high));

	    target_storage++;
	    source_storage++;
	  }
	return(target_term);
	break;
      }

    case Object::uQuant:
      {
	QuantifiedTerm* source_quant 
	  = OBJECT_CAST(QuantifiedTerm*, source_term);

	QuantifiedTerm* target_quant = target_heap.newQuantifiedTerm();

	target_quant->setQuantifier(copy_share_term(source_quant->getQuantifier(),
						    target_heap, low, high));

	target_quant->setBoundVars(copy_share_term(source_quant->getBoundVars(),
					     target_heap, low, high));

	target_quant->setBody(copy_share_term(source_quant->getBody(),
					target_heap, low, high));

	return(target_quant);
	break;
      }

    case Object::uSubst:
      {
	Substitution* source_sub = OBJECT_CAST(Substitution*, source_term);
	
	Substitution* target_term = target_heap.newSubstitution();
	target_term->setTerm(copy_share_term(source_sub->getTerm(),
					     target_heap, low, high));
	Object* temp = copy_share_term(source_sub->getSubstitutionBlockList(), 
				       target_heap, low, high);

        DEBUG_ASSERT(temp->isCons());
	target_term->setSubstitutionBlockList(temp);

	return(target_term);
	break;
      }

    default:
      DEBUG_ASSERT(false);
      return source_term;
      break;
    }
}

Object*
Heap::copyTerm(Object* source_term, Heap& target_heap)
{
  list<VarRec *> var_rec_list;
  list<VarRec *> object_variable_rec_list;

  Object* result =  
       copy_term(source_term, target_heap, 
		 var_rec_list, object_variable_rec_list);
  for (list<VarRec *>::iterator iter = var_rec_list.begin();
       iter != var_rec_list.end();
       iter++)
    {
      delete *iter;
    }
  for (list<VarRec *>::iterator iter = object_variable_rec_list.begin();
       iter != object_variable_rec_list.end();
       iter++)
    {
      delete *iter;
    }
  return result;
}

Object*
Heap::copyShareTerm(Object* source_term, Heap& target_heap,
		   const heapobject* low, const heapobject* high)
{
  return (copy_share_term(source_term, target_heap, low, high));
}








