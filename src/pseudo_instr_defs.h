// pseudo_instr_defs.h -
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
// $Id: pseudo_instr_defs.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef PSEUDO_INSTR_DEFS_H
#define PSEUDO_INSTR_DEFS_H

//
// Type definitions for the data used to represent pseudo instructions
//
struct pseudo_instr0_data {
  ReturnValue (*funct)(void); // pointer to function
    int32	mode;			 // bit representation of mode of args
    char *name;			// Used by QuAM tracer
};

struct pseudo_instr1_data {
  ReturnValue (*funct)(Object*&); // pointer to function
  int32	mode;			// bit representation of mode of args
  char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr2_data {
  ReturnValue (*funct)(Object*&, Object*&);
  int32	mode;
  char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr3_data {
  ReturnValue (*funct)(Object*&, Object*&, Object*&);
  int32	mode;
  char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr4_data {
  ReturnValue (*funct)(Object*&, Object*&, Object*&, Object*&);
  int32	mode;
  char *name;			// Used by QuAM tracer
};
  
struct pseudo_instr5_data {
  ReturnValue (*funct)(Object*&, Object*&, Object*&, Object*&, Object*&);
  int32 mode;
  char *name;
};

extern pseudo_instr0_data pseudo_instr0_array[];
extern pseudo_instr1_data pseudo_instr1_array[];
extern pseudo_instr2_data pseudo_instr2_array[];
extern pseudo_instr3_data pseudo_instr3_array[];
extern pseudo_instr4_data pseudo_instr4_array[];
extern pseudo_instr5_data pseudo_instr5_array[];

#endif // PSEUDO_INSTR_DEFS_H
