// objects.cc -
//
// ##Copyright##
// 
// Copyright (C) 2000-2010 
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
// $Id: objects.cc,v 1.6 2006/01/31 23:17:51 qp Exp $

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
  switch (tTag())
    {
    case tVar:
      return OBJECT_CAST(Variable *, this)->size();
      break;
    case tObjVar:
      return OBJECT_CAST(ObjectVariable *, this)->size();
      break;
    case tStruct:
      return OBJECT_CAST(Structure *, this)->size();
      break;
    case tCons:
      return Cons::size();
      break;
    case tQuant:
      return QuantifiedTerm::size();
      break;
    case tShort:
      return Short::size();
      break;
    case tLong:
      return Long::size();
      break;
    case tDouble:
      return Double::size();
      break;
    case tAtom:
      return Atom::size();
      break;
    case tString:
      return OBJECT_CAST(StringObject*, this)->size();
      break;
    case tSubst:
      return Substitution::size();
      break;
    case tSubBlock:
      return OBJECT_CAST(SubstitutionBlock *, this)->size();
      break;
    default:
      // Not all tTags considered!
      assert(false);
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
  assert(this->isObjectVariable());
  assert(OBJECT_CAST(const Reference*, this)->getReference() == 
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
  assert(this->isObjectVariable());
  assert(OBJECT_CAST(const Reference*, this)->getReference() == this);
  assert(objvar->isObjectVariable());
  assert(OBJECT_CAST(const Reference*, objvar)->getReference() == objvar);

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
  assert(this->isObjectVariable());
  assert(this == this->variableDereference());

  for ( ; i <= sub_block->getSize(); i++)
    {
      assert(sub_block->getDomain(i)->variableDereference()->isObjectVariable());

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
      assert(sub_block->getDomain(i)->isObjectVariable());
      
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
  assert(this->isLocalObjectVariable());
  assert(sub->isNil() || 
	 (sub->isCons() && 
	  OBJECT_CAST(Cons *, sub)->isSubstitutionBlockList()));
  
  bool    found = false;
  
  Object* end = AtomTable::nil;
  
  for (Object* s = sub; 
       s->isCons(); 
       s = OBJECT_CAST(Cons *, s)->getTail())
    {
      assert(OBJECT_CAST(Cons*, s)->getHead()->isSubstitutionBlock());
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

#ifdef QP_DEBUG
bool
Object::check_object()
{
  if ((tag & 1) == 0) return false;
  switch (tTag())
    {
    case Object::tVar:
      {
	Object* n  = OBJECT_CAST(Reference*, this)->getReference();
	if (n == this) return true;
	return ((n != NULL) && n->check_object());
      }
      break;
    case Object::tObjVar:
      {
	Object* n = OBJECT_CAST(Reference*, this)->getReference();
	if (n == this) return true;
	return ((n != NULL) && n->check_object());
      }
      break;
    case Object::tStruct:
      {
	Structure* s = OBJECT_CAST(Structure *, this);
	for (u_int i = 0; i <= s->getArity(); i++)
	  {
	    if (s->getArgument(i) == NULL || !s->getArgument(i)->check_object()) return false;
	  }
	return true;
      }
      break;
    case Object::tCons:
      {
	Cons* l = OBJECT_CAST(Cons *, this);
	return ((l->getHead() != NULL) && l->getHead()->check_object() && 
		(l->getTail() != NULL) && l->getTail()->check_object());
      }
      break;
    case Object::tQuant:
      {
	QuantifiedTerm* q = OBJECT_CAST(QuantifiedTerm *, this);
	return ((q->getQuantifier() != NULL) && 
		q->getQuantifier()->check_object() && 
		(q->getBoundVars() != NULL) &&
		q->getBoundVars()->check_object() && 
		(q->getBody() != NULL) &&
		q->getBody()->check_object());
      }
      break;
    case Object::tShort:
    case Object::tLong:
    case Object::tDouble:
    case Object::tAtom:
    case Object::tString:
      return true;
      break;
    case Object::tSubst:
      {
	Substitution* s = OBJECT_CAST(Substitution *, this);
	return((s->getTerm() != NULL) &&
	       s->getTerm()->check_object() && 
	       (s->getSubstitutionBlockList() != NULL) &&
	       s->getSubstitutionBlockList()->check_object());
      }
      break;
    case Object::tSubBlock:
      {
	SubstitutionBlock * s = OBJECT_CAST(SubstitutionBlock *, this);
	for (u_int i = 1; i <= s->getSize(); i++)
	  {
	    if ((s->getDomain(i) == NULL) ||
		!s->getDomain(i)->check_object() || 
		(s->getRange(i) == NULL) ||
		!s->getRange(i)->check_object() )return false;
	  }
	return true;
      }
      break;
    default:
      return false;
    }
}
#endif






