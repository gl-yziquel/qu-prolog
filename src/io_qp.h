// io_qp.h - High level I/O management.
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
// $Id: io_qp.h,v 1.20 2005/11/26 23:34:30 qp Exp $

#ifndef	IO_QP_H
#define	IO_QP_H

#ifdef WIN32
        #define _WINSOCKAPI_
        #include <windows.h>
        #include <time.h>
        #include <winsock2.h>
#else
        #include <sys/file.h>
        #include <sys/types.h>
        #include <sys/times.h>
        #include <sys/time.h>
        #include <sys/socket.h>
        #include <unistd.h>
#endif


#include <stdio.h>
#include <sstream>
#include <fstream>
#include <string.h>


#include "config.h"
#include "objects.h"
#include "defs.h"

#ifdef ICM_DEF
#include "icm_environment.h"
#endif

class Thread;

enum AccessMode {
  AM_READ = 0,
  AM_WRITE = 1,
  AM_APPEND = 2
};



// No file descriptor
#define NO_FD -1

// Buffer size for reading from fd
#define BUFFSIZE 1024

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
    { return type == QPSOCKET; }

  virtual bool isEnded(void) const = 0;

  // Ready for action?
  // virtual bool isReady(void) const = 0;

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
  // bool isReady(void);

  // Finished for IO?
  virtual bool isEnded(void) const;
};

//-----------------------------------------------
//
// Streams
//
//-----------------------------------------------

using namespace std;

//
// QPStream - an abstract class to be inherited by different
// kinds of streams. It provides the stream interface methods.
//

class QPStream
{
 private:
  IOType type;                // the stream type
  word32 lineCounter;         // line counter for input streams
  heapobject* properties;     // a stream properties structure
  
 public:
  explicit QPStream(IOType t);
  
  virtual ~QPStream()
    { 
      delete[] properties; 
    }

  IOType Type(void) { return type; }
  
  bool isInput(void) const 
    { return (type == ISTREAM) || (type == ISTRSTREAM) 
	|| (type == IFDSTREAM) || (type == IMSTREAM); }
  bool isOutput(void) const 
    { return (type == OSTREAM) || (type == OSTRSTREAM) 
	|| (type == OFDSTREAM) || (type == OMSTREAM); }
  
  void setProperties(Object* prop);
  // set the properties for a default read string stream.
  void setRSProperties(void);

  Object* getProperties(void);
  
  virtual int getFD(void) const
    {
      abort(); return 0;
    }

  virtual void setFD(int f) {}
  
  virtual void get_read(void) 
    {  assert((type == IFDSTREAM) || (type = IMSTREAM)); }

  void newline(void) { lineCounter++; }
  void unline(void) { lineCounter--; }

  word32 lineNumber(void) const { return lineCounter; }

  virtual bool isReady(void) { return true; }

  virtual bool msgReady(void) { abort(); return true; }

  IODirection getDirection(void) const
    { return (isInput()? INPUT : OUTPUT); }

  virtual void pushString(string*) { abort(); }

  virtual bool seekg(streampos pos, ios::seekdir d = ios::beg)
    {
      assert(isInput());
      abort();
      return true;
    }

  virtual bool eof(void)
    {
      assert(isInput());
      abort();
      return true;
    }

  virtual bool bad(void) = 0;

  virtual bool fail(void) = 0;

  virtual void clear(ios::iostate state_arg = ios::goodbit) = 0;

  virtual bool get(char& ch)
    {
      assert(isInput());
      abort();
      return true;
    }

  virtual int get(void)
    {
      assert(isInput());
      abort();
      return 0;
    }

  virtual bool unget(void)
    {
      assert(isInput());
      abort();
      return true;
    }

  virtual int peek(void)
    {
      assert(isInput());
      abort();
      return 0;
    }

  virtual bool seekp(streampos pos, ios::seekdir d = ios::beg)
    {
      assert(isOutput());
      abort();
      return true;
    }

  virtual bool put(char ch)
    {
      assert(isOutput());
      abort();
      return true;
    }

