// io_qp.h - High level I/O management.
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
// $Id: io_qp.h,v 1.3 2001/05/23 21:52:35 qp Exp $

#ifndef	IO_QP_H
#define	IO_QP_H

#include <sys/file.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdiostream.h>
#include <strstream.h>
#include <fstream.h>
#include <string.h>
#include <unistd.h>

#include "config.h"

#include "defs.h"

#include "icm_environment.h"
//#include "thread.h"

class Thread;

enum AccessMode	{
  AM_READ = 0,
  AM_WRITE = 1,
  AM_APPEND = 2
};

enum IOType {
  ISTREAM,
  OSTREAM,
  ISTRSTREAM,
  OSTRSTREAM,
  IMSTREAM,
  OMSTREAM,
  SOCKET
};

enum IODirection {
  INPUT,
  OUTPUT,
  INPUT_OUTPUT
};

//
// FD is a class for forcing streams that deal with the outside world
// to deal with the possibility of blocking on i/o.
//
class FD
{
protected:
  int fd;

  const IOType type;
  
public:
  FD(const int f, const IOType t)
    : fd(f), type(t) { }

  virtual ~FD(void) { }

  int getFD(void) const { return fd; }
  void setFD(const int f) { fd = f; }

  IOType Type(void) const { return type; }

  bool isInput(void) const 
    { return (type == ISTREAM) || (type == ISTRSTREAM) || (type == IMSTREAM); }
  bool isOutput(void) const 
    { return (type == OSTREAM) || (type == OSTRSTREAM) || (type == OMSTREAM); }
  bool isInputOutput(void) const 
    { return type == SOCKET; }

  virtual bool isEnded(void) const = 0;

  // Ready for action?
  virtual bool isReady(void) const = 0;

};

//-----------------------------------------------
//
// Sockets
//
//-----------------------------------------------

class Socket : public FD
{
private:
  enum socketStatus {
    SS_INIT, SS_SOCKET, SS_BIND, SS_LISTEN,
    SS_ACCEPT, SS_CONNECTED, SS_CLOSED
    } sstatus;

  enum socketMode {
    SM_INIT, SM_CONNECTION, SM_CONNECTIONLESS
    } smode;

  //
  // Type and protocol.
  //
  int stype;
  int sproto;
  int istream;
  int ostream;

public:
  Socket(const int t, const int p, const int f);
  
  ~Socket(void)
  {
    closeSocket();
  }
  
  void setIStream(int i) { istream = i; }
  void setOStream(int o) { ostream = o; }

  int getIStream(void) { return istream; }
  int getOStream(void) { return ostream; }

  void setConnection(void)	{ smode = SM_CONNECTION; }
  void setConnectionless(void)	{ smode = SM_CONNECTIONLESS; }
  
  // Setting status
  void setSocket(void)		{ sstatus = SS_SOCKET; }
  void setBind(void)		{ sstatus = SS_BIND; }
  void setListen(void)		{ sstatus = SS_LISTEN; }
  void setAccept(void)		{ sstatus = SS_ACCEPT; }
  void setConnected(void)	{ sstatus = SS_CONNECTED; }
  void setClose(void)		{ sstatus = SS_CLOSED; }
  
  // Testing status and mode
  bool isSocket(void) const	{ return sstatus == SS_SOCKET; }
  bool isSocketAllowed(void) const	{ return sstatus == SS_INIT; }
  bool isBindAllowed(void) const	{ return sstatus == SS_SOCKET; }
  bool isListenAllowed(void) const
  {
    return smode == SM_CONNECTION && sstatus == SS_BIND;
  }
  bool isAcceptAllowed(void) const
  {
    return smode == SM_CONNECTION && sstatus == SS_LISTEN;
  }
  bool isConnectAllowed(void) const;
  bool isSendAllowed(void) const
  {
    return ((smode == SM_CONNECTION || smode == SM_CONNECTIONLESS) &&
	    sstatus == SS_CONNECTED);
  }
  bool isRecvAllowed(void) const
  {
    return ((smode == SM_CONNECTIONLESS &&
	     (sstatus == SS_SOCKET ||
	      sstatus == SS_BIND ||
	      sstatus == SS_CONNECTED)) ||
	    (smode == SM_CONNECTION && sstatus == SS_CONNECTED));
  }
  bool isSendtoAllowed(void) const;
  bool isRecvfromAllowed(void) const;
  bool isSendbrAllowed(void) const
  {
    return isBroadcast() && sstatus == SS_BIND;
  }
  bool isCloseAllowed(void) const { return sstatus != SS_INIT; }
  
