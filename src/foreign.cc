// foreign.cc - Incremental loading of foreign language functions.
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
// $Id: foreign.cc,v 1.14 2002/12/24 00:03:54 qp Exp $

#include "global.h"
#include "thread_qp.h"

#include "atom_table.h"
#include "pred_table.h"

extern AtomTable *atoms;
extern PredTab *predicates;

#if defined(SOLARIS) || defined(LINUX) || defined(NETBSD) || defined(MACOSX)

#include <dlfcn.h>
#include <sstream>
#include <stdlib.h>
#include <unistd.h>

#if (defined(FREEBSD) || defined(MACOSX))
#include        <pthread.h>
#include        <signal.h>
#include <sys/wait.h>
#endif //defined(FREEBSD) || defined(MACOSX)


extern	"C"	int mkstemp(char *);

#if (defined(FREEBSD) || defined(MACOSX))
extern char **environ;
int local_bsd_system (char *command) {
  int pid, status;
  
  if (command == 0)
    return 1;
  pid = fork();
  if (pid == -1)
    return -1;
  if (pid == 0) {
    signal(SIGVTALRM, SIG_IGN);
    char *argv[4];
    argv[0] = "sh";
    argv[1] = "-c";
    argv[2] = command;
    argv[3] = 0;
    execve("/bin/sh", argv, environ);
    exit(127);
  }
  do {
    if (waitpid(pid, &status, 0) == -1) {
      if (errno != EINTR)
	return -1;
    } else
      return status;
  } while(1);
}

#endif //defined(FREEBSD) || defined(MACOSX)

//
// Link and load the object files and libraries.
//
bool
Thread::LinkLoad(Object* objects, Object* libraries)
{
  ostringstream strm;
  char output[] = "/tmp/symXXXXXX";
  Object* file;
  void *handle;

  //
  // Generate the linking command.
  //
  mkstemp(output);
  
#ifdef SOLARIS
        strm << "ld -G ";
#else
#ifdef MACOSX
	strm << "g++ -flat_namespace -undefined suppress -bundle ";
#else
        strm << "g++ -shared -Wl,-soname," << output << " ";
#endif // MACOSX
#endif // SOLARIS

  for (objects = objects->variableDereference();
       objects->isCons();
       objects = OBJECT_CAST(Cons*, objects)->getTail()->variableDereference())
    {
      file =  OBJECT_CAST(Cons*,objects)->getHead()->variableDereference();
      DEBUG_ASSERT(file->isAtom());
      
      strm << atoms->getAtomString(file) << " ";
    }
  DEBUG_ASSERT(objects->isNil());
  
  for (libraries = libraries->variableDereference();
       libraries->isCons();
       libraries = 
         OBJECT_CAST(Cons*, libraries)->getTail()->variableDereference())
    {
      file =  OBJECT_CAST(Cons*, libraries)->getHead()->variableDereference();
      
      DEBUG_ASSERT(file->isAtom());
      
      strm << atoms->getAtomString(file) << " ";
    }

  DEBUG_ASSERT(libraries->isNil());
  
#ifdef SOLARIS
        strm << "-lc -o " << output << ends;
#else // !SOLARIS
        strm << " -lc -o " << output << ends;
#endif // SOLARIS

  
  //
  // Link the object files and the libraries.
  //
  const char *command = strm.str().data();

#if (defined(FREEBSD) || defined(MACOSX))
  if (local_bsd_system(command))
#else
  if (system(command))
#endif
    {
#ifdef SOLARIS
      Warning(__FUNCTION__, "cannot ld -G");
#else // !SOLARIS
      Warning(__FUNCTION__, "Can't create shared object");
#endif // SOLARIS
      unlink(output);
      return(false);
    }
  
  if ((handle = dlopen(output, RTLD_LAZY)) == NULL)
    {
      Warning(__FUNCTION__, dlerror());
      unlink(output);
      return(false);
    }
  
  ForeignFile = new Handle(handle, ForeignFile);
  unlink(output);
  
  return(true);
}

//
// Look up a symbol.
//
EscFn
Thread::FnAddr(const char *fn) const
{
  void	*loc;
  
  if ((loc = dlsym(ForeignFile->file(), fn)) == NULL)
    {
      Warning(__FUNCTION__, dlerror());
      return((EscFn)(EMPTY_LOC));
    }
  return((EscFn)(loc));
}
#else	// SOLARIS
bool
Thread::LinkLoad(Object*, Object*)
{
  // Nothing!
  return true;
}

EscFn
Thread::FnAddr(const char *) const
{
  // Nothing, again!
  return (EscFn) NULL;
}

#endif	// SOLARIS

//
// psi_load_foreign(object files, libraries, predicate list, function list)
// Link and load the object files.  Link the predicate and function together.
//
Thread::ReturnValue
Thread::psi_load_foreign(Object *& object_file_arg,
			    Object *& libraries_arg,
			    Object *& predicate_list_arg,
			    Object *& function_list_arg)
{
  Object* argOF = heap.dereference(object_file_arg);
  Object* argL = heap.dereference(libraries_arg);
  Object* argPL = heap.dereference(predicate_list_arg);
  Object* argFL = heap.dereference(function_list_arg);


  if (argOF->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 1);
    }

  if (argL->isVariable())
    {
      PSI_ERROR_RETURN(EV_INST, 2);
    }

  //
  // Link and load the object files and libraries with the emulator.
  //
  if (! LinkLoad(argOF, argL))
    {
      return RV_FAIL;
    }
  
  Object* predList = argPL->variableDereference();
  Object* funcList = argFL->variableDereference();

  //
  // Install the predicate with the function as the definition.
  //
  for (;
       predList->isCons() && funcList->isCons();
       predList = 
	 OBJECT_CAST(Cons*, predList)->getTail()->variableDereference(),
       funcList = 
	 OBJECT_CAST(Cons*, funcList)->getTail()->variableDereference())
    {
      Object* head = 
	OBJECT_CAST(Cons*, predList)->getHead()->variableDereference();
      if (!head->isStructure() ||
	  OBJECT_CAST(Structure*, head)->getArity() != 2)
	{
	  PSI_ERROR_RETURN(EV_TYPE, 3);
	}
      
      Object* pred 
	= OBJECT_CAST(Structure*, head)->getArgument(1)->variableDereference();
      Object* arity 
	= OBJECT_CAST(Structure*, head)->getArgument(2)->variableDereference();
      Object* fn 
	= OBJECT_CAST(Cons*, funcList)->getHead()->variableDereference();

      if (!pred->isAtom() ||
	  !arity->isShort() ||
	  !(0 <= arity->getNumber() && 
	    arity->getNumber() <= (signed) ARITY_MAX) ||
	  !fn->isAtom())
	{
	  PSI_ERROR_RETURN(EV_TYPE, 4);
	}
      
      predicates->addEscape(atoms, OBJECT_CAST(Atom*, pred), 
			    arity->getNumber(),
			    FnAddr(atoms->getAtomString(fn)), code);
    }

  if (!predList->isNil())
    {
      PSI_ERROR_RETURN(EV_RANGE, 3);
    }
  if (!funcList->isNil())
    {
      PSI_ERROR_RETURN(EV_RANGE, 4);
    }
  
  return RV_SUCCESS;
}







