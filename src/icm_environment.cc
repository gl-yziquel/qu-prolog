// icm_environment.cc -
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
// $Id: icm_environment.cc,v 1.4 2001/09/23 22:32:00 qp Exp $

#include "config.h"

#ifdef ICM_DEF
#include "icm.h"
#include "icmP.h"
#include "icm_environment.h"

#ifndef USE_ICM_DEREGISTER
//#warning Not using icmDeregisterAgent() call.
static icmStatus qpDeregisterAgent(icmConn conn, icmHandle handle);
#endif

bool
ICMEnvironment::Register(char *ps)
{
  DEBUG_ASSERT(ps != NULL);

#ifdef DEBUG_ICM
  cerr.form("%s %s\n", __FUNCTION__, ps);
#endif

  DEBUG_ASSERT(process_symbol == NULL);

  icmHandle tmp = icmParseHandle(ps);
  
#ifdef DEBUG_ICM      
  cerr.form("%s Before icmRegisterAgent()\n", __FUNCTION__);
#endif
  
  const icmStatus status = icmRegisterAgent(conn, tmp, NULL, &handle);
  
#ifdef DEBUG_ICM
  char buf[MAXSTRING];
  (void) icmHandleName(handle, buf, 512);
  cerr.form("%s After icmRegisterAgent() %s\n", __FUNCTION__, buf);
#endif
  
  switch (status)
    {
    case icmOk:
      (void) icmKeepHandle(handle);
      process_symbol = ps;
      return true;
      break;
    case icmFailed:
      Fatal(__FUNCTION__, "Couldn't register agent name %s\n", ps);
      return false;
      break;
    case icmError:
      Fatal(__FUNCTION__, "ICM comms server unavailable\n");
      return false;
      break;
    case icmEndFile:
      DEBUG_ASSERT(false);
      return false;
      break;
    }
  
  DEBUG_ASSERT(false);
  return false;
}

bool
ICMEnvironment::Unregister(void)
{
  DEBUG_ASSERT(process_symbol != NULL);

#ifdef DEBUG_ICM
  char buf[MAXSTRING];
  (void) icmHandleName(handle, buf, 512);
#endif

#ifdef USE_ICM_DEREGISTER
#ifdef DEBUG_ICM
  cerr.form("%s Before icmDeregisterAgent() %s\n", __FUNCTION__, buf);
#endif
  const icmStatus status = icmDeregisterAgent(conn, handle);
#else
#ifdef DEBUG_ICM
  cerr.form("%s Before qpDeregisterAgent() %s\n", __FUNCTION__, buf);
#endif
  const icmStatus status = qpDeregisterAgent(conn, handle);
#endif
  
#ifdef DEBUG_ICM
  cerr.form("%s After icmDeregisterAgent()\n", __FUNCTION__);
#endif
  
  switch (status)
    {
    case icmOk:
      (void) icmReleaseHandle(handle);
      process_symbol = NULL;
      return true;
      break;
    case icmFailed:
      Warning(__FUNCTION__, "Couldn't deregister agent name %s\n",
	      process_symbol);
      return false;
      break;
    case icmError:
      Warning(__FUNCTION__, "ICM comms server unavailable\n");
      return false;
      break;
    case icmEndFile:
      DEBUG_ASSERT(false);
      return false;
      break;
    }
  
  DEBUG_ASSERT(false);
  return false;
}

#ifndef USE_ICM_DEREGISTER
// TO DO: This procedure is to work around a problem with the
// TO DO: ICM icmDeregisterAgent() mechanism.
// TO DO: It should go away when that code is fixed.
static icmStatus
qpDeregisterAgent(icmConn conn, icmHandle handle)
{
  if(conn!=NULL && conn->socket>0 && conn->server!=NULL)
    {
      icmMsg msg = icmFormatMsg(NULL,"%(icmDeregisterAgent%h%)", handle);
      icmStatus ret = icmSendMsg(conn, conn->server, handle, NULL, msg);
      icmReleaseMsg(msg);

      return ret;
    }
  else
    {
      return icmError;
    }
}
#endif
#endif // ICM_DEF

