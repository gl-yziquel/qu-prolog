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
// $Id: errors.cc,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#include <iostream.h>
#include <stdarg.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#include "config.h"

#include "area_offsets.h"
#include "defs.h"

extern const char *Program;

//
// Remember AreaName.
//
const	char    *ErrArea = NULL;

//
// General error message handlers.
//

//
// Just print out the message and continue the execution.
//
void
Warning(const char *where, const char *message, ...)
{
	va_list	ap;

	cerr.form("%s(%ld): %s: Warning: ",
		  Program, getpid(), where);
	va_start(ap, message);
	cerr.vform(message, ap) << endl;
	va_end(ap);
}

//
// Print out the message and exit with an error code.
//
void
Fatal(const char *where, const char *message, ...)
{
	va_list	ap;

	cerr.form("%s(%ld): %s: Fatal: ",
		  Program, getpid(), where);
	va_start(ap, message);
	cerr.vform(message, ap) << '\n';
	va_end(ap);
	exit(EXIT_FAILURE);
}

//
// Print out usage information and exit with an error code.
//
void
Usage(const char *program, const char *usage)
{
  cerr.form("Usage: %s %s\n", program, usage);

  exit(EXIT_FAILURE);
}

//
// Commonly used error message handlers.
//
void
SegmentTooLarge(const char *where, const char* which)
{
  Fatal(where, "too large segment request in %s", which);
}

void
OutOfMemory(const char *where)
{
  Fatal(where, "out of system (C++) memory");
}

void
OutOfPage(const char *where, const char *which, const word32 size)
{
  Fatal(where, "out of memory in %s (%dK)", which, size);
}

void
OutOfHashTable(const char *where, const char *which, const word32 size)
{
  Fatal(where, "out of memory in %s (%d entries)", which, size);
}

void
EmptyStack(const char *where, const char *which)
{
  Fatal(where, "empty stack in %s", which);
}

void
BadReset(const char *where, const char *which, const StackLoc loc)
{
  Fatal(where, "bad reset to location %#x in %s", loc, which);
}

void
BadReference(const char *where, const char *which, const StackLoc loc)
{
  Fatal(where, "bad reference to location %#x in %s", loc, which);
}

void
WrongFileFormat(const char *where, const char *which)
{
  Fatal(where, "wrong format for file %s", which);
}

void
SaveFailure(const char *where, const char *data, const char *which)
{
  if (which == NULL)
    {
      Fatal(where, "failed to save %s", data);
    }
  else
    {
      Fatal(where, "failed to save %s (%s)", data, which);
    }
}

void
ReadFailure(const char *where, const char *data, const char *which)
{
  if (which == NULL)
    {
      Fatal(where, "failed to read %s", data);
    }
  else
    {
      Fatal(where, "failed to read %s (%s)", data, which);
    }
}
void OutOfHeapSpace(const char *where, char *which, const word32 size)
{
  Fatal(where, "out of heap space in %s (%dK)", which, size);
}



