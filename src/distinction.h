// distinction.h - Contains a set of functions for dealing with distinctness 
//		   information associated with object variables.
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
// $Id: distinction.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef DISTINCTION_H
#define DISTINCTION_H


private:
void setDistinctObjectVariable(ObjectVariable *, ObjectVariable *);

bool distinctBoundList(ObjectVariable *, Object *bound_list);

public:
//
// Set two object variables to be distinct from each other.
//
void setDistinct(ObjectVariable *, ObjectVariable *);

//
// Check whether two object variables are distinct.
//
bool distinctFrom(Object *) const;

//
// Set all the range elements to be mutually disjoint from each other.
// Assume the ranges are newly created object variables.
//
void setMutualDistinctRanges(SubstitutionBlock *);

//
// If there is no distinctness information between the object variable
// and a domain, set the object variable to be distinct from the domain.
// Fail, if the object variable is equal to any domain.
// NOTE:
//      ObjectVariable should be dereferenced before this function is called.
//
bool generateDistinction(ObjectVariable *, Object *);

//
// The function returns true if the ObjectVariable is distinct from all domains
// in the i-th to SubSize-th entry of the substitution.
// 
bool distinctFromDomains(SubstitutionBlock *, size_t i);

//
// Ensure the object variables in the bound variable list are mutually 
// distinct.
//
bool checkBinder(Object *list, Object*);

//
// Return the length of the bound variables list.
//
size_t boundListLength(void);



#endif	// DISTINCTION_H









