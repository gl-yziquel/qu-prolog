// generate_var_names.cc -
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
// $Id: generate_var_names.cc,v 1.3 2000/12/13 23:10:01 qp Exp $

#include "atom_table.h"
#include "thread_qp.h"

extern AtomTable *atoms;

//
// Generate a new name for variables.  Find one that is either not in use or
// generate a new variable name.
// The name sequence is:
//	A, .., Z, A1, .., Z1, A2, .., Z2, ...
//
Atom*
Thread::GenerateVarName(Thread* threadPtr, word32& counter, char* buff)
{
  ostrstream strm(buff, ATOM_LENGTH);
  AtomLoc loc;
  
  do
    {
      strm.seekp(0);
      //
      // Generate a new name and check whether it is used.
      //
      if (strm.good() && strm.form("%c", 'A' + counter % 26).fail())
	{
	  Fatal(__FUNCTION__, "problem in generating variable name");
	}
      //
      // Add the digit suffix when the suffix is greater than 0.
      if (counter > 25)
	{
	  if (strm.good() && strm.form("%d", counter / 26).fail())
	    {
	      Fatal(__FUNCTION__, "problem in generating variable name");
	    }
	}
      strm << ends;
      counter++;
      loc = atoms->lookUp(buff);
    }
  while (loc != EMPTY_LOC && 
	 threadPtr->names.getVariable(atoms->getAtom(loc)) != NULL);

  //
  // A name is found.
  //
  if (loc == EMPTY_LOC)
    {
      return(atoms->add(buff));
    }
  else
    {
      return(atoms->getAtom(loc));
    }
}

//
// Generate a new name for object variables.  Find one that is either not in
// use or generate a new variable name.
//
// !!!!
// Note that another version of this function,
// GenerateRObjectVariableName(), is used for generating
// the names of object variables when
// psi_writeR_ObjectVariable is called.
// !!!!
//
Atom*
Thread::GenerateObjectVariableName(Thread* threadPtr, word32& counter, char* buff)
{
  ostrstream strm(buff, ATOM_LENGTH);
  AtomLoc loc = EMPTY_LOC;

  do
    {
      strm.seekp(0);
      //
      // Generate a new name and check whether it is used.
      //
      if (strm.good() && strm.form("_x%d", counter).fail())
	{
	  Fatal(__FUNCTION__, 
		"problem in generating object variable name");
	}
      strm << ends;
      counter++;
      loc = atoms->lookUp(buff);
    } while (loc != EMPTY_LOC && 
	     threadPtr->names.getVariable(atoms->getAtom(loc)) != NULL);

  //
  // A name is found.
  //
  if (loc == EMPTY_LOC)
    {
      return(atoms->add(buff));
    }
  else
    {
      return(atoms->getAtom(loc));
    }
}


//
// Generate a new name for object variables.  Find one that is either not in
// use or generate a new variable name.
//
// !!!!
// Note that another version of this function,
// GenerateObjectVariableName(), is used for generating
// the names of object variables when
// psi_write_ObjectVariable is called.
// !!!!
//
Atom*
Thread::GenerateRObjectVariableName(Thread* threadPtr, word32& counter, char* buff)
{
  ostrstream strm(buff, ATOM_LENGTH);
  AtomLoc loc = EMPTY_LOC;

  do
    {
      strm.seekp(0);
      //
      // Generate a new name and check whether it is used.
      //
      if (strm.good() && strm.form("x%d", counter).fail())
	{
	  Fatal(__FUNCTION__,
		"problem in generating object variable name");
	}
      strm << ends;
      counter++;
      loc = atoms->lookUp(buff);
     } while (loc != EMPTY_LOC && 
	      threadPtr->names.getVariable(atoms->getAtom(loc)) != NULL);

  //
  // A name is found.
  //
  if (loc == EMPTY_LOC)
    {
      return(atoms->add(buff));
    }
  else
    {
      return(atoms->getAtom(loc));
    }
}





