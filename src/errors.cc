// errors.cc - Error messages handlers.
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
// $Id: errors.cc,v 1.5 2002/12/05 03:39:27 qp Exp $

#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

#include "config.h"

#include "area_offsets.h"
#include "defs.h"

using namespace std;

extern const char *Program;

//
// Remember AreaName.
//
const	char    *ErrArea = NULL;

//
// General error message handlers.
//

void
Fatal(const char *where, const char *message)
{
   cerr << Program << "(" << (long)getpid() << ") : " 
	<< where << ": Fatal : " << message << endl;
   exit(EXIT_FAILURE);
}

void
FatalS(const char *where, const char *message, const char *extra_message)
{
   cerr << Program << "(" << (long)getpid() << ") : " 
	<< where << ": Fatal : " << message
	<< " : " << extra_message << endl;
   exit(EXIT_FAILURE);
}

void
Warning(const char *where, const char *message)
{
   cerr << Program << "(" << (long)getpid() << ") : " 
	<< where << ": Warning : " << message << endl;
}

void
WarningS(const char *where, const char *message, const char *extra_message)
{
   cerr << Program << "(" << (long)getpid() << ") : " 
	<< where << ": Warning : " << message 
	<< " : " << extra_message << endl;
}

//
// Print out usage information and exit with an error code.
//
void
Usage(const char *program, const char *usage)
{
  cerr << "Usage: " << program << " " << usage << endl;

  exit(EXIT_FAILURE);
}

//
// Commonly used error message handlers.
//
void
SegmentTooLarge(const char *where, const char* which)
{
  cerr << Program << "(" << (long)getpid() << ") : " << where
       << ": Fatal : too large segment request in " << which;
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
OutOfPage(const char *where, const char *which, const word32 size)
{
  cerr << Program << "(" << (long)getpid() << ") : " << where
       << ": Fatal : out of memory in " << which
       << "(" << size << "K)";
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
OutOfHashTable(const char *where, const char *which, const word32 size)
{
  cerr << Program << "(" << (long)getpid() << ") : " << where
       << ": Fatal : out of memory in " << which
       << "(" << size << " entries)";
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
EmptyStack(const char *where, const char *which)
{
  cerr << Program << "(" << (long)getpid() << ") : " << where
       << ": Fatal : empty stack in " << which;
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
BadReset(const char *where, const char *which, const StackLoc loc)
{
  cerr << Program << "(" << (long)getpid() << ") : " << where
       << ": Fatal : bad reset to location " 
       << hex << loc << dec
       << " in " << which;
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
BadReference(const char *where, const char *which, const StackLoc loc)
{
  cerr << Program << "(" << (long)getpid() << ") : " << where
       << ": Fatal : bad reference to location " 
       << hex << loc << dec
       << " in " << which;
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
WrongFileFormat(const char *where, const char *which)
{
  cerr << Program << "(" << (long)getpid() << ") : " << where
       << ": Fatal : wrong format for file " << which;
  cerr << endl;
  exit(EXIT_FAILURE);
}

void
SaveFailure(const char *where, const char *data, const char *which)
{
  if (which == NULL)
    {
      cerr << Program << "(" << (long)getpid() << ") : " << where
	   << ": Fatal : failed to save " << which;
      cerr << endl;
      exit(EXIT_FAILURE);
    }
  else
    {
      cerr << Program << "(" << (long)getpid() << ") : " << where
	   << ": Fatal : failed to save " << data << " (" << which << ")";
      cerr << endl;
      exit(EXIT_FAILURE);
    }
}

void
ReadFailure(const char *where, const char *data, const char *which)
{
  if (which == NULL)
    {
      cerr << Program << "(" << (long)getpid() << ") : " << where
	   << ": Fatal : failed to read " << which;
      cerr << endl;
      exit(EXIT_FAILURE);
    }
  else
    {
      cerr << Program << "(" << (long)getpid() << ") : " << where
	   << ": Fatal : failed to read " << data << " (" << which << ")";
      cerr << endl;
      exit(EXIT_FAILURE);
    }
}
void OutOfHeapSpace(const char *where, char *which, const word32 size)
{
  cerr << Program << "(" << (long)getpid() << ") : " << where
       << ": Fatal : out of heap space in  " << which
       << "(" << size << "K)";
  cerr << endl;
  exit(EXIT_FAILURE);
}