  // Testing mode
  bool isConnection(void) const	{ return smode == SM_CONNECTION;}
  bool isConnectionless(void) const { return smode == SM_CONNECTIONLESS; }
  
  // Testing availability for i/o operations
  bool isBroadcast(void) const;

  // Opening and closing
  bool openSocket(const int, const int);
  bool closeSocket(void);
  
  // Accept
  void setAccepted(Socket *, const int);
  
  // Ready for action?
  virtual bool isReady(void) const;

  // Finished for IO?
  virtual bool isEnded(void) const;
};

//-----------------------------------------------
//
// Streams
//
//-----------------------------------------------

class imstream
{
private:
  // a read/write buffer.
  //
  strstreambuf* sb;
  istream* strin;
  ostream* strout;
  // the icm handle for incoming messages.
  icmHandle sender_handle;
  // the thread pointer to the thread that opened the stream
  Thread* thread;

  list<ICMMessage *>::iterator *iter;
  
  bool found;

  bool msg_ready(void);
  void get_a_msg(void);

public:
  imstream(icmHandle handle, Thread* th)
    {
      sb = new strstreambuf(128);
      strin = new istream(sb);
      strout = new ostream(sb);
      sender_handle = handle;
      thread = th;
      iter = new list<ICMMessage *>::iterator;
      found = false;
    }
      
  virtual ~imstream(void)
    {
      delete strin;
      delete strout;
      delete sb;
    }

  inline Thread*  getThread(void)
    {
      return thread;
    }

  inline bool isFound(void)
    {
      return found;
    }

  inline void setFound(void)
    {
      found = true;
    }

  inline icmHandle getSenderHandle(void)
    {
      return sender_handle;
    }

  inline list<ICMMessage *>::iterator * getIter(void)
    {
      return iter;
    }

  inline bool seekg(streampos pos, ios::seekdir d = ios::beg)
    {
      return (!strin->seekg(pos, d).fail());
    }

  inline bool eof(void)
    {
      return (strin->eof());
    }

  inline bool is_at_eof(void)
    {
      strin->get(); 
      strin->unget();
      return strin->eof();
    }

  inline bool fail(void)
    {
      return strin->fail();
    }

  inline void clear(ios::iostate state_arg = ios::goodbit)
    {
      strin->clear(state_arg);
    }

  inline bool get(char& ch)
    {
      if (is_at_eof())
	{
	  get_a_msg();
	}
      return (!strin->get(ch).fail());
    }

  inline int get(void)
    {
      if (is_at_eof())
	{
	  get_a_msg();
	}
      return (strin->get());
    }

  inline bool unget(void)
    {
      return (!strin->unget().fail());
    }
  
  inline int peek(void)
    {
      return strin->peek();
    }

  inline bool good(void)
    {
      return strin->good();
    }

};

class omstream
{
private:
  icmHandle to_handle;
  Thread* sender_thread;
  ICMEnvironment* icm_environment;
  
  ostrstream* ostrm;

  void send_msg(void);

public:
  omstream(icmHandle thandle, Thread* thread, ICMEnvironment* icm_env)
    {
      to_handle = thandle;
      sender_thread = thread;
      icm_environment = icm_env;
      ostrm = new ostrstream();
    }

  virtual ~omstream(void)
    {
      delete ostrm;
    }

  inline bool fail(void)
    {
      return ostrm->fail();
    }

  inline void clear(ios::iostate state_arg = ios::goodbit)
    {
      ostrm->clear(state_arg);
    }

