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
icmConn conn=NULL;

/* Our ICM handle */
icmHandle ourHandle = NULL;

/* Our handle name */
char handle_name[HANDLE_NAME_SIZE];

/* The pipe for connecting the ICM message in thread to the main (Tk) thread */
int icm_msg_pipe[2];

/* Tcl channel for the pipe */
Tcl_Channel channel;

/*
 * The icm event loop - executed as a sub-thread
 *
 * Assumes all messages sent to this process are ICM-strings.
 */
void * icm_thread_event_loop()
{
    long seqNo = -LONG_MAX;
    icmHandle recip;
    icmHandle sender;
    icmMsg msg;
    icmOption opts;
    size_t len;
    char sender_handle_name[HANDLE_NAME_SIZE];
    char replyto_handle_name[HANDLE_NAME_SIZE];

    for(;;)
    {
        icmDataRec data;
        icmHandle hh;
        char res[MAXSTRING];
        icmGetMsg(conn, &recip, &sender, &opts, &msg, &seqNo);
	if (icmScanMsg(msg, "%S", &data) == icmOk)
        {
	    icmHandle replyto = sender;
            // If this call fails, replyto is unchanged
            (void) icmIsOption(opts, icmReplyto, &replyto);

	    icmHandleName(sender, sender_handle_name,HANDLE_NAME_SIZE);
	    icmHandleName(replyto, replyto_handle_name,HANDLE_NAME_SIZE);
	    write(icm_msg_pipe[1], data.data, data.size);
	    len = strlen(ICM_MESSAGE_SEPARATOR);
	    write(icm_msg_pipe[1], ICM_MESSAGE_SEPARATOR, len);
	    len = strlen(sender_handle_name);
	    write(icm_msg_pipe[1], sender_handle_name, len);
	    len = strlen(ICM_ADDRESS_SEPARATOR);
	    write(icm_msg_pipe[1], ICM_ADDRESS_SEPARATOR, len);
	    len = strlen(replyto_handle_name);
	    write(icm_msg_pipe[1], replyto_handle_name, len);
	    len = strlen(ICM_END_MESSAGE);
	    write(icm_msg_pipe[1], ICM_END_MESSAGE, len);
            free(data.data);
	    icmReleaseMsg(msg);
	    icmReleaseOptions(opts);
	    seqNo = -LONG_MAX;
        }
        else 
        if (sender == conn->server
            && icmScanMsg(msg,"%(icmDeregisterAgent%s%h%)",&res,&hh)==icmOk
            && icmSameAgentHandle(hh,ourHandle)==icmOk)
        {
            icmReleaseMsg(msg);
            icmReleaseOptions(opts);
            exit(0);
        }

    }
    return NULL;
}


/*
 * The Tk-c interface to the ICM comms initialization.
 * Fails if the process has already initialized the comms
 * or if the process can't be initialized.
 */
int 
c_icmInitComms(ClientData clientData, Tcl_Interp *interp,
               int argc, char *argv[])     
{
    int port;
    if (argc != 3)
    {
        interp->result = "Usage: icmInitComms port ipaddress";
        return TCL_ERROR;
    }
    if (conn != NULL)
    {
        interp->result = "Process already initialized";
	 return TCL_ERROR;
    }
    sscanf(argv[1], "%d", &port);
    if (*argv[2] == '\0')
    {
      if(icmInitComms(port,NULL,&conn)!=icmOk)
      {
        interp->result = "Failed to initialise process";
        return TCL_ERROR;
      }
    }
    else
    {
      if(icmInitComms(port,argv[2],&conn)!=icmOk)
      {
        interp->result = "Failed to initialise process";
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
                       int argc, char *argv[])
{
    if (argc != 2)
    {
        interp->result = "Usage: icmRegisterAgent ?name?";
        return TCL_ERROR;
    }
    if (conn == NULL)
    {
        interp->result = "Process not initialized";
	 return TCL_ERROR;
    }
    if (ourHandle != NULL)
    {
        interp->result = "Process already registered";
	 return TCL_ERROR;
    }

    /* Construct handle from supplied process name */

    ourHandle = icmParseHandle(argv[1]);

    if(icmRegisterAgent(conn,ourHandle,NULL,&ourHandle)==icmOk)
    {
	pthread_t icm_thread;
        char tk_file_handle[TK_FILE_HANDLE_SIZE];

	/* Open the pipe */
	if (pipe(icm_msg_pipe) == -1)
	{
	     ourHandle = NULL;
             interp->result = "Unable to open pipe";
             return TCL_ERROR;
	}

	/* Start the sub-thread for processing ICM messages */

	pthread_create(&icm_thread, NULL, icm_thread_event_loop, NULL);   

	/* Create a Tcl file channel */
        channel = Tcl_MakeFileChannel((ClientData)icm_msg_pipe[0], 
	                              TCL_READABLE);
	/* Create the file handle string */
        sprintf(tk_file_handle, "file%d",icm_msg_pipe[0]);
	/* Register the Tcl channel with Tcl */
        Tcl_RegisterChannel(interp, channel);
	/* Return the file handle */
        strcpy(interp->result, tk_file_handle);
        return TCL_OK;
	}
    else
    {
	ourHandle = NULL;
        interp->result = "Failed to register";
        return TCL_ERROR;
    }
}

/*
 * The Tk-c interface to icmDeregisterAgent.
 */
int c_icmDeregisterAgent(ClientData clientData, Tcl_Interp *interp,
                         int argc, char *argv[])
{
    icmMsg msg;
    
    if (argc != 1)
    {
        interp->result = "Usage: icmDeregisterAgent";
        return TCL_ERROR;
    }
    if (ourHandle == NULL)
    {
        interp->result = "Process not registered";
	 return TCL_ERROR;
    }

    msg = icmFormatMsg(NULL,"%(icmDeregisterAgent%h%)",ourHandle);
    icmSendMsg(conn,conn->server,ourHandle,NULL,msg);
    icmReleaseMsg(msg);

    ourHandle = NULL;
    if (close(icm_msg_pipe[0]) == -1)
    {
         interp->result = "Cannot close pipe0";
         return TCL_ERROR;
    }
    if (close(icm_msg_pipe[1]) == -1)
    {
         interp->result = "Cannot close pipe1";
         return TCL_ERROR;
    }
    Tcl_UnregisterChannel(interp, channel);
    
    return TCL_OK;
}

int c_icmFmtSendMsg(ClientData clientData, Tcl_Interp *interp, 
                    int argc, char *argv[])
{
    icmHandle tgt;
    icmHandle reply;
    icmDataRec data;
    icmOption opts;
    

    if (argc == 3)
    {
      tgt = icmParseHandle(argv[1]);
      data.size = strlen(argv[2]);
      data.data = argv[2];
      reply = tgt;
    }
    else if (argc == 4)
    {
      tgt = icmParseHandle(argv[1]);
      data.size = strlen(argv[3]);
      data.data = argv[3];
      reply = icmParseHandle(argv[2]);
    }
    else
    {
        interp->result = "Usage: icmFmtSendMsg ?to_addr? (?from?) ?msg?";
        return TCL_ERROR;
    }

    opts = icmNewOpt(NULL, icmReplyto, reply);

    if (icmFmtSendMsg(conn, tgt, ourHandle, opts, "%S", &data) == icmOk)
    {
	icmReleaseOptions(opts);
        interp->result = "sent";
        return TCL_OK;
    }
    else
    {
	icmReleaseOptions(opts);
        interp->result = "unable to send message";
        return TCL_ERROR;
    }
}

#endif // ICM_DEF
