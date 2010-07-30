// qa_options.cc - Options for qa.
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
// $Id: qa_options.cc,v 1.2 2005/03/08 00:35:12 qp Exp $

#ifdef WIN32
#include <io.h>
#else
#include <unistd.h>
#endif

#include <stdlib.h>

#ifdef WIN32
#include "WinXGetopt.h"  // #include "../win32/src/XGetopt.h"
#endif
#include "qa_options.h"

#include "defaults.h"

static const char *INPUT_FILE = NULL;
static const char *OUTPUT_FILE = NULL;

QaOptions::QaOptions(int argc, char **argv)
  : Options("-i input-file\n"
	    "\t-o output-file\n"),
    input_file(INPUT_FILE),
    output_file(OUTPUT_FILE)
{
  int32 c;

  static const char *opts =  "i:o:";

  //
  // Parse command line options.
  //
#ifdef LINUX
  while ((c = getopt(argc, argv, opts)),
	 (c != -1 && c != '?'))
#else	// LINUX
#ifdef WIN32
  while ((c = getopt(argc, argv, const_cast<TCHAR*>(opts))) != -1)
#else
  while ((c = getopt(argc, argv, opts)) != -1)
#endif
#endif // LINUX
    {
      switch ((char) c)
	{
	case 'i':
	  input_file.Value(optarg);
	  break;
	case 'o':
	  output_file.Value(optarg);
	  break;
	}
    }

  valid = input_file.Value() != NULL &&
    output_file.Value() != NULL;
}