  virtual const string str(void)
    {
      assert((type == OSTRSTREAM) || (type == OFDSTREAM));
      abort();
      return "";
    }

  virtual void operator<<(const char c)
    {
      assert(isOutput());
      abort();
    }

  virtual void operator<<(const char* s)
    {
      assert(isOutput());
      abort();
    }

  virtual void operator<<(const int n)
    {
      assert(isOutput());
      abort();
    }

  virtual void operator<<(const double n)
    {
      assert(isOutput());
      abort();
    }

  virtual void flush(void)
    {
      assert(isOutput());
      abort();
    }

  virtual bool set_autoflush(void)
    {
      return false;
    }

  virtual int tell(void) = 0;

  virtual bool good(void) = 0;

#ifdef ICM_DEF
  virtual icmHandle getSenderHandle(void)
    {
      abort(); return icmDummyHandle();
    }
#endif

};

// ---------------------------------------
// Streams derived from the QPStream class
// ---------------------------------------

// INPUT STREAMS

//
// QP version of istream
//
class QPistream: public QPStream
{
 private:
  ifstream stream;

 public:
  explicit QPistream(const char* file);

  ~QPistream() {}

  bool seekg(streampos pos, ios::seekdir d = ios::beg);

  bool eof(void)
   { return (stream.peek() == EOF); }

  bool bad(void) 
   { return (stream.bad()); }

  bool fail(void) 
   { return (stream.fail()); }

  void clear(ios::iostate state_arg = ios::goodbit)
    { stream.clear(state_arg); }

  bool get(char& ch)
    { return (!stream.get(ch).fail()); }
  
  int get(void)
    { return stream.get(); }

  bool unget(void)
    { return (!stream.unget().fail()); }

  int peek(void)
    { return (stream.peek()); }

  int tell(void)
    { return stream.tellg(); }

  bool good(void)
    { return stream.good(); }

};


//
// QP version of istringstream
//
class QPistringstream: public QPStream
{
 private:
  istringstream stream;

 public:
  explicit QPistringstream(const string& buff);

  ~QPistringstream() {}

  bool seekg(streampos pos, ios::seekdir d = ios::beg)
    { return (!stream.seekg(pos, d).fail()); }

  bool eof(void)
   { return (stream.peek() == EOF); }

  bool bad(void) 
   { return (stream.bad()); }

  bool fail(void) 
   { return (stream.fail()); }

  void clear(ios::iostate state_arg = ios::goodbit)
    { stream.clear(state_arg); }

  bool get(char& ch)
    { return (!stream.get(ch).fail()); }
  
  int get(void)
    { return stream.get(); }

  bool unget(void)
    { return (!stream.unget().fail()); }

  int peek(void)
    { return (stream.peek()); }

  int tell(void)
    { return stream.tellg(); }

  bool good(void)
    { return stream.good(); }


};

//
// QP version of streams with file descriptors - an istringstream is
// used as a buffer - select is used to determine if stream is
// ready and read is used to "load up" the istringstream
//
class QPifdstream: public QPStream
{
 private:
  istringstream stream;
  int fd;
  bool done_get;

 public:
  explicit QPifdstream(int f);

  ~QPifdstream() {}

  int getFD(void) const 
    { return fd; } 

  bool isReady(void);

  void get_read(void);

  bool seekg(streampos pos, ios::seekdir d = ios::beg)
    { return (!stream.seekg(pos, d).fail()); }

  bool eof(void)
   { return (stream.peek() == EOF); }

  bool bad(void) 
   { return (stream.bad()); }

  bool fail(void) 
   { return (stream.fail()); }

  void clear(ios::iostate state_arg = ios::goodbit)
    { stream.clear(state_arg); }

  bool get(char& ch);

  int get(void);

  bool unget(void)
    { return (!stream.unget().fail()); }

  int peek(void)
    { return (stream.peek()); }

  int tell(void)
    { return stream.tellg(); }

  bool good(void)
    { return stream.good(); }

};

