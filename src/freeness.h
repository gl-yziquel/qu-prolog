// freeness.h - has two components:
//               a.  freeness test returns no, unsure, yes.
//               b.  applies not_free_in constraints to terms.
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
// $Id: freeness.h,v 1.3 2002/03/13 01:38:25 qp Exp $

#ifndef	FREENESS_H
#define	FREENESS_H

private:

bool notFreeInStructure(ObjectVariable *, PrologValue&,
			bool gen_delays = true);

bool notFreeInList(ObjectVariable *, PrologValue&, bool gen_delays = true);

bool notFreeInQuantifier(ObjectVariable *, PrologValue&, 
			 bool gen_delays = true);


public:
//
// Check whether ObjectVariable is not free in the s*X.
// (X may be a variable or object variable)
//
bool notFreeInVar(ObjectVariable *, PrologValue&, bool gen_delays = true);

//
// Constrain object variable to be not free in the term.  Fails if free in.
// Succeeds if not free in.  Delays otherwise.
// Delayed not_free_in problems are generated where necessary.
//
bool notFreeIn(ObjectVariable *, PrologValue&, bool gen_delays = true);

//
// Not free in calls generated internally by the system can be of the form
// object_variable not_free_in term with object_variable of the form s*x and
// term having possible free locals.
//
bool internalNotFreeIn(PrologValue object_variable,
		       PrologValue term);

//
// Simplify the substitution associated with var and apply not free in.
//
bool notFreeInVarSimp(ObjectVariable *, PrologValue&);

//
// Add extra info to all variables appearing in the term.
// This is needed so that when simplifying terms new variables with extra
// info are not produced because, otherwise it will cause problems
// with term copying.
//
void addExtraInfoToVars(Object *term);

//
// Used in simplifying substitutions.
// Do trivial simplifications without resorting to simplify_term.
// "Complicated" constraints are ignored
//
bool notFreeInNFISimp(ObjectVariable*, PrologValue&);

//
// A C-level implementation of freeness_test.
// 
truth3 freeness_test(ObjectVariable*, PrologValue&);

//
// freeness_test_quant does the freeness test on a quantified term
//
truth3 freeness_test_quant(ObjectVariable*, PrologValue&);

//
// freeness_test_var does the freeness test on a var term
//
truth3 freeness_test_var(ObjectVariable*, PrologValue&);

//
// freeness_test_obvar does the freeness test on an obvar term
//
truth3 freeness_test_obvar(ObjectVariable*, PrologValue&);

//
// Carry out a quick test to see if an object var is NFI a term.
// USed by dropSub to remove subs where possible.
//

bool fastNFITerm(ObjectVariable*, Object*);

#endif	// FREENESS_H








