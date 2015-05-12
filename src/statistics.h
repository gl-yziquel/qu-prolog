// statistics.h - Return statistical information.
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
// $Id: statistics.h,v 1.2 2001/11/21 00:21:17 qp Exp $

#ifndef	STATISTICS_H
#define STATISTICS_H

private:

//
// Return the amount of space used and available in a stack.
//
ReturnValue return_stack_stat(const FixedSizeStack& stack, Object *& );

//
// Return the amount of space used and available in the binding trail.
//
ReturnValue return_stack_stat(const BindingTrail&, Object *& );

//
// Return the amount of space used and available in the other trail.
//
ReturnValue return_stack_stat(const OtherTrail&, Object *& );

//
// Return the amount of space used and available in a heap.
//
ReturnValue return_heap_stat(Heap& hp, Object *& );
//
// Return the amount of space used and available in the code area.
//
ReturnValue return_code_stat(Code& code, Object *& object1, 
			     Object *& object2, Object *& object3);
//
// Return the amount of space used and available in a hash table.
//
ReturnValue return_table_stat(FixedSizeHashTable& table, 
			      Object *& );

public:
//
// psi_cputime(var)
// Unifies  with the time in milliseconds since the system was
// started up.
//
ReturnValue psi_cputime(Object *& );

//
// psi_stat_choice(var, var, var)
// Return the amount of space used and available, and maximum usage
// in choice point stack.
//
ReturnValue psi_stat_choice(Object *& , Object *& , Object *& );

//
// psi_stat_global(var, var, var)
// Return the amount of space used and available, and maximum usage in heap.
//
ReturnValue psi_stat_global(Object *& , Object *& , Object *& );

//
// psi_stat_local(var, var, var)
// Return the amount of space used and available, and maximum usage
// in environment stack.
//
ReturnValue psi_stat_local(Object *& , Object *& , Object *& );
//
// psi_stat_binding_trail(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the binding trail.
//
ReturnValue psi_stat_binding_trail(Object *& , Object *& , Object *& );
//
// psi_stat_other_trail(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the other trail.
//
ReturnValue psi_stat_other_trail(Object *& , Object *& , Object *& );


//
// psi_stat_code(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the code area.
//
ReturnValue psi_stat_code(Object *& , Object *& , Object *& );

//
// psi_stat_string(var, var, var)
// Return the amount of space used and available, and maximum usage
// in the string table.
//
ReturnValue psi_stat_string(Object *& , Object *& , Object *& );

//
// psi_stat_ip(var, var, var)
// Return the amount of space used and available in the IP table.
//
ReturnValue psi_stat_ip_table(Object *& , Object *& );

//
// psi_stat_name(var, var)
// Return the amount of space used and availabe in the name table.
//
ReturnValue psi_stat_name(Object *& , Object *& );

//
// psi_stat_atom(var, var)
// Return the amount of space used and availabe in the atom table.
//
ReturnValue psi_stat_atom(Object *& , Object *& );
//
// psi_stat_scratchpad(var, var)
// Return the space info for the scratchpad.
//
ReturnValue psi_stat_scratchpad(Object *&, Object *&,  Object *&);

//
// psi_stat_predicate(var, var)
// Return the amount of space used and availabe in the predicate table.
//
ReturnValue psi_stat_predicate(Object *& , Object *& );

//
// psi_stat_memory(var)
// Return the total amount of space allocated by the operating system.
//
ReturnValue psi_stat_memory(Object *& );

//
// psi_stat_program(var)
// Return the amount of space used by code area and various tables.
//
ReturnValue psi_stat_program(Object *& );

#endif // STATISTICS_H
