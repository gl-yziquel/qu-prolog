// errors.h - Error messages handlers.
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
// $Id: errors.h,v 1.5 2005/03/08 00:35:05 qp Exp $

#ifndef	ERRORS_H
#define	ERRORS_H

#include <errno.h>
//#include <pthread.h>
#include <stdio.h>
#include <string.h>

#include "area_offsets.h"
#include "defs.h"

// Optimisations for functions which do not return.  This will
// necessarily vary from compiler to compiler.
 
#ifdef __GNUC__
#define NO_RETURN __attribute__ ((noreturn))
#else
#define NO_RETURN
#endif // __GNUC__

//
// Remember the name of the overflow area.
//
extern	const char	*ErrArea;

//
// General error message handlers.
//

//
// Just print out the message and continue the execution.
//

void Warning(const char *where, const char *message);
void WarningS(const char *where, const char *message, 
	      const char *extra_message);
//
// Print out the message and exit with an error code.
//
//
// Print out the message and exit with an error code.
//
extern  void    Fatal(const char *where,
                      const char *message) NO_RETURN;

extern  void    FatalS(const char *where,
		       const char *message,
		       const char *extra_message) NO_RETURN;

//
// Print out the usage message.
//
extern void Usage(const char *program,
		  const char *usage) NO_RETURN;

//
// Commonly used error message handlers.
//

//
// Fatal ones:
//
extern	void	SegmentTooLarge(const char *where,
				const char *which
				) NO_RETURN;
extern	void	OutOfPage(const char *where,
			  const char *which,
			  const word32 size) NO_RETURN;
extern	void	OutOfHashTable(const char *where,
			       const char *which,
			       const word32 size) NO_RETURN;
extern	void	EmptyStack(const char *where,
			   const char *which
			   ) NO_RETURN;
extern	void	BadReset(const char *where,
			 const char *which,
			 const StackLoc loc) NO_RETURN;
extern	void	BadReference(const char *where,
			     const char *which,
			     const StackLoc loc) NO_RETURN;
extern	void	WrongFileFormat(const char *where,
				const char *which
				) NO_RETURN;
extern	void	SaveFailure(const char *where,
			    const char *name,
			    const char *which = NULL) NO_RETURN;
extern	void	ReadFailure(const char *where,
			    const char *name,
			    const char *which = NULL) NO_RETURN;

extern void OutOfHeapSpace(const char *where, char *which,
                    const word32 size) NO_RETURN;

//
// A system call that indicates failure by returning a non-0 value.
// In this case, the error is indicated by the return value.
//
#define SYSTEM_CALL_NON_ZERO(f)				               \
do {							               \
  const int result = (f);				               \
  if (result != 0)					               \
    {                                                                  \
      FatalS(#f, " failed: ", strerror(result));  	       \
    }							               \
} while (0)

//
// A system call that indicates an error by returning a value less than zero.
// In this case, the error is indicated by the value in errno.
//
#define SYSTEM_CALL_LESS_ZERO(f)					\
do {									\
  if ((f) < 0)								\
    {									\
      perror(__FUNCTION__);						\
      Fatal(#f, " failed");	                                \
    }									\
} while (0)

//
// A system call that indicates failure by returning a non-0 value,
// but also has an error value that indicates that the operation failed
// for some reason that isn't catastrophic, e.g. a timeout or some such
// (c.f. pthread_mutex_trylock(), pthread_cond_timedwait()).
// 
// This macro returns from the calling function. It's mainly intended
// to be used in wrapper functions.
//
#define SYSTEM_CALL_NON_ZERO_RETURN_BOOL(f, val)			\
do {									\
  const int result = (f);						\
  if (result == 0)							\
    {									\
      return true;							\
    }									\
  else if (result == val)						\
    {									\
      return false;							\
    }									\
  else									\
    {									\
      FatalS(#f,  " failed: ", strerror(result)); \
      return false;							\
    }									\
} while (0)

#endif	// ERRORS_H
