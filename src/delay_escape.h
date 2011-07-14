// delay_escape.h - General delay mechanism.
//
// ##Copyright##
// 
// Copyright (C) 2000-2011 
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
// $Id: delay_escape.h,v 1.3 2001/09/20 03:22:05 qp Exp $

#ifndef	DELAY_ESCAPE_H
#define	DELAY_ESCAPE_H

public:
//
// psi_delay(variable, term)
// Delay the call to term and associate the problem with variable.
// mode(in,in)
//
ReturnValue	psi_delay(Object *& , Object *& );

//
// psi_delayed_problems_for_var(variable, term)
// Return the list of delayed problems associated with the given variable.
// mode(in,out)
//
ReturnValue	psi_delayed_problems_for_var(Object *& , Object *& );

//
// psi_get_bound_structure(variable, variable)
// Return the dereferenced variable as the argument of a "bound" structure.
// mode(in,out)
//
ReturnValue	psi_get_bound_structure(Object *& , Object *& );

//
// psi_psidelay_resume
// Restore the thread state after a retry delay from a pseudo instruction
// mode()
//
ReturnValue	 psi_psidelay_resume(void);

//
// psi_get_delays(delays,type,avoid)
// Return the list of delayed problems of given type
// type is 'all' or 'unify' other than those in avoid.
// mode(out,in,in)
// 

ReturnValue psi_get_delays(Object *&, Object*&, Object*&);

//
// psi_bound(term)
// test if term is bound to something
// mode(in)
//
ReturnValue psi_bound(Object *&);

//
// Remove any solved problems associated with any variables.
//
ReturnValue psi_compress_var_delays(void);


//
// Retry the delayed nfi problems.
//
ReturnValue psi_retry_ov_delays(void);

//
// Retry the delayed nfi and = problems.
//
ReturnValue psi_retry_ov_eq_delays(void);

#endif	// DELAY_ESCAPE_H
