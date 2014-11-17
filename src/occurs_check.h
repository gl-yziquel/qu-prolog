// occurs_check.h - 	Performing occurs check.
//
// ##Copyright##
// 
// Copyright (C) 2000-Mon Nov 17 15:45:58 AEST 2014 
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
// $Id: occurs_check.h,v 1.2 2002/08/25 23:35:10 qp Exp $

#ifndef	OCCURS_CHECK_H
#define	OCCURS_CHECK_H

public:
enum CheckType {ALL_CHECK, DIRECT};

private:
truth3 occursCheckSubAndSimplify(const CheckType type,
				 Object *sub_block_list,
				 Object*& simp_list, Object* var);

bool simpleOccursCheckSub(Object* subblock, Object* var);

truth3 simpleOccursCheck(Object* term, Object* var);


public:

truth3 occursCheckAndSimplify(const CheckType type, 
			      PrologValue& term, Object*& simpterm, 
			      Object* var);

//
// Check occurrence of variable in term. 
//
inline truth3 occursCheck(const CheckType type,
			  Object* variable, Object* term, Object*& simpterm)
{
  assert(variable->isVariable());
  if (OBJECT_CAST(Variable*, variable)->isOccursChecked() &&
      status.testOccursCheck())
    {
      truth3 result = simpleOccursCheck(term, variable);
      if (result == false)
	{
	  simpterm = term;
	  return false;
	}
      else if (result == true)
	{
	  simpterm = term;
	  return true;
	}
      PrologValue pt(term);
      Object* var = variable->variableDereference();
      return(occursCheckAndSimplify(type, pt, simpterm, var));
    }
  else
    {
      //
      // Do not perform occurs check.
      //
      simpterm = term;
      return false;
    }
}

inline truth3 occursCheckPV(const CheckType type,
			    Object* variable, PrologValue& term, 
			    Object*& simpterm)
{
  Object* oterm =  heap.prologValueToObject(term);
  return occursCheck(type, variable, oterm, simpterm);
}

#endif	// OCCURS_CHECK_H


