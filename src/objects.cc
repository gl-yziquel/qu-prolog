// objects.cc -
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
// $Id: objects.cc,v 1.3 2002/11/03 08:37:29 qp Exp $

#include "objects.h"

using namespace std;

// The next best thing to generic dispatching

size_t Object::size_dispatch(void)
{
  if (this == NULL)
    {
      cerr << "Warning - size of NULL" << endl;
      return(0);
    }
  switch (utag())
    {
    case uVar:
      return OBJECT_CAST(Variable *, this)->size();
      break;
    case uObjVar:
      return OBJECT_CAST(ObjectVariable *, this)->size();
      break;
    case uStruct:
      return OBJECT_CAST(Structure *, this)->size();
      break;
    case uCons:
      return Cons::size();
      break;
    case uQuant:
      return QuantifiedTerm::size();
      break;
    case uConst:
      if (isAtom ())
	return Atom::size();
      if (isShort ())
	return Short::size();
      else if (isLong ())
	return Long::size();
#if 0
      else if (isFloat())
	return Float::size();
#endif
      else
	{
	  DEBUG_ASSERT(false);
	  return 0;
	}
      break;
    case uSubst:
      return Substitution::size();
      break;
    case uSubsBlock:
      return OBJECT_CAST(SubstitutionBlock *, this)->size();
      break;
    default:
      // Not all uTags considered!
      DEBUG_ASSERT(false);
      return 0;
    }
}

//
// Check whether the object variable is in the distinctness information list.
// NOTE:
//	ObjectVariable should be dereferenced before this function is called.
//
bool
Object::isObjectVariableInDistinctList(const ObjectVariable *objvar) const
{
  DEBUG_ASSERT(this->isObjectVariable());
  DEBUG_ASSERT(OBJECT_CAST(const Reference*, this)->getReference() == 
	       OBJECT_CAST(const Object*, this));

  for (Object *distinct = objvar->getDistinctness(); 
       distinct->isCons(); 
       distinct = OBJECT_CAST(Cons *, distinct)->getTail())
    {
      Object *term = 
	OBJECT_CAST(Cons *, distinct)->getHead()->variableDereference();
      if (term == this)
	{
	  return true;
	}
    }

  return false;
}

//
// Check whether two object variables are distinct. 
// Return true if object variables are known to be distinct.
// NOTE:
//	ObjectVariable1 and ObjectVariable2 should be dereferenced 
//	before this function is called.
//
bool
Object::distinctFrom(const Object *objvar) const 
{
  DEBUG_ASSERT(this->isObjectVariable());
  DEBUG_ASSERT(OBJECT_CAST(const Reference*, this)->getReference() == this);
  DEBUG_ASSERT(objvar->isObjectVariable());
  DEBUG_ASSERT(OBJECT_CAST(const Reference*, objvar)->getReference() == objvar);

  if (this == objvar)
    {
      return false;
    }
  else if (this->isLocalObjectVariable() || 
	   objvar->isLocalObjectVariable())
    {
      return true;
    }
  else
    {
      return isObjectVariableInDistinctList(OBJECT_CAST(const ObjectVariable*, 
							objvar));
    }
}

//
// The function returns true if the object_variable is distinct from
// all domains in the i-th to SubSize-th entry of the substitution.
// 
bool
Object::distinctFromDomains(const SubstitutionBlock *sub_block, size_t i)
{
  DEBUG_ASSERT(this->isObjectVariable());
  DEBUG_ASSERT(this == this->variableDereference());

  for ( ; i <= sub_block->getSize(); i++)
    {
      DEBUG_ASSERT(sub_block->getDomain(i)->isObjectVariable());

      ObjectVariable *domain 
	= OBJECT_CAST(ObjectVariable*, 
		      sub_block->getDomain(i)->variableDereference());

      if (! distinctFrom(domain))
	{
	  return false;
	}
    }

  return true;
}

//
// Return the length of the bound variables list.
//
size_t
Object::boundListLength(void)
{
  Object* list = this->variableDereference();
  
  size_t length = 0;
  
  while (list->isCons())
    {
      length++;
      
      list = OBJECT_CAST(Cons *, list)->getTail()->variableDereference();
      
    }
  
  return list->isNil() ? length : UINT_MAX;
}



//
// Check whether one of the domains contains the given object variable.
//
bool
ObjectVariable::isObjectVariableInDomain(SubstitutionBlock *sub_block)
{
  for (size_t i = sub_block->getSize(); i > 0; i--)
    {
      DEBUG_ASSERT(sub_block->getDomain(i)->isObjectVariable());
      
      ObjectVariable *dom = 
	OBJECT_CAST(ObjectVariable*, sub_block->getDomain(i)->variableDereference());
      
      if (this == dom)
	{
	  return true;
	}
    }
  
  return false;
}


//
// The substitution is scanned from right to left for the local object 
// variable on a domain or range place. If the last occurrence of the 
// local object variable is as a range element, then save the corresponding
// domain element and the new end of the substitution which 
// is one where local object variable is found.
//
bool
Object::containLocalObjectVariable(Object* sub, Object*& domElem, 
				   Object*& newEnd)
{
  DEBUG_ASSERT(this->isLocalObjectVariable());
  DEBUG_ASSERT(sub->isNil() || 
	       (sub->isCons() && 
	       OBJECT_CAST(Cons *, sub)->isSubstitutionBlockList()));
  
  bool    found = false;
  
  Object* end = AtomTable::nil;
  
  for (Object* s = sub; 
       s->isCons(); 
       s = OBJECT_CAST(Cons *, s)->getTail())
    {
      DEBUG_ASSERT(OBJECT_CAST(Cons*, s)->getHead()->isSubstitutionBlock());
      SubstitutionBlock *subblock = 
	OBJECT_CAST(SubstitutionBlock *, OBJECT_CAST(Cons *, s)->getHead());
      if (subblock->containsLocal())
	{
	  for (size_t i = 1; i <= subblock->getSize(); i++)
	    {
	      if (subblock->getDomain(i) == this)
		{
		  found = false;
		}
	      else if (subblock->getRange(i) == this)
		{
		  found = true;
		  end = s;
		  domElem = subblock->getDomain(i);
		}
	    }
	}
    }
  if (! found)
    {
      return(false);
    }
  else
    {
      newEnd = end;
    }
  return(true);
}