#ifdef ICM_DEF
//
// QP version of streams using ICM messages - an istringstream is
// used as a buffer.
//
class QPimstream: public QPStream
{
 private:
  istringstream stream;
  // the icm handle for incoming messages.
  icmHandle sender_handle;
  int iom_fd;

  list<string *> message_strings;

  bool done_get;

 public:
  explicit QPimstream(icmHandle handle); 

  ~QPimstream() { }
  
  int getFD(void) const { return iom_fd; }

  void setFD(int fd) { iom_fd = fd; }

  bool msgReady(void);

  bool isReady(void);
  
  void get_read(void);
  
  void pushString(string* st);

  bool seekg(streampos pos, ios::seekdir d = ios::beg)
  { return (!stream.seekg(pos, d).fail()); }
  
  bool eof(void)
  { return (stream.peek() == EOF); }

  bool bad(void) 
   { return (stream.bad()); }

  bool fail(void) 
   { return (stream.fail()); }

  void clear(ios::iostate state_arg = ios::goodbit)
    { stream.clear(state_arg); }

  bool get(char& ch);

  int get(void);

  bool unget(void)
    { return (!stream.unget().fail()); }

  int peek(void)
    { return (stream.peek()); }

  int tell(void)
    { return stream.tellg(); }

  bool good(void)
    { return stream.good(); }

  icmHandle getSenderHandle(void);

};
#endif


// OUTPUT STREAMS

//
// QP version of ostream
//
class QPostream: public QPStream
{
 private:
  ostream* stream;
  bool can_delete;


 public:
  QPostream(const char* file, ios::openmode mode);
  QPostream(ostream* strmptr);

  ~QPostream() { if (can_delete) delete stream;}

  bool bad(void) 
   { return (stream->bad()); }

  bool fail(void)
    { return (stream->fail()); }

  void clear(ios::iostate state_arg = ios::goodbit)
    { stream->clear(state_arg); }

  int tell(void)
    { return stream->tellp(); }

  bool good(void)
    { return stream->good(); }

  bool seekp(streampos pos, ios::seekdir d = ios::beg)
    {
      return stream->seekp(pos, d);
    }

  bool put(char ch)
    {
      return !stream->put(ch).fail();
    }

  void operator<<(const char c)
    {
      (*stream) << c;
    }

  void operator<<(const char* s)
    {
      (*stream) << s;
    }

  void operator<<(const int n)
    {
      (*stream) << n;
    }

  void operator<<(const double n)
    {
      (*stream) << n;
    }

  void flush(void)
    {
      stream->flush();
    }
};


//
// QP version of ostringstream
//
class QPostringstream: public QPStream
{
 private:
  ostringstream stream;


 public:
  QPostringstream();

  ~QPostringstream() {}

  bool bad(void) 
   { return (stream.bad()); }

  bool fail(void)
    { return (stream.fail()); }

  void clear(ios::iostate state_arg = ios::goodbit)
    { stream.clear(state_arg); }

  int tell(void)
    { return stream.tellp(); }

  bool good(void)
    { return stream.good(); }

  bool seekp(streampos pos, ios::seekdir d = ios::beg)
    {
      return stream.seekp(pos, d);
    }

  bool put(char ch)
    {
      return !stream.put(ch).fail();
    }

  void operator<<(const char c)
    {
      stream << c;
    }

  void operator<<(const char* s)
    {
      stream << s;
    }

  void operator<<(const int n)
    {
      stream << n;
    }

  void operator<<(const double n)
    {
      stream << n;
    }

 const string str(void)
    {
      return stream.str();
    }

  void flush(void)
    {
      stream.flush();
    }
};

//
// QP version of streams with file descriptors - an ostringstream is
// used as a buffer.
//
class QPofdstream: public QPStream
{
 private:
  ostringstream stream;
  int fd;
  bool auto_flush;
  void send(void);


 public:
  explicit QPofdstream(int n);

  ~QPofdstream() {}

  bool bad(void) 
   { return (stream.bad()); }

