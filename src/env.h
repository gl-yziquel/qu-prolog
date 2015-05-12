//
// env.h - Contains a set of functions which can be used for
// 	     assessing the overall tasks such as setting flags,
//           call another functions and print out the statistics.
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
// $Id: env.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $


#ifndef ENV_H
#define ENV_H

private:
ReturnValue call_predicate(int32 noargs, ...);

public:

//
// psi_uncurry(term1, term2).
// Flattens (uncurries) term1 to term2.
// mode(in,out)
//
ReturnValue psi_uncurry(Object *& , Object *& );

//
// psi_set_flag(integer, integer).
// Sets internal system flag.
// mode(in,in)
//
ReturnValue psi_set_flag(Object *& , Object *& );

//
// psi_get_flag(integer, variable).
// Gets internal system flag.
// mode(in,out)
//
ReturnValue psi_get_flag(Object *& , Object *& );

ReturnValue psi_make_cleanup_cp(Object *& );

//
// psi_call_predicate(structure,..args...)
// These functions execute the nonvariable term as the term
// itself in the program text with arguments ...args....
// mode(in)
// mode(in,in)
// mode(in,in,in)
// mode(in,in,in,in)
// 
ReturnValue psi_call_predicate0(Object *&);
ReturnValue psi_call_predicate1(Object *&, Object *&);
ReturnValue psi_call_predicate2(Object *&, Object *&, Object *&);
ReturnValue psi_call_predicate3(Object *&, Object *&, Object *&, Object *&);
ReturnValue psi_call_predicate4(Object *&, Object *&, Object *&, Object *&, Object *&);

#if 0
// 
// psi_call_clause(address, term)
// Execute a clause from address and use the term as query.  This is used for
// decompiling a dynamic clause.
// mode(in,in)
//
ReturnValue psi_call_clause(Object *& , Object *& );
#endif // 0

//
// psi_get_qplibpath(variable).
// This functionn returns the path for 
// files to the variable.
// mode(out)
//
ReturnValue psi_get_qplibpath(Object *& );

//
// Get hold of the value of the environment variable QPLIBPATH.
//
void	InitQPLibPath(void);

#endif	// ENV_H

