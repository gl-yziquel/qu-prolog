// token.h -     Qu-Prolog tokeniser
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
// $Id: token.h,v 1.2 2002/11/10 07:54:55 qp Exp $

#ifndef TOKEN_H
#define TOKEN_H

private:
//
// Look up the classification of a character.
//
inline int8 InType(const char c);

//
// Look up the digital value of a character.
//
inline int32 DigVal(const char c);

//
// true if it is a space.
// 
inline bool IsLayout(const char c);
 
// 
// Output messages for detected syntax errors. 
//
inline void SyntaxError(int32& Integer, const int32 err);

//
// Peek ahead one character
//
inline int Peek(QPStream *InStrm, const word32);

//
// Echo a read prompt.
//
// Retained for historical reasons.
//
inline void ReadPrompt(const QPStream *, const char);

//
// Recover from a numeric error.
//
inline void RecoverNumber(QPStream *InStrm, const int32 base);

//
// Recover from a name that is too long.
//
inline void RecoverName(QPStream *InStrm);

//
// Recover from a quoted name.
//
inline void RecoverQuotedName(QPStream *InStrm, const bool put);

//
// Get a character.
//
inline int Get(QPStream *InStrm);

//
// Put back a character or clear EOF.
//
inline void Putback(QPStream *InStrm, const int c);

//
// ReadCharacter(Stream *InStrm, int8 q)
// Reads one character from a quoted atom or list.
// Two adjacent quotes are read as a single character, otherwise a quote is
// returned as 0.  Error is returned as -1.  If the input syntax has character
// escapes, they are processed.
// \xhh sequences are two hexadecimal digits long.
// Note that the \c sequence allows continuation of strings.  For example:
//     "This is a string, which \c
//      has to be continued over \c
//      several lines.\n".
//
int32 ReadCharacter(QPStream *InStrm, const char q, int32& Integer);

//
// GetToken() reads a single token from the input stream and returns the
// token type.  The value of the token is stored in one of the
// variables: Integer, Simple, String.
//
int32 GetToken(QPStream *InStrm, int32& Integer, char *Simple, Object*& String);

public:
//
// psi_read_next_token(stream, var, var)
//
// Read a token from the stream and return the token type and value.
// mode(in,out,out)
//
ReturnValue psi_read_next_token(Object *&, Object *&, Object *&);

#endif	// TOKEN_H
