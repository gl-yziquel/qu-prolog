// user_hash_table_escapes.cc - Interface to user hash table.
//
// ##Copyright##
// 
// Copyright (C) 2000-Tue May 12 09:17:22 AEST 2015 
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
// $Id: user_hash_table_escapes.cc,v 1.1 2006/01/31 23:19:09 qp Exp $

#include "user_hash_table.h"
#include "code.h"
#include "thread_qp.h"

extern Code *code;

extern UserHashState* user_hash;

//
// psi_user_ht_insert(Fst, Snd, Data)
// Insert Data into the user hash table indexed by Fst and Snd
//
// mode(in,in,in)

Thread::ReturnValue 
Thread::psi_user_ht_insert(Object *& fst_obj, Object *& snd_obj, 
			   Object *& data_obj)
{
  Object* fst = fst_obj->variableDereference();
  Object* snd = snd_obj->variableDereference();
  Object* data = data_obj->variableDereference();
  if (!fst->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (!snd->isAtom() && !snd->isInteger()) 
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  user_hash->addEntry(fst, snd, data, TheHeap());
  code->Stamp();
  return RV_SUCCESS;

}

//
// psi_user_ht_lookup(Fst, Snd, Data)
// Lookup Data in the user hash table indexed by Fst and Snd
//
// mode(in,in,out)

Thread::ReturnValue 
Thread::psi_user_ht_lookup(Object *& fst_obj, Object *& snd_obj, 
			   Object *& data)
{
  Object* fst = fst_obj->variableDereference();
  Object* snd = snd_obj->variableDereference();
  if (!fst->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (!snd->isAtom() && !snd->isInteger()) 
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  bool result = user_hash->lookupEntry(fst, snd, data, TheHeap());
  return BOOL_TO_RV(result);
}

//
// psi_user_ht_remove(Fst, Snd)
// Remove entry in the user hash table indexed by Fst and Snd
//
// mode(in,in)
Thread::ReturnValue 
Thread::psi_user_ht_remove(Object *& fst_obj, Object *& snd_obj)
{
  Object* fst = fst_obj->variableDereference();
  Object* snd = snd_obj->variableDereference();
  if (!fst->isAtom())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (!snd->isAtom() && !snd->isInteger()) 
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }
  user_hash->removeEntry(fst, snd);
  code->Stamp();
  return RV_SUCCESS;
}


//
// psi_user_ht_search(Fst, Snd, Data)
// Collect together all entries in the hash table that match
// Fst and Snd. Data is a list of elements of the form '$'(F,S,T)
//
// mode(in,in,out)

Thread::ReturnValue 
Thread::psi_user_ht_search(Object *& fst_obj, Object *& snd_obj, 
			   Object *& data)
{
  Object* fst = fst_obj->variableDereference();
  Object* snd = snd_obj->variableDereference();
  if (!fst->isAtom() && !fst->isVariable())
    {
      PSI_ERROR_RETURN(EV_TYPE, 1);
    }
  if (!snd->isAtom() && !snd->isInteger() && !snd->isVariable()) 
    {
      PSI_ERROR_RETURN(EV_TYPE, 2);
    }

  user_hash->hashIterReset();

  data =  AtomTable::nil;

  Object *fst1, *snd1, *t1;
  while (user_hash->hashIterNext(fst1, snd1, t1, TheHeap()))
    {
      if ((fst->isVariable() || fst->equalConstants(fst1))
	  &&
	  (snd->isVariable() || snd->equalConstants(snd1)))
	{
	  Structure* term = TheHeap().newStructure(3);
	  term->setFunctor(AtomTable::dollar);
	  term->setArgument(1, fst1);
	  term->setArgument(2, snd1);
	  term->setArgument(3, t1);

	  Object* tmp = TheHeap().newCons(term, data);
	  data = tmp;
	}
    }
  return RV_SUCCESS;
}
