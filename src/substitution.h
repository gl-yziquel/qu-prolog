// substitution.h - Contains a set of functions for dealing
//		    with Qu-Prolog substitution. 
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
// $Id: substitution.h,v 1.3 2002/03/13 01:38:25 qp Exp $

#ifndef	SUBSTITUTION_H
#define	SUBSTITUTION_H

//
// Throughout the comments relating to substitutions - substituted terms
// are represented as s1 * s2 * s3 ... * sn * t where si are substitution
// blocks. When the substitutions are collected together (as after dereference)
// then they are represented as a list. Because the right most sub block 
// applies to the term first then the list of substitution blocks has the
// the rightmost sub at the head and the left most at the tail.
// Also substitution blocks are represented as [tn/xn, ..., t1/x1]
// in comments and the t1/x1 applies first and so in the datastructure
// representing blocks t1, x1 is the first range, domain pair.
//

public:
//
// Copy the spine of a sequence of substitutions up to the stop point.
// tail specifies the new tail of copied version.
//
Object *copySubSpine(Object *sub_block_list1,
		     Object *sub_block_list2,
		     Object *sub_block_list3);

// 
// Split a sequence of substitutions at a specified point and return the
// right part.
// For example:
//	sub			= s1 * ... * si * sj * sk * ... * sn 
//	SplitPoint		= sj 
//	SplitSubstitution	= sk * ... * sn 
// 
inline Object *splitSubstitution(Object *sub_list, Object *split_point)
{
  DEBUG_ASSERT(sub_list->isList() && split_point->isList());
  DEBUG_ASSERT(sub_list->isNil() || OBJECT_CAST(Cons*, sub_list)->isSubstitutionBlockList());
  DEBUG_ASSERT(split_point->isNil() || OBJECT_CAST(Cons*, split_point)->isSubstitutionBlockList());

  return copySubSpine(sub_list, split_point, AtomTable::nil);
}

// 
// Remove a specified substitution from a sequence of substitutions.
// For example:
//	sub			= s1 * ... * si * sj * sk * ... * sn 
//	unwanted		= sj 
//	RemoveSubstitution	= s1 * ... * si * sk * ... * sn 
// 
inline Object* removeSubstitution(Object *sub_list, Object *unwanted)
{
  DEBUG_ASSERT(sub_list->isList() && unwanted->isCons());
  DEBUG_ASSERT(sub_list->isNil() || OBJECT_CAST(Cons*, sub_list)->isSubstitutionBlockList());
  DEBUG_ASSERT(OBJECT_CAST(Cons*, unwanted)->isSubstitutionBlockList());

  return copySubSpine(sub_list, unwanted, OBJECT_CAST(Cons*,unwanted)->getTail());
}

//
// Invert substitution.
//
bool invert(Thread&, Object *sub_block_list, PrologValue& term);

//
// Used to invert sub to transform sub * x not_free_in term into
// x not_free_in sub-1 * term .
//
// NOTE: no extra not_free_in conditions are added.
//
void invertWithoutNFI(Object *sub_block_list, PrologValue&);

//
// If a term has a non-empty substitution, create a new SUBSTITUTION_OPERATOR
// and assign substitution and term. If term has an empty substitution then
// just return the term part.
//
Object *prologValueToObject(PrologValue&);

//
// Check whether the object variable occurs as the most right range
// in any substitution from the composition of substitutions.
//
bool isLocalInRange(Object *, Object *sub_block_list);

//
// Copy the rightmost substitution table before any destructive processing is
// performed.  The range elements are replaced by $'s.
//
Object *copySubstitutionBlockWithDollars(Object *sub_block_list, size_t);

bool canRemove(Thread&, Object*, int, 
	       SubstitutionBlock**, Object*);
//
// Remove useless entry from a substitution wherever it is possible.
// Assumed to be (Prolog) dereferenced.
//
void dropSubFromTerm(Thread&, PrologValue&);

#endif	// SUBSTITUTION_H