  inline bool put(char ch)
    {
      if (ostrm->put(ch).fail())
	{
	  return false;
	}
      send_msg();
      return true;
    }
  
  inline void operator<<(const char c)
    {
      (*ostrm) << c;
      send_msg();
    }

  inline void operator<<(const char* s)
    {
      (*ostrm) << s;
      send_msg();
    }

  inline void operator<<(const int n)
    {
      (*ostrm) << n;
      send_msg();
    }

  inline void form(const char* formstr, const word32 data)
    {
      ostrm->form(formstr, data);
      send_msg();
    }

  inline int tell(void)
    {
      return (ostrm->tellp());
    }

  inline bool good(void)
    {
      return (ostrm->good());
    }

};

//
// Basic stream class. These streams aren't capable of dealing with
// the outside world, and are only intended as a base class for
// further refinement.
//
class Stream : public FD
{
private:
  //
  // Status of the stream.
  //
  union	{
    istream	*i_stream;
    istrstream  *i_strstream;
    ostream	*o_stream;
    ostrstream  *o_strstream;
    imstream    *i_mstream;
    omstream    *o_mstream;
  } desc;

  //
  // A closeable flag
  //
  bool closeable;

  //
  // Line counter.
  //
  word32	lineCounter;

  heapobject* properties;

public:
  //
  // An explicit fd is supplied.
  //
  Stream(istream *is, const int f = EOF)
    : FD(f, ISTREAM)
  {
    lineCounter = 1;
    desc.i_stream = is;
    closeable = (is != &cin);
    properties = new heapobject[Structure::size(7)];
  }
  Stream(ostream *os, const int f = EOF)
    : FD(f, OSTREAM)
  {
    lineCounter = 1;
    desc.o_stream = os;
    closeable = ((os != &cout) || (os != &cerr));
    properties = new heapobject[Structure::size(7)];
  }

  //
  // Things with a meaningful fd.
  //
  Stream(ifstream *is)
    : FD(is->rdbuf()->fd(), ISTREAM)
  {
    lineCounter = 1;
    desc.i_stream = is;
    closeable = true;
    properties = new heapobject[Structure::size(7)];
  }
  Stream(ofstream *os)
    : FD(os->rdbuf()->fd(), OSTREAM)
  {
    lineCounter = 1;
    desc.o_stream = os;
    closeable = true;
    properties = new heapobject[Structure::size(7)];
  }

  //
  // Things without a meaningful fd.
  //
  Stream(istrstream *istrm)
    : FD(EOF, ISTRSTREAM)
  {
    lineCounter = 1;
    desc.i_strstream = istrm;
    closeable = true;
    properties = new heapobject[Structure::size(7)];
  }
  Stream(ostrstream *ostrm)
    : FD(EOF, OSTRSTREAM)
  {
    lineCounter = 1;
    desc.o_strstream = ostrm;
    closeable = true;
    properties = new heapobject[Structure::size(7)];
  }

  Stream(imstream *imstrm)
    : FD(EOF, IMSTREAM)
  {
    lineCounter = 1;
    desc.i_mstream = imstrm;
    closeable = true;
    properties = new heapobject[Structure::size(7)];
  }

  Stream(omstream *omstrm)
    : FD(EOF, OMSTREAM)
  {
    lineCounter = 1;
    desc.o_mstream = omstrm;
    closeable = true;
    properties = new heapobject[Structure::size(7)];
  }

  ~Stream(void)
  {
    delete[] properties;

    if (closeable)
      {
	close();
      }
  }

  void setProperties(Object* prop);
  // set the properties for a default read string stream.
  void setRSProperties(void);

  Object* getProperties(void)
    {
      return (reinterpret_cast<Object*>(properties));
    }

