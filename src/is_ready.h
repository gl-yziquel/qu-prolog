// is_ready.h - Handy macros
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
// $Id: is_ready.h,v 1.6 2002/04/28 04:59:32 qp Exp $

#ifndef	IS_READY_H
#define	IS_READY_H

// IS_READY_IO(FD *s,
//	       const time_t timeout)
//
// This macro is used to simplify the coding required when we're checking
// whether an IO operation on a socket or stream is about to be attempted,
// and we're worried that the operation might cause blocking.
#define IS_READY_IO(s, timeout)				\
do {									\
 /* Timed out? */					\
 if (block_status.IsTimedOut() /* || (s)->isEnded()*/ )			\
   {									\
     return RV_FAIL;							\
   }									\
 /* Ready for action? */						\
 else if ((s)->isReady() || (s)->isEnded())				\
   {									\
     /* Do nothing - we're ready to rock! */				\
   }									\
 /* A poll? */								\
 else if ((timeout) == 0)						\
   {									\
     return RV_FAIL;							\
   }									\
 /* Previously blocked? */						\
 else if (restart_status.IsRestart())					\
   {									\
     return RV_BLOCK;							\
   }									\
 else /* Block for the first time. */					\
   {									\
     block_status.setBlockIO((s)->getFD(), (s)->Type(), (timeout));	\
     return RV_BLOCK;							\
   }									\
} while (0)

// IS_READY_ICM(Heap& heap,
//              CondList<ICMMessage *> queue,
//	        CondList<ICMMessage *>::iterator iter,
//	        const size_t timeout)
//
// This macro is used to simplify the coding required when we're checking
// whether an ICM operation is about to be attempted,
// and we're worried that the operation might cause blocking.
#define IS_READY_ICM(heap, queue, iter, timeout)			\
do {									\
  /* Timed out? */							\
  if (block_status.IsTimedOut())					\
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
          /* Wind back the iterator to the element before the end(). */	\
	  /* (N.B. If the queue is empty, this has no real effect.) */	\
          (iter)--;							\
          block_status.setBlockICM((iter), (queue).size(), (timeout));  \
          return RV_BLOCK;						\
	}								\
    }									\
  else /* There's a message to read. Yippee! */				\
    {									\
      /* Previously blocked on empty queue? */				\
      if (block_status.testBlockICM() &&				\
	  block_status.QueueSize() == 0)				\
	{								\
	  /* Set the iterator to start of the queue. */			\
	  (iter) = (queue).begin();					\
	}								\
    }									\
} while (0)


// IS_READY_IMSTREAM(CondList<ICMMessage *> queue,
//                   icmHandle sender_handle,
//	             CondList<ICMMessage *>::iterator iter,
//	             const size_t timeout)
//
// This macro is used to simplify the coding required when we're checking
// whether an IMSTREAM operation is about to be attempted,
// and we're worried that the operation might cause blocking.
#define IS_READY_IMSTREAM(queue, strm, timeout)	        \
do {									\
  /* Timed out? */							\
  if (block_status.IsTimedOut() && scheduler->Status().testEnableTimeslice()) \
    {									\
      return RV_FAIL;							\
    }									\
  /* Skip commited messages.*/						\
      list<ICMMessage *>::iterator *iter = (strm)->getIter();               \
      if (!(strm)->isFound())                           	    \
        {                                             \
          *(iter) = (queue).begin();                  \
        }                                             \
      bool found = false;                                                   \
      for (;								\
           *(iter) != (queue).end();                   		\
           (*(iter))++)                                              \
        {                                                                   \
          if ( (**(iter))->Committed() )                                     \
           {                                                                \
  	     continue;					                \
           }                                                                \
          ICMMessage& icm_message = ***iter;                                \
          icmHandle from_handle = icm_message.Sender();                     \
          if (icmSameHandle(from_handle, (strm)->getSenderHandle()) == icmOk) \
            {                                                               \
              found = true;                                                 \
              break;                                                        \
             }                                                              \
        }                                                                   \
      /* End of queue? */					\
      if (*(iter) == (queue).end())				\
        {							\
	  if (scheduler->Status().testEnableTimeslice())          \
	    {                                                   \
              DEBUG_ASSERT(!found);                                 \
              /* Just a poll? */					\
              if ((timeout) == 0)					\
	        {							\
	          return RV_FAIL;					\
	        }							\
              else /* Block the thread. */				\
	        {							\
              /* Wind back the iterator to the element before the end(). */ \
	      /* (N.B. If the queue is empty, this has no real effect.) */  \
                  (*(iter))--;						\
                  block_status.setBlockICM(*(iter), (queue).size(),(timeout)); \
                  return RV_BLOCK;					\
	        }						\
	    }                                                   \
	  else                                                   \
	    {                                                   \
              (*(iter))--;						\
	    }                                                   \
        }								\
      else /* There's a message to read. Yippee! */			\
        {								\
          (strm)->setFound();                                                 \
          DEBUG_ASSERT(found);                                              \
        }								\
} while (0)


#ifdef ICM_DEF
#define IS_READY_STREAM(s, timeout)                                     \
do {                                                                    \
     if ((s)->Type() == IMSTREAM)                                         \
       {                                                                \
         if ((s)->is_at_eof())                                     \
	   {                                                            \
             IS_READY_IMSTREAM((s)->getThread()->ICMQueue(), (s),  timeout);  \
           }                                                            \
       }                                                                \
     else                                                               \
       {                                                                \
         if (scheduler->Status().testEnableTimeslice())       \
	   {                                                   \
             IS_READY_IO((s), timeout);                                       \
	   }                                                   \
       }                                                                \
} while (0)

#else // ICM_DEF

#define IS_READY_STREAM(s, timeout)                                     \
do {                                                                    \
     if ((s)->Type() == IMSTREAM)                                         \
       {                                                                \
         return RV_FAIL;           \
       }                                                                \
     else                                                               \
       {                                                                \
         if (scheduler->Status().testEnableTimeslice())       \
	   {                                                   \
             IS_READY_IO((s), timeout);                                       \
	   }                                                   \
       }                                                                \
} while (0)
#endif // ICM_DEF

#endif	// IS_READY_H














