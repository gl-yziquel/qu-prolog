/*
 * Support for the ICM-API in Tk
 *
 */

#include "config.h"

#ifdef ICM_DEF
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>  
#include <string.h>  
#include <unistd.h>

#include "icm_support.h"


/* The connection to the ICM server */
static icmConn conn=NULL;

/* Our ICM handle */
static icmHandle ourHandle = NULL;

/* String for general processing */
static char tmp_string[HANDLE_NAME_SIZE];

/* Tcl channel for communication */
static Tcl_Channel channel;

static long seqNo = -LONG_MAX;


/*
 * The Tk-c interface to the ICM comms initialization.
 * Fails if the process has already initialized the comms
 * or if the process can't be initialized.
 */
int 
c_icmInitComms(ClientData clientData, Tcl_Interp *interp,
               int argc, const char *argv[])     
{
    int port;
    if (argc != 3)
    {
      Tcl_SetResult(interp, "Usage: icmInitComms port ipaddress", TCL_STATIC);
      return TCL_ERROR;
    }
    if (conn != NULL)
    {
      Tcl_SetResult(interp, "Process already initialized", TCL_STATIC);
      return TCL_ERROR;
    }
    sscanf(argv[1], "%d", &port);
    initICMIo();
    if (*argv[2] == '\0')
    {
      if(icmInitComms(port,NULL,&conn)!=icmOk)
      {
	Tcl_SetResult(interp, "Failed to initialise process", TCL_STATIC);
        return TCL_ERROR;
      }
    }
    else
    {
	  strcpy(tmp_string, argv[2]); 
      if(icmInitComms(port,tmp_string,&conn)!=icmOk)
      {
	Tcl_SetResult(interp, "Failed to initialise process", TCL_STATIC);
        return TCL_ERROR;
      }
    }
    return TCL_OK;
}

/*
 * The Tk-c interface to icmRegisterAgent.
 * Fails if the process has not been initialized
 * or if the process is currently registered
 * or if the process cannot be registered.
 *
 * The process is registered, a pipe is created
 * and a thread is created that gets ICM messages,
 * decodes them and writes them to the pipe.
 */
int c_icmRegisterAgent(ClientData clientData, Tcl_Interp *interp, 
                       int argc, const char *argv[])
{
    if (argc != 2)
    {
      Tcl_SetResult(interp, "Usage: icmRegisterAgent ?name?", TCL_STATIC);
      return TCL_ERROR;
    }
    if (conn == NULL)
    {
      Tcl_SetResult(interp, "Process not initialized", TCL_STATIC);
      return TCL_ERROR;
    }
    if (ourHandle != NULL)
    {
      Tcl_SetResult(interp, "Process already registered", TCL_STATIC);
      return TCL_ERROR;
    }

    /* Construct handle from supplied process name */
    
	strcpy(tmp_string, argv[1]);
    ourHandle = icmParseHandle(tmp_string);
    
    if(icmRegisterAgent(conn,ourHandle,NULL,&ourHandle)==icmOk)
      {
	/* Get the ICM communications file descriptor */
	int fd = icmCommSocket(conn);
	/* Create a Tcl file channel */
        channel = Tcl_MakeFileChannel((ClientData)fd, TCL_READABLE);
	/* Register the Tcl channel with Tcl */
        Tcl_RegisterChannel(interp, channel);
	/* Return the channel name */
	strcpy(tmp_string, Tcl_GetChannelName(channel));
	Tcl_SetResult(interp, tmp_string, TCL_VOLATILE);
        return TCL_OK;
      }
    else
      {
	ourHandle = NULL;
	Tcl_SetResult(interp, "Failed to register", TCL_STATIC);
        return TCL_ERROR;
      }
}

/*
 * The Tk-c interface to icmDeregisterAgent.
 */
int c_icmDeregisterAgent(ClientData clientData, Tcl_Interp *interp,
                         int argc, const char *argv[])
{
  icmStatus status;
  if (argc != 1)
    {
      Tcl_SetResult(interp, "Usage: icmDeregisterAgent", TCL_STATIC);
      return TCL_ERROR;
    }
  if (ourHandle == NULL)
    {
      Tcl_SetResult(interp, "Process not registered", TCL_STATIC);
      return TCL_ERROR;
    }
  status = icmDeregisterAgent(conn, ourHandle);
  if (status != icmOk)
    {
      Tcl_SetResult(interp, "Cannot deregister", TCL_STATIC);
      return TCL_ERROR;
    }
  
  Tcl_UnregisterChannel(interp, channel);
  
  return TCL_OK;
}