  //
  // Close the active stream.
  //
  void close(void)
  {
    switch (type)
      {
      case ISTREAM:
	{
	  delete desc.i_stream;
	  desc.i_stream = NULL;
	}
	break;
      case OSTREAM:
	{
	  delete desc.o_stream;
	  desc.o_stream = NULL;
	}
	break;
      case ISTRSTREAM:
	{
	  delete desc.i_strstream;
	  desc.i_strstream = NULL;
	}
	break;
      case OSTRSTREAM:
	{
	  delete desc.o_strstream;
	  desc.o_strstream = NULL;
	}
	break;
      case IMSTREAM:
	{
	  delete desc.i_mstream;
	  desc.i_mstream = NULL;
	}
	break;
     case OMSTREAM:
	{
	  delete desc.o_mstream;
	  desc.o_mstream = NULL;
	}
	break;
      default:
	DEBUG_ASSERT(false);
	break;
      }
  }

  //
  // Change the line counter.
  //
  void	newline(void);
  void	unnewline(void);
  
  //
  // Return the current line number.
  //
  word32 lineNumber(void)	{ return(lineCounter); }

  //
  // Is the stream finished?
  //
  virtual bool isEnded(void) const;

  // Ready for action?
  virtual bool isReady(void) const;

  // 
  // Is the streem NULL?
  //
  inline bool isEmpty(void)
    {
      return (desc.i_stream == NULL);
    }

  // 
  //  Get the stream direction.
  //
  inline IODirection getDirection(void)
    {
      switch (type)
	{
	case ISTREAM:
	case ISTRSTREAM:
	case IMSTREAM:
	  return INPUT;
	  break;
	case OSTREAM:
	case OSTRSTREAM:
	case OMSTREAM:
	  return OUTPUT;
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return OUTPUT;
	  break;
	}
    }

  // support for imstreams
  //
  inline bool is_at_eof(void)
  {
  	DEBUG_ASSERT(type == IMSTREAM);
	return desc.i_mstream->is_at_eof();
  }

  inline list<ICMMessage *>::iterator * getIter(void)
    {
  	DEBUG_ASSERT(type == IMSTREAM);
	return desc.i_mstream->getIter();
    }

  inline Thread* getThread(void)
    {
  	DEBUG_ASSERT(type == IMSTREAM);
	return desc.i_mstream->getThread();
    }

  inline bool isFound(void)
    {
  	DEBUG_ASSERT(type == IMSTREAM);
	return desc.i_mstream->isFound();
    }

  inline void setFound(void)
    {
  	DEBUG_ASSERT(type == IMSTREAM);
	desc.i_mstream->setFound();
    }                                

  //
  // Versions of the standard IO methods for this class.
  //
  inline bool seekg(streampos pos, ios::seekdir d = ios::beg)
    {
      switch (type)
	{
	case ISTREAM:
	  return (!desc.i_stream->seekg(pos, d).fail());
	  break;
	case ISTRSTREAM:
	  return (!desc.i_strstream->seekg(pos, d).fail());
	  break;
	case IMSTREAM:
	  return (desc.i_mstream->seekg(pos, d));
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return false;
	  break;
	}
    }

  inline bool eof(void)
    {
      switch (type)
	{
	case ISTREAM:
	  //return (desc.i_stream->eof());
	  return (desc.i_stream->peek() == EOF);
	  break;
	case ISTRSTREAM:
	  //return (desc.i_strstream->eof());
	  return (desc.i_strstream->peek() == EOF);
	  break;
	case IMSTREAM:
	  return (desc.i_mstream->eof());
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return false;
	  break;
	}
    }

  inline bool fail(void)
    {
      switch (type)
	{
	case ISTREAM:
	  return (desc.i_stream->fail());
	  break;
	case OSTREAM:
	  return (desc.o_stream->fail());
	  break;
	case ISTRSTREAM:
	  return (desc.i_strstream->fail());
	  break;
	case OSTRSTREAM:
	  return (desc.o_strstream->fail());
	  break;
	case IMSTREAM:
	  return (desc.i_mstream->fail());
	  break;
	case OMSTREAM:
	  return (desc.o_mstream->fail());
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return false;
	  break;
	}
    }


