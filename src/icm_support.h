// icm_support.h -
// Support for the ICM-API in Tk
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
// $Id: icm_support.h,v 1.5 2003/05/16 01:22:32 qp Exp $

#ifndef ICM_SUPPORT_H
#define ICM_SUPPORT_H

#include "icm.h"
#include "icmP.h"
#include "icmFile.h"
#include "tcl.h"

/*
 * Tk interface function declarations

int c_icmInitComms(ClientData clientData, Tcl_Interp *interp,
                       int argc, char *argv[]);
int c_icmRegisterAgent(ClientData clientData, Tcl_Interp *interp,
                       int argc, char *argv[]);
int c_icmDeregisterAgent(ClientData clientData, Tcl_Interp *interp,
                       int argc, char *argv[]);
int c_icmGetMsg(ClientData clientData, Tcl_Interp *interp,
                    int argc, char *argv[]);
int c_icmMsgAvail(ClientData clientData, Tcl_Interp *interp,
                    int argc, char *argv[]);
int c_icmFmtSendMsg(ClientData clientData, Tcl_Interp *interp,
                    int argc, char *argv[]);

 */
/*
 * Declarations of some string sizes
 */

#define MAXSTRING 1024
/* Size of the buffer to hold message string */
#define MSG_SIZE 10000  
/* Size of string to hold handle name */
#define HANDLE_NAME_SIZE 10000
/* Size of the string for holding the Tk file handle */
#define TK_FILE_HANDLE_SIZE 20
/* ICM message delimiters for transfer to Tk */
#define ICM_END_MESSAGE "$$EICMM$$"
#define ICM_MESSAGE_SEPARATOR_SIZE 9
#define ICM_MESSAGE_SEPARATOR "$$SICMA$$"
#define ICM_ADDRESS_SEPARATOR_SIZE 9
#define ICM_ADDRESS_SEPARATOR "$$ICMAS$$"


#endif // ICM_SUPPORT_H