int c_icmGetMsg(ClientData clientData, Tcl_Interp *interp,
                    int argc, const char *argv[])
{
  if (argc != 1)
    {
      Tcl_SetResult(interp, "Usage: icmGetMsg", TCL_STATIC);
      return TCL_ERROR;
    }
  if (ourHandle == NULL)
    {
      Tcl_SetResult(interp, "Process not registered", TCL_STATIC);
      return TCL_ERROR;
    }
  {
    icmHandle recip;
    icmHandle sender;
    icmMsg msg;
    icmOption opts;
    char sender_handle_name[HANDLE_NAME_SIZE];
    char replyto_handle_name[HANDLE_NAME_SIZE];
    icmStatus status = icmGetMsg(conn, &recip, &sender, &opts, &msg, &seqNo);
    switch (status)
      {
      case icmOk:
	{

	  icmDataRec data;
	  if (icmScanMsg(msg, "%S", &data) == icmOk)
	    {
	      Tcl_Obj* tcl_msg[3];
	      Tcl_Obj* tcl_list;
	      icmHandle replyto = sender;
	      // If this call fails, replyto is unchanged
	      (void) icmIsOption(opts, icmReplyto, &replyto);
	      
	      icmHandleName(sender, sender_handle_name,HANDLE_NAME_SIZE);
	      icmHandleName(replyto, replyto_handle_name,HANDLE_NAME_SIZE);
	      
	      tcl_msg[0] = Tcl_NewStringObj(data.data, data.size);
	      tcl_msg[1] = Tcl_NewStringObj(sender_handle_name, -1);
	      tcl_msg[2] = Tcl_NewStringObj(replyto_handle_name, -1);
	      tcl_list = Tcl_NewListObj(3, tcl_msg);
	      Tcl_SetObjResult(interp, tcl_list);

	      free(data.data);
	      icmReleaseMsg(msg);
	      icmReleaseOptions(opts);
	      seqNo = -LONG_MAX;
	    }
	  else
	    {
	      icmReleaseMsg(msg);
	      icmReleaseOptions(opts);
	      exit(0);
	    }
	  break;
	}
      case icmFailed:
	Tcl_SetResult(interp, "icmGetMsg() returned icmFailed", TCL_STATIC);
	return TCL_ERROR;
	break;
      case icmError:
	Tcl_SetResult(interp, "icmGetMsg() returned icmError", TCL_STATIC);
	break;
      case icmEndFile:
	Tcl_SetResult(interp, "ICM Communicatons Server has closed connection",
		      TCL_STATIC);
	break;
      }
  }
  return TCL_OK;
}

int c_icmMsgAvail(ClientData clientData, Tcl_Interp *interp, 
                    int argc, const char *argv[])
{
  if (argc != 1)
    {
      Tcl_SetResult(interp, "Usage: icmMsgAvail", TCL_STATIC);
      return TCL_ERROR;
    }
  if (ourHandle == NULL)
    {
      Tcl_SetResult(interp, "Process not registered", TCL_STATIC);
      return TCL_ERROR;
    }
  if (icmMsgAvail(conn, seqNo) == icmOk)
    {
      Tcl_SetResult(interp, "yes", TCL_STATIC);
    }
  else 
    { 
      Tcl_SetResult(interp, "no", TCL_STATIC);
    }
  return TCL_OK;
}


int c_icmFmtSendMsg(ClientData clientData, Tcl_Interp *interp, 
                    int argc, const char *argv[])
{
    icmHandle tgt;
    icmHandle reply;
    icmDataRec data;
    icmOption opts;
    

    if (argc == 3)
    {
	  strcpy(tmp_string, argv[1]);
      tgt = icmParseHandle(tmp_string);
      data.size = strlen(argv[2]);
      data.data = (char*)argv[2];
      reply = tgt;
    }
    else if (argc == 4)
    {
	  strcpy(tmp_string, argv[1]);
      tgt = icmParseHandle(tmp_string);
      data.size = strlen(argv[3]);
      data.data = (char*)argv[3];
	  strcpy(tmp_string, argv[2]);
      reply = icmParseHandle(tmp_string);
    }
    else
    {
      Tcl_SetResult(interp, "Usage: icmFmtSendMsg ?to_addr? (?from?) ?msg?", 
		    TCL_STATIC);
      return TCL_ERROR;
    }

    opts = icmNewOpt(NULL, icmReplyto, reply);

    if (icmFmtSendMsg(conn, tgt, ourHandle, opts, "%S", &data) == icmOk)
    {
	icmReleaseOptions(opts);
	Tcl_SetResult(interp, "sent", TCL_STATIC);
        return TCL_OK;
    }
    else
    {
	icmReleaseOptions(opts);
	Tcl_SetResult(interp, "unable to send message", TCL_STATIC);
        return TCL_ERROR;
    }
}

#if defined(MACOSX)
int Tkicm_SafeInit(Tcl_Interp *interp)
#else
int Tkicm_Init(Tcl_Interp *interp)
#endif
{
  Tcl_CreateCommand(interp, "icmInitComms", c_icmInitComms,
		    (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
  Tcl_CreateCommand(interp, "icmRegisterAgent", c_icmRegisterAgent,
		    (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
  Tcl_CreateCommand(interp, "icmDeregisterAgent", c_icmDeregisterAgent,
		    (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);
  Tcl_CreateCommand(interp, "icmGetMsg", c_icmGetMsg,
		    (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL); 
  Tcl_CreateCommand(interp, "icmMsgAvail", c_icmMsgAvail,
		    (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);  
  Tcl_CreateCommand(interp, "icmFmtSendMsg", c_icmFmtSendMsg,
		    (ClientData)NULL, (Tcl_CmdDeleteProc *)NULL);     

  return TCL_OK;
}

#endif // ICM_DEF
