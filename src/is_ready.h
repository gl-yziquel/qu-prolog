// is_ready.h - Handy macros
//
// ##Copyright##
// 
// Copyright (C) 2000-2011 
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
// $Id: is_ready.h,v 1.16 2006/02/14 02:40:09 qp Exp $

#ifndef	IS_READY_H
#define	IS_READY_H

// IS_READY_IO(FD *s,
//	       const time_t timeout)
//
// This macro is used to simplify the coding required when we're checking
// whether an IO operation on a socket or stream is about to be attempted,
// and we're worried that the operation might cause blocking.
#define IS_READY_IO(s)				                        \
do {									\
 /* Ready for action? */						\
 if ((s)->isReady())				                        \
   {									\
     /* Do nothing - we're ready to rock! */				\
   }                                                                    \
 else /* Block */							\
   {									\
     BlockingIOObject* blockobj = new BlockingIOObject(this, (s)->getFD(), (s)->Type(), iom);							\
     scheduler->blockedQueue().push_back(blockobj); 	        	\
     block_status.setBlocked();                                         \
     return RV_BLOCK;							\
   }									\
} while (0)

// IS_READY_MESSAGE(Heap& heap,
//              listist<Message *> queue,
//	        listist<Message *>::iterator iter, int timeout)
//
// This macro is used to simplify the coding required when we're checking
// whether a message operation is about to be attempted,
// and we're worried that the operation might cause blocking.
#define IS_READY_MESSAGE(heap, queue, iter, timeout)			\
do {									\
  /* Timed out? */							\
  if (block_status.isRestartTime())					\
    {									\
      delete &(iter);                                                   \
      return RV_FAIL;							\
    }									\
  /* Skip commited messages.*/						\
  for (;								\
       (iter) != (queue).end() && (*(iter))->Committed();		\
       (iter)++)							\
    ;									\
  /* End of queue? */							\
  if ((iter) == (queue).end())						\
    {									\
      /* Just a poll? */						\
      if ((timeout) == 0)						\
	{								\
          delete &(iter);                                               \
	  return RV_FAIL;						\
	}								\
      else /* Block the thread. */					\
	{								\
          BlockingMessageObject* blockobj = new BlockingMessageObject(this, (timeout), &iter);							\
          scheduler->blockedQueue().push_back(blockobj); 	       	\
          block_status.setBlocked();                                    \
          return RV_BLOCK;						\
	}								\
    }									\
  else /* There's a message to read. Yippee! */				\
    {									\
    }									\
} while (0)


//
// This macro is used to simplify the coding required when we're checking
// whether an IMSTREAM operation is about to be attempted,
// and we're worried that the operation might cause blocking.
#define IS_READY_IMSTREAM(s)	                                \
do {									\
 /* Ready for action? */						\
 if ((s)->isReady())				        \
   {									\
     /* Do nothing - we're ready to rock! */				\
   }                                                                    \
 else /* Block */					\
   {									\
     BlockingIOObject* blockobj = new BlockingIOObject(this, (s)->getFD(), (s)->Type(), iom);							\
     scheduler->blockedQueue().push_back(blockobj); 	        	\
     block_status.setBlocked();                                    \
     return RV_BLOCK;							\
   }									\
} while (0)


#define IS_READY_STREAM(s)                                                  \
do {                                                                        \
     if ((s)->Type() == IMSTREAM)                                           \
       {                                                                    \
         IS_READY_IMSTREAM((s));              \
       }                                                                    \
     else                                                                   \
       {                                                                    \
         IS_READY_IO((s));                                                  \
       }                                                                    \
} while (0)


#define IS_READY_SOCKET(socket)                                             \
do {                                                                        \
      if (scheduler->Status().testEnableTimeslice())                        \
        {                                                                   \
           if (is_ready((socket)->getFD(), QPSOCKET))                         \
             {                                                              \
             }                                                              \
           else /* Block */						\
             {								\
               BlockingIOObject* blockobj = new BlockingIOObject(this, (socket)->getFD(), QPSOCKET, iom);							\
               scheduler->blockedQueue().push_back(blockobj); 	       	\
               block_status.setBlocked();                                    \
               return RV_BLOCK;                                             \
              }                                                             \
        }                                                                   \
} while (0)
               


#endif	// IS_READY_H