  inline void clear(ios::iostate state_arg = ios::goodbit)
    {
      switch (type)
	{
	case ISTREAM:
	  desc.i_stream->clear(state_arg);
	  break;
	case OSTREAM:
	  desc.o_stream->clear(state_arg);
	  break;
	case ISTRSTREAM:
	  desc.i_strstream->clear(state_arg);
	  break;
	case OSTRSTREAM:
	  desc.o_strstream->clear(state_arg);
	  break;
	case IMSTREAM:
	  desc.i_mstream->clear(state_arg);
	  break;
	case OMSTREAM:
	  desc.o_mstream->clear(state_arg);
	  break;
	default:
	  DEBUG_ASSERT(false);
	  break;
	}
    }

  inline bool get(char& ch)
    {
      switch (type)
	{
	case ISTREAM:
	  return (!desc.i_stream->get(ch).fail());
	  break;
	case ISTRSTREAM:
	  return (!desc.i_strstream->get(ch).fail());
	  break;
	case IMSTREAM:
	  return (desc.i_mstream->get(ch));
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return false;
	  break;
	}
    }

  inline int get(void)
    {
      switch (type)
	{
	case ISTREAM:
	  return (desc.i_stream->get());
	  break;
	case ISTRSTREAM:
	  return (desc.i_strstream->get());
	  break;
	case IMSTREAM:
	  return (desc.i_mstream->get());
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return -1;
	  break;
	}
    }

  inline bool unget(void)
    {
      switch (type)
	{
	case ISTREAM:
	  return (!desc.i_stream->unget().fail());
	  break;
	case ISTRSTREAM:
	  return (!desc.i_strstream->unget().fail());
	  break;
	case IMSTREAM:
	  return (desc.i_mstream->unget());
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return false;
	  break;
	}
    }

  inline bool seekp(streampos pos, ios::seekdir d = ios::beg)
    {
      switch (type)
	{
	case OSTREAM:
	  return (!desc.o_stream->seekp(pos, d).fail());
	  break;
	case OSTRSTREAM:
	  return (!desc.o_strstream->seekp(pos, d).fail());
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return false;
	  break;
	}
    }


  inline int peek(void)
    {
      switch (type)
	{
	case ISTREAM:
	  return desc.i_stream->peek();
	  break;
	case ISTRSTREAM:
	  return desc.i_strstream->peek();
	  break;
	case IMSTREAM:
	  return desc.i_mstream->peek();
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return false;
	  break;
	}
    }

  inline bool put(char ch)
    {
      switch (type)
	{
	case OSTREAM:
	  return (!desc.o_stream->put(ch).fail());
	  break;
	case OSTRSTREAM:
	  return (!desc.o_strstream->put(ch).fail());
	  break;
	case OMSTREAM:
	  return (desc.o_mstream->put(ch));
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return false;
	  break;
	}
    }

  inline char* str(void)
    {
      switch (type)
	{
	case OSTRSTREAM:
	  return desc.o_strstream->str();
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return NULL;
	  break;
	}
    }

  inline int pcount(void)
    {
      switch (type)
	{
	case OSTRSTREAM:
	  return desc.o_strstream->pcount();
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return 0;
	  break;
	}
    }

  inline void operator<<(const char c)
    {
      switch (type)
	{
	case OSTREAM:
	  *(desc.o_stream) << c;
	  break;
	case OSTRSTREAM:
	  *(desc.o_strstream) << c;
	  break;
	case OMSTREAM:
	  *(desc.o_mstream) << c;
	  break;
	default:
	  DEBUG_ASSERT(false);
	  break;
	}
    }

  inline void operator<<(const char* s)
    {
      switch (type)
	{
	case OSTREAM:
	  *(desc.o_stream) << s;
	  break;
	case OSTRSTREAM:
	  *(desc.o_strstream) << s;
	  break;
	case OMSTREAM:
	  *(desc.o_mstream) << s;
	  break;
	default:
	  DEBUG_ASSERT(false);
	  break;
	}
    }

  inline void operator<<(const int n)
    {
      switch (type)
	{
	case OSTREAM:
	  *(desc.o_stream) << n;
	  break;
	case OSTRSTREAM:
	  *(desc.o_strstream) << n;
	  break;
	case OMSTREAM:
	  *(desc.o_mstream) << n;
	  break;
	default:
	  DEBUG_ASSERT(false);
	  break;
	}
    }