  bool fail(void)
    { return (stream.fail()); }

  void clear(ios::iostate state_arg = ios::goodbit)
    { stream.clear(state_arg); }

  int tell(void)
    { return stream.tellp(); }

  bool good(void)
    { return stream.good(); }

  bool seekp(streampos pos, ios::seekdir d = ios::beg)
    {
      return stream.seekp(pos, d);
    }

  bool put(char ch);

  void operator<<(const char c);

  void operator<<(const char* s);

  void operator<<(const int n);

  void operator<<(const double n);

  const string str(void);

  void flush(void);

  bool set_autoflush(void);

};

#ifdef ICM_DEF
//
// QP version of streams using ICM messages - an ostringstream is
// used as a buffer.
//
class QPomstream: public QPStream
{
 private:
  ostringstream stream;
  icmHandle to_handle;
  Thread* sender_thread;
  ICMEnvironment* icm_environment;

  bool auto_flush;
  void send(void);


 public:
  QPomstream(icmHandle handle, Thread* thread, 
	     ICMEnvironment* icm_env); 

  ~QPomstream() {}

  bool bad(void) 
   { return (stream.bad()); }

  bool fail(void)
    { return (stream.fail()); }

  void clear(ios::iostate state_arg = ios::goodbit)
    { stream.clear(state_arg); }

  int tell(void)
    { return stream.tellp(); }

  bool good(void)
    { return stream.good(); }

  bool seekp(streampos pos, ios::seekdir d = ios::beg)
    {
      return stream.seekp(pos, d);
    }

  bool put(char ch);

  void operator<<(const char c);

  void operator<<(const char* s);

  void operator<<(const int n);

  void operator<<(const double n);

  const string str(void);

  void flush(void);

  bool set_autoflush(void);

};
#endif


//
// Maintains a record of the current streams.
// This role might be expanded in future.
//
class IOManager
{
private:
  QPStream* open_streams[NUM_OPEN_STREAMS];
  int current_input;
  int current_output;
  int current_error;
  QPStream* save_stdin;
  QPStream* save_stdout;
  QPStream* save_stderr;
  
public:
  IOManager(QPStream *in, QPStream *out, QPStream *error);
  
  ~IOManager(void) { }
  
  QPStream *StdIn(void) { return open_streams[0]; }
  QPStream *StdOut(void) { return open_streams[1]; }
  QPStream *StdErr(void) { return open_streams[2]; }

  int CurrentInput(void) { return current_input; }
  int CurrentOutput(void) { return current_output; }
  int CurrentError(void) { return current_error; }

  void SetCurrentInput(u_int in)
  {
    assert(in >= 0 && in < NUM_OPEN_STREAMS);
    assert(open_streams[in] != NULL);
    current_input = in;
  }
  void SetCurrentOutput(u_int out)
  {
    assert(out >= 0 && out < NUM_OPEN_STREAMS);
    assert(open_streams[out] != NULL);
    current_output = out;
  }
  void SetCurrentError(u_int error)
  {
    assert(error >= 0 && error < NUM_OPEN_STREAMS);
    assert(open_streams[error] != NULL);
    current_error = error;
  }
  int OpenStream(QPStream* strm);

  bool CloseStream(u_int i);
  
  QPStream* GetStream(u_int i);

  bool set_std_stream(int stdstrm, u_int i);

  bool reset_std_stream(int stdstrm);

#ifdef ICM_DEF
  bool updateStreamMessages(icmHandle, icmMsg);
#endif
  
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
      assert(i >= 0 && i < NUM_OPEN_SOCKETS);
      assert(open_sockets[i] != NULL);
      open_sockets[i] = NULL;
    }
  
  Socket* GetSocket(u_int i)
    {
      assert(i >= 0 && i < NUM_OPEN_SOCKETS);
      return (open_sockets[i]);
    }

};


// Returns true if the fd is ready for I/O in the appropriate direction.
extern bool is_ready(const int fd, const IOType type);

#endif	// IO_QP_H

