// environment.cc - Each environment records the state of computation within a
//		    clause.  It enables the computation to continue after the
//		    current subgoal has been solved.
//
// ##Copyright##
// 
// Copyright (C) 2000, 20001
// Software Verification Research Centre
// The University of Queensland
// Australia 4072
// 
// email: svrc@it.uq.edu.au
// 
// The Qu-Prolog 6.0 System and Documentation  
// 
// COPYRIGHT NOTICE, LICENCE AND DISCLAIMER.
// 
// Copyright 2000,2001 by The University of Queensland, 
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
// 	written consent from the SVRC; and
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
// For information on commercial use of this software contact the SVRC.
// 
// ##Copyright##
//
// $Id: environment.cc,v 1.2 2001/12/06 02:56:06 qp Exp $

#include "area_offsets.h"
#include "objects.h"
#include "defs.h"
#include "environment.h"
#include "indent.h"

//
// Push a new environment onto the stack.
// If EnvLoc or StackLoc changes representation, then a bug may
// occur if this is not changed.
//
/*
EnvLoc
EnvironmentStack::push(const EnvLoc PrevEnv, const CodeLoc ContInst,
		       const word32 NumYs)
{
	EnvLoc	env;

	//
	// Allocate environment.
	//
	env = pushRecord(sizeof(Environment) + (NumYs - 1) * sizeof(Object*));
	//
	// Initialise fixed fields.
	//
	fetchEnv(env)->previousEnvironment = PrevEnv;
	fetchEnv(env)->continuationInstruction = ContInst;
	fetchEnv(env)->NumYRegs = NumYs;
	fetchEnv(env)->zeroYRegs();

	return(env);
}
*/

// Display the meaningful fields for debugging purposes.
ostream&
EnvironmentStack::Display(ostream& ostrm, const EnvLoc index, 
			  const size_t depth)
{
  Environment *e = fetchEnv(index);

  Indent(ostrm, depth);
  cerr.form("previousEnvironment=%#lx\n", e->previousEnvironment);

  Indent(ostrm, depth);
  cerr.form("continuationInstruction=%#lx\n", e->continuationInstruction);
  
  return ostrm;
}


#ifdef DEBUG
void 
EnvironmentStack::printMe(AtomTable& atoms, EnvLoc env)
{  
  while (true)
    {
      cerr << "Environment [" << env << "] ";
      if (gc_isMarkedEnv(env))
	{
	  cerr << "gc_marked";
	}
      cerr << endl;
      for (int i = (getNumYRegs(env) & 0x7FFFFFFFUL)-1; i >= 0; i--)
	{
	  cerr << "Y[" << i << "] : " << hex << (word32)(yReg(env,i)) << dec << endl;
	}
            if (env == firstEnv())
	{
	  return;
	}
      env = getPreviousEnv(env);
    }
}
#endif //DEBUG














