// bind.cc - Qu-Prolog bindings. 
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
// $Id: bind.cc,v 1.6 2006/01/31 23:17:49 qp Exp $


#include        "thread_qp.h"
//#include        "trail.h"

//
// Bind variable1 to variable2 or variable2 to variable1.
// Assumes both variables are dereferenced.
//
void
Thread::bindVariables(Variable *variable1, Variable *variable2)
{
  assert(variable1 == variable1->variableDereference());
  assert(variable2 == variable2->variableDereference());
  assert(variable1->isVariable());
  assert(variable2->isVariable());
  Variable *junior;
  Variable *senior;
  
  //
  // Find which variable is "younger", and which is "older".
  //

  assert(variable1->isThawed() || variable2->isThawed() || !status.testHeatWave());
  if (variable1->isFrozen())
    {
      junior = variable2;
      senior = variable1;
      if (junior->getName() != NULL && senior->getName() == NULL)
        {
          senior = addExtraInfo(senior);
          updateAndTrailObject(reinterpret_cast<heapobject*>(senior),
                               junior->getName(), Reference::NameOffset);
        }
    }
  else if (variable2->isFrozen())
    {
      junior = variable1;
      senior = variable2;
      if (junior->getName() != NULL && senior->getName() == NULL)
        {
          senior = addExtraInfo(senior);
          updateAndTrailObject(reinterpret_cast<heapobject*>(senior),
                               junior->getName(), Reference::NameOffset);
        }
    }
  else if ((reinterpret_cast<void*>(variable1) < reinterpret_cast<void*>(variable2)))
    {
      junior = variable2;
      senior = variable1;
    }
  else
    {
      junior = variable1;
      senior = variable2;
    }

  if (junior->hasExtraInfo() && !senior->hasExtraInfo())
    {
      Variable* tmp = junior;
      junior = senior;
      senior = tmp;
    }

  if (junior->getDelays()->isCons())
    {
      wakeUpDelayedProblems(junior);
    }

  if (junior->isOccursChecked() && !senior->isOccursChecked())
    {
      trailTag(senior);
      senior->setOccursCheck();
    }
  bindAndTrail(junior, senior);
}

//
// Bind object_variable1 to object_variable2 or object_variable2 to 
// object_variable1 based on age.
//
void
Thread::bindObjectVariables(ObjectVariable *object_variable1, 
			  ObjectVariable *object_variable2)
{
  ObjectVariable *junior;
  ObjectVariable *senior;
  assert(object_variable1->isObjectVariable() 
	       && object_variable1 == object_variable1->variableDereference());
  assert(object_variable2->isObjectVariable() 
	       && object_variable2 == object_variable2->variableDereference());
  
  assert(! object_variable1->isLocalObjectVariable());
  assert(! object_variable2->isLocalObjectVariable());

  //
  // Find which variable is "younger", and which is "older".
  //
  if (object_variable1->isFrozen())
    {
      junior = object_variable2;
      senior = object_variable1;
    }
  else if (object_variable2->isFrozen())
    {
      junior = object_variable1;
      senior = object_variable2;
    }
  else if ((reinterpret_cast<void*>(object_variable1) < reinterpret_cast<void*>(object_variable2)))
    {
      junior = object_variable2;
      senior = object_variable1;
    }
  else
    {
      junior = object_variable1;
      senior = object_variable2;
    }

  //
  // Pass on the name if necessary
  //
  if (junior->getName() != NULL && senior->getName() == NULL)
    {
      updateAndTrailObject(reinterpret_cast<heapobject*>(senior), 
			   junior->getName(), Reference::NameOffset);
    }
  //
  // wake up delays for junior
  //
  if (junior->getDelays()->isCons())
    {
      wakeUpDelayedProblems(junior);
    }

  //
  // Transfer distinctness information from junior to senior.
  //
  if (junior->getDistinctness()->isCons())
    {
      Object* merged = heap.copyDistinctnessList(junior->getDistinctness(), 
						 senior);
      updateAndTrailObject(reinterpret_cast<heapobject*>(senior), 
			   merged, ObjectVariable::DistinctnessOffset);
    }
  bindAndTrail(junior, senior);
}










