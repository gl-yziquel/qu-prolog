// pseudo_instr.h -  definitions for pseudo-instructions
//
// ##Copyright##
// 
// Copyright (C) 2000-Thu Dec 10 06:53:58 AEST 2015 
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
// $Id: pseudo_instr.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef	PSEUDO_INSTR_H
#define	PSEUDO_INSTR_H

Object*&
PSIGetReg(const word32 i)
{
  if (i < NUMBER_X_REGISTERS)
    {
      return X[i];
    }
  else
    {
      return envStack.yReg(currentEnvironment, i - NUMBER_X_REGISTERS);
    }
}

//
// Create new variables for objects associated with an arg with out mode
// The modes are bits with 1 meaning out mode.
//
void psi1NewVars(int32, Object *&);
void psi2NewVars(int32, Object *&, Object *&);
void psi3NewVars(int32, Object *&, Object *&, Object *&);
void psi4NewVars(int32, Object *&, Object *&, Object *&, Object *&);
void psi5NewVars(int32, Object *&, Object *&, Object *&, Object *&, Object *&);

//
// Build a call for a pseudo instruction for use in interrupt handling
// and fast retry
//
Object* psi0BuildCall(word32);
Object* psi1BuildCall(word32, Object *);
Object* psi2BuildCall(word32, Object *, Object *);
Object* psi3BuildCall(word32, Object *, Object *, Object *);
Object* psi4BuildCall(word32, Object *, Object *, Object *, Object *);
Object* psi5BuildCall(word32, Object *, Object *, Object *, Object *, Object *);

//
// Pseudo instruction error handlers
// These are executed when a positive error number is returned from
// the pseudo instruction
//
CodeLoc psi0ErrorHandler(word32);
CodeLoc psi1ErrorHandler(word32, Object *);
CodeLoc psi2ErrorHandler(word32, Object *, Object *);
CodeLoc psi3ErrorHandler(word32, Object *, Object *, Object *);
CodeLoc psi4ErrorHandler(word32, Object *, Object *, Object *, Object *);
CodeLoc psi5ErrorHandler(word32, Object *, Object *, Object *, Object *, Object *);

//
// Build a structure to hold the current X registers and PC.
//
Object* psiSaveState(void);

#endif	// PSEUDO_INSTR_H
