// pipe.cc -
//
// ##Copyright##
// 
// Copyright (C) 2000-2009 
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
// $Id: pipe.cc,v 1.5 2005/03/08 00:35:11 qp Exp $

#include <errno.h>
#ifdef WIN32
#include <io.h>
#include <fcntl.h>
#endif

#include "thread_qp.h"

Thread::ReturnValue
Thread::psi_pipe(Object *& input_stream_arg,
		 Object *& output_stream_arg)
{
  int fdes[2];

#ifdef WIN32
  int res = _pipe(fdes, 256, _O_BINARY);
#else
  int res = pipe(fdes);
#endif
  if (res == -1)
    {
      PSI_ERROR_RETURN(EV_SYSTEM, 0);
    }

  QPStream *instream = new QPifdstream(fdes[0]);

  QPStream *outstream = new QPofdstream(fdes[1]);


  input_stream_arg =  heap.newInteger(reinterpret_cast<wordptr>(instream));
  output_stream_arg = heap.newInteger(reinterpret_cast<wordptr>(outstream));

  return RV_SUCCESS;
}















