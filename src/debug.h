// debug.h - Low level debug facilities for Qu-Prolog emulator.
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
// $Id: debug.h,v 1.1.1.1 2000/12/07 21:48:04 qp Exp $

#ifndef DEBUG_H
#define DEBUG_H

#ifdef DEBUG

#include <iostream.h>
#include <pthread.h>
#include <stdlib.h>

// Every program in the suite has to define its own name.
extern const char *Program;

#define	DEBUG_ASSERT(cond)						      \
  do {									      \
    if (! (cond))							      \
      {									      \
	cerr.form("%s(%ld): %s: debug error at %ld in %s",		      \
		  Program, pthread_self(), __FUNCTION__, __LINE__, __FILE__); \
        abort();							      \
      }									      \
  } while (0)

#define	DEBUG_CODE(s)				\
do {						\
 s						\
} while (0)

#define DEBUG_ENTER							\
do {									\
  cerr.form("%s(%ld):->%s\n", Program, pthread_self(), __FUNCTION__);	\
} while (0)

#define DEBUG_EXIT							\
do {									\
  cerr.form("%s(%ld):<-%s\n", Program, pthread_self(), __FUNCTION__);	\
} while (0)

#define DEBUG_CALL(c)							\
do {									\
  cerr.form("%s(%ld): Before %s\n", __FUNCTION__, pthread_self(), #c);	\
  c;									\
  cerr.form("%s(%ld): After %s\n", __FUNCTION__, pthread_self(), #c);	\
} while (0)

#define DEBUG_DISPLAY(h, c, a) 				     \
do {									     \
  cerr.form("%s(%ld): %s %s\n", Program, pthread_self(), __FUNCTION__ , #c); \
  h.DisplayTerm(cerr, a, c);					     \
  cerr << endl;								     \
} while (0)

#define DEBUG_PTR(p)							   \
do {									   \
  cerr.form("%s(%ld): %s %p\n", Program, pthread_self(), __FUNCTION__, p); \
} while (0)

#else	// DEBUG

#define	DEBUG_ASSERT(cond)
#define	DEBUG_CODE(s)
#define DEBUG_ENTER
#define DEBUG_EXIT
#define DEBUG_CALL(c) do { c; } while (0)
#define DEBUG_DISPLAY(h, c)

#endif	// DEBUG

#endif	// DEBUG_H


