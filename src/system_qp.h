// system_qp.h - Functions which use system to call CShell commands and
//           syscall to call system commands.
//
// ##Copyright##
// 
// Copyright (C) 2000-Tue May 12 09:17:22 AEST 2015 
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
// $Id: system_qp.h,v 1.4 2004/11/24 00:12:35 qp Exp $

#ifndef SYSTEM_QP_H
#define SYSTEM_QP_H

public:
//
// psi_system(constant, var)
// X0 is a string for CShell commands. X1 is unified with the return
// value from the call to the function system.
// mode(in,out)
//
ReturnValue	psi_system(Object *& , Object *& );

//
// psi_access(atom, integer, var)
// Check the file in X0 whether has the mode in X1.  Return the result in X2.
// mode(in,in,out)
//
ReturnValue	psi_access(Object *& , Object *& , Object *& );

//
// psi_absolute_path(atom, atom)
// Get the full path name
// mode(in, out)
//
ReturnValue	psi_absolute_path(Object *& , Object *&);

//
// psi_chdir(atom)
// Change directory to dir given by the argument
// mode(in)
//
ReturnValue	psi_chdir(Object *&);

//
// psi_getcwd(atom)
// Get the current working directory
// mode(out)
//
ReturnValue	psi_getcwd(Object *&);

//
// psi_mktemp(atom, var)
// Return a temporary file name.
// mode(in,out)
//
ReturnValue	psi_mktemp(Object *& , Object *& );

//
// psi_realtime(-Integer)
//
// Returns system time.
//
ReturnValue psi_realtime(Object *&);

//
// psi_gmtime(?Integer, ?timestruct)
//
// psi_gmtime(Time, TimeStruct) succeeds if
// Time is the Unix Epoch time corresponding to the time given in
// TimeStruct which is of the form gmt_time(Year, Mth, Day, Hours, Mins, Secs)
ReturnValue psi_gmtime(Object *& , Object *& );

//
// psi_localtime(?Integer, ?timestruct)
//
// psi_localtime(Time, TimeStruct) succeeds if
// Time is the Unix Epoch time corresponding to the time given in
// TimeStruct which is of the form 
// local_time(Year, Mth, Day, Hours, Mins, Secs)
ReturnValue psi_localtime(Object *& , Object *& );

// @user
// @pred signal_to_atom(SignalNumber, SignalAtom)
// @type signal_to_atom(integer, atom)
// @mode signal_to_atom(+, -) is det
// @description
// Takes a signal number and maps it to the appropriate signal string.
// @end pred
// @end user
ReturnValue psi_signal_to_atom(Object *&, Object *&);

// @doc
// @pred nsig(NSIG)
// @type nsig(integer)
// @mode nsig(-) is det
// @description
// Returns the number of signals on this machine.
// @end pred
// @end user
ReturnValue psi_nsig(Object *&);

// @user
// @pred strerror(Errno, String)
// @type strerror(integer, atom)
// @mode strerror(in, out) is det
// @description
// An interface to the strerror(3C) call.
// @end pred
// @end doc
ReturnValue psi_strerror(Object *&, Object *&);



ReturnValue psi_stat(Object *&, Object *&);

#endif // SYSTEM_QP_H