  inline void form(const char* formstr, const word32 data)
    {
      switch (type)
	{
	case OSTREAM:
	  desc.o_stream->form(formstr, data);
	  break;
	case OSTRSTREAM:
	  desc.o_strstream->form(formstr, data);
	  break;
	case OMSTREAM:
	  desc.o_mstream->form(formstr, data);
	  break;
	default:
	  DEBUG_ASSERT(false);
	  break;
	}
    }

  inline void flush(void)
    {
      switch (type)
	{
	case OSTREAM:
	  desc.o_stream->flush();
	  break;
	case OSTRSTREAM:
	  desc.o_strstream->flush();
	  break;
	case OMSTREAM:
	  break;
	default:
	  DEBUG_ASSERT(false);
	  break;
	}
    }

  inline bool frozen(void)
    {
      switch (type)
	{
	case OSTRSTREAM:
	  return (desc.o_strstream->frozen());
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return false;
	  break;
	}
    }

  inline void freeze(int fr = 1)
    {
      switch (type)
	{
	case OSTRSTREAM:
	  desc.o_strstream->freeze(fr);
	  break;
	default:
	  DEBUG_ASSERT(false);
	  break;
	}
    }

  inline int tell(void)
    {
      switch (type)
	{
	case ISTREAM:
	  return (desc.i_stream->tellg());
	  break;
	case OSTREAM:
	  return (desc.o_stream->tellp());
	  break;
	case ISTRSTREAM:
	  return (desc.i_strstream->tellg());
	  break;
	case OSTRSTREAM:
	  return (desc.o_strstream->tellp());
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return -1;
	  break;
	}
    }

  inline bool good(void)
    {
      switch (type)
	{
	case ISTREAM:
	  return (desc.i_stream->good());
	  break;
	case OSTREAM:
	  return (desc.o_stream->good());
	  break;
	case ISTRSTREAM:
	  return (desc.i_strstream->good());
	  break;
	case OSTRSTREAM:
	  return (desc.o_strstream->good());
	  break;
	case IMSTREAM:
	  return (desc.i_mstream->good());
	  break;
	case OMSTREAM:
	  return (desc.o_mstream->good());
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return false;
	  break;
	}
    }

  inline icmHandle getSenderHandle(void)
    {
      switch (type)
	{
	case IMSTREAM:
	  return (desc.i_mstream->getSenderHandle());
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return (desc.i_mstream->getSenderHandle());
	  break;
	}
    }

};

//
// Maintains a record of the current streams.
// This role might be expanded in future.
//
class IOManager
{
private:
  Stream* open_streams[NUM_OPEN_STREAMS];
  int current_input;
  int current_output;
  int current_error;
  Stream* save_stdin;
  Stream* save_stdout;
  Stream* save_stderr;
  
public:
  IOManager(Stream *in, Stream *out, Stream *error)
  {
    for (u_int i = 0; i < NUM_OPEN_STREAMS; i++)
      {
	open_streams[i] = NULL;
      }
    DEBUG_ASSERT(in != NULL);
    DEBUG_ASSERT(out != NULL);
    DEBUG_ASSERT(error != NULL);
    save_stdin = in;
    save_stdout = out;
    save_stderr = error;
    open_streams[0] = in;
    open_streams[1] = out;
    open_streams[2] = error;
    current_input = 0;
    current_output = 1;
    current_error = 2;
  }
  
  ~IOManager(void) { }
  
  const Stream *StdIn(void) { return open_streams[0]; }
  const Stream *StdOut(void) { return open_streams[1]; }
  const Stream *StdErr(void) { return open_streams[2]; }

  int CurrentInput(void) { return current_input; }
  int CurrentOutput(void) { return current_output; }
  int CurrentError(void) { return current_error; }

  void SetCurrentInput(u_int in)
  {
    DEBUG_ASSERT(in >= 0 && in < NUM_OPEN_STREAMS);
    DEBUG_ASSERT(open_streams[in] != NULL);
    current_input = in;
  }
  void SetCurrentOutput(u_int out)
  {
    DEBUG_ASSERT(out >= 0 && out < NUM_OPEN_STREAMS);
    DEBUG_ASSERT(open_streams[out] != NULL);
    current_output = out;
  }
  void SetCurrentError(u_int error)
  {
    DEBUG_ASSERT(error >= 0 && error < NUM_OPEN_STREAMS);
    DEBUG_ASSERT(open_streams[error] != NULL);
    current_error = error;
  }
  int OpenStream(Stream* strm)
    {
      u_int i;
      for (i = 0; i < NUM_OPEN_STREAMS; i++)
	{
	  if (open_streams[i] == NULL)
	    {
	      break;
	    }
	}
      if (i == NUM_OPEN_STREAMS)
	{
	  return -1;
	}
      open_streams[i] = strm;
      return i;
    }
  void CloseStream(u_int i)
    {
      DEBUG_ASSERT(i >= 0 && i < NUM_OPEN_STREAMS);
      DEBUG_ASSERT(open_streams[i] != NULL);
      open_streams[i] = NULL;
    }
  
  Stream* GetStream(u_int i)
    {
      DEBUG_ASSERT(i >= 0 && i < NUM_OPEN_STREAMS);
      return (open_streams[i]);
    }

  bool set_std_stream(int stdstrm, u_int i)
    {
      if (stdstrm < 0 || stdstrm > 2)
	{
	  return false;
	}
      if (i < 0 || i >=  NUM_OPEN_STREAMS || open_streams[i] == NULL)
	{
	  return false;
	}
      if (open_streams[i]->getDirection() == 
	  open_streams[stdstrm]->getDirection())
	{
	  open_streams[stdstrm] = open_streams[i];
	  open_streams[i] = NULL;
	  return true;
	}
      return false;
    }

  bool reset_std_stream(int stdstrm)
    {
      switch (stdstrm)
	{
	case 0:
	  if (open_streams[0] == save_stdin)
	    {
	      return false;
	    }
	  open_streams[0]->close();
	  open_streams[0] = save_stdin;
	  break;
	case 1:
	  if (open_streams[1] == save_stdout)
	    {
	      return false;
	    }
	  open_streams[1]->close();
	  open_streams[1] = save_stdout;
	  break;
	case 2:
	  if (open_streams[2] == save_stderr)
	    {
	      return false;
	    }
	  open_streams[2]->close();
	  open_streams[2] = save_stderr;
	  break;
	default:
	  DEBUG_ASSERT(false);
	  return false;
	}
      return true;
    }
  
};


class SocketManager
{
private:
  Socket* open_sockets[NUM_OPEN_SOCKETS];
  
public:
  SocketManager(void)
  {
    for (u_int i = 0; i < NUM_OPEN_SOCKETS; i++)
      {
	open_sockets[i] = NULL;
      }
  }
  
  ~SocketManager(void) { }
  
  int OpenSocket(Socket* sock)
    {
      u_int i;
      for (i = 0; i < NUM_OPEN_SOCKETS; i++)
	{
	  if (open_sockets[i] == NULL)
	    {
	      break;
	    }
	}
      if (i == NUM_OPEN_SOCKETS)
	{
	  return -1;
	}
      open_sockets[i] = sock;
      return i;
    }
  void CloseSocket(u_int i)
    {
      DEBUG_ASSERT(i >= 0 && i < NUM_OPEN_SOCKETS);
      DEBUG_ASSERT(open_sockets[i] != NULL);
      open_sockets[i] = NULL;
    }
  
  Socket* GetSocket(u_int i)
    {
      DEBUG_ASSERT(i >= 0 && i < NUM_OPEN_SOCKETS);
      return (open_sockets[i]);
    }

};


inline int qp_fileno(const istream& istrm) { return istrm.rdbuf()->_fileno; }
inline int qp_fileno(const ostream& ostrm) { return ostrm.rdbuf()->_fileno; }

// Returns true if the fd is ready for I/O in the appropriate direction.
extern bool is_ready(const int fd, const IOType type);

#endif	// IO_QP_H

