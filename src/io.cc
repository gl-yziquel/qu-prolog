// io.cc -
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
// $Id: io.cc,v 1.25 2002/12/22 04:12:29 qp Exp $

#include <sys/time.h>
#include <sys/types.h>
#include <string.h>
// #include <stropts.h>
#include <fcntl.h>

#include "global.h"
#include "io_qp.h"
#include "protos.h"
#include "thread_qp.h"
#include "icm_handle.h"
#include "scheduler.h"
#include "signals.h"
#include "thread_table.h"

extern Scheduler *scheduler;
extern Signals *signals;
extern ThreadTable *thread_table;
extern ThreadOptions *thread_options;
extern ICMMessageChannel * icm_channel;

//-----------------------------------------------
//
// Sockets
//
//-----------------------------------------------
Socket::Socket(const int t, const int p, const int f)
  : FD(f, SOCKET),
    sstatus(SS_INIT),
    smode(SM_INIT),
    stype(t),
    sproto(p),
    istream(-1),
    ostream(-1)
{
  if (t == SOCK_STREAM)
    {
      setConnection();
    }
  else
    {
      setConnectionless();
    }

  //
  // When the socket is closed or the process dies, make sure that we
  // can reuse the address.
  //
  int opt_val = 1;

  SYSTEM_CALL_LESS_ZERO(setsockopt(getFD(), SOL_SOCKET, SO_REUSEADDR,
				   (char *) &opt_val, sizeof(opt_val)));
}

bool
Socket::isConnectAllowed(void) const
{
  bool result = false;

  switch (smode)
    {
    case SM_INIT:
      result = false;
      break;
    case SM_CONNECTION:
    case SM_CONNECTIONLESS:
      result = (sstatus == SS_SOCKET ||	sstatus == SS_BIND);
      break;
    }

  return result;
}

bool
Socket::isSendtoAllowed(void) const
{
  bool result = false;

  switch (smode)
    {
    case SM_INIT:
      result = false;
      break;
    case SM_CONNECTION:
    case SM_CONNECTIONLESS:
      result = (sstatus == SS_SOCKET || sstatus == SS_BIND ||
		sstatus == SS_CONNECTED);
      break;
    }

  return result;
}

bool
Socket::isRecvfromAllowed(void) const
{
  bool result = false;

  switch (smode)
    {
    case SM_INIT:
      result = false;
      break;
    case SM_CONNECTION:
    case SM_CONNECTIONLESS:
      result = (sstatus == SS_SOCKET || sstatus == SS_BIND ||
		sstatus == SS_CONNECTED);
      break;
    }

  return result;
}

bool
Socket::isBroadcast(void) const
{
  int val;
  unsigned int len = sizeof(val);

  if (getsockopt(getFD(),
		 SOL_SOCKET, SO_BROADCAST, (char *)&val, &len))
    {
      return false;
    }

  return val != 0;
}

bool
Socket::openSocket(const int type, const int proto)
{
  stype = type;
  sproto = proto;

  setFD(socket(AF_INET, type, proto));

  setIStream(-1);
  setOStream(-1);

  if (getFD() < 0)
    return false;

  setSocket();
  return true;
}

bool
Socket::closeSocket(void)
{
  if (close(getFD()) < 0)
    return false;
  
  setClose();
  
  return true;
}

void
Socket::setAccepted(Socket *sock, const int new_fd)
{
  sock->setFD(new_fd);
  sock->setConnection();
  sock->setConnected();
}


bool
Socket::isEnded(void) const
{
  return sstatus == SS_CLOSED;
}

//-----------------------------------------------
//
// Streams
//
//-----------------------------------------------

QPStream::QPStream(IOType t):type(t),lineCounter(1)
{ 
  properties = new heapobject[Structure::size(7)]; 
}

void 
QPStream::setProperties(Object* prop)
{
  DEBUG_ASSERT(prop->isStructure());
  // copy the tag
  properties[0] = *(reinterpret_cast<heapobject*>(prop));
  Object* propobject = reinterpret_cast<Object*>(properties);
  DEBUG_ASSERT(propobject->isStructure());
  // copy functor and args
  for (u_int i = 0; i <= OBJECT_CAST(Structure*, propobject)->getArity(); i++)
    {
        OBJECT_CAST(Structure*, propobject)->setArgument(i, OBJECT_CAST(Structure*, prop)->getArgument(i)->variableDereference());
    }
}

void
QPStream::setRSProperties(void)
{
  // !! WARNING !! Do the following a different way
  // This sets up the structure tag and arity directly.
  properties[0] = (7 << 8) | 0x0000000CUL;
  DEBUG_ASSERT(reinterpret_cast<Object*>(properties)->isStructure());
  Structure* propstr = reinterpret_cast<Structure*>(properties);
  propstr->setFunctor(atoms->add("$prop"));
  propstr->setArgument(1, atoms->add("read"));
  propstr->setArgument(2, atoms->add("input"));
  propstr->setArgument(3, atoms->add("string"));
  propstr->setArgument(4, atoms->add("none"));
  propstr->setArgument(5, atoms->add("error"));
  propstr->setArgument(6, atoms->add("false"));
  propstr->setArgument(7, atoms->add("test"));
}


Object* QPStream::getProperties(void)
{
  return (reinterpret_cast<Object*>(properties));
}


///////////////////////////////////////////////////////////
// QPistream
//////////////////////////////////////////////////////////

QPistream::QPistream(const char* file): QPStream(ISTREAM), stream(file) {}

bool QPistream::seekg(streampos pos, ios::seekdir d)
{ 
  return (!stream.seekg(pos, d).fail()); 
}

///////////////////////////////////////////////////////////
// QPistringstream
//////////////////////////////////////////////////////////

QPistringstream::QPistringstream(const string& buff)
  : QPStream(ISTRSTREAM), stream(buff) {}

///////////////////////////////////////////////////////////
// QPifstream
//////////////////////////////////////////////////////////

QPifdstream::QPifdstream(int f):  
  QPStream(IFDSTREAM), stream(""), fd(f), done_get(false) { }

bool QPifdstream::get(char& ch)
{
  if (done_get && eof())
    {
      get_read();
    }
  done_get = true;
  
  return (!stream.get(ch).fail());
}

int QPifdstream::get(void)
{
  if (done_get && eof())
    {
      get_read();
    }
  done_get = true;
  
  return (stream.get());
}

bool
QPifdstream::isReady(void)
{
  // Not at end of buffer so ready to read
  if (done_get && !eof()) return true;

  // otherwise use select to see if there is anything on low-level
  // stream - and if so transfer to buffer.

  if (is_ready(fd, IFDSTREAM))
    {
      get_read();
      return true;
    }
  else
    {
      return false;
    }
}

void
QPifdstream::get_read(void)
{
  DEBUG_ASSERT(fd != NO_FD);
  char buff[BUFFSIZE];
  // read from fd
  int buffsize = read(fd, buff, BUFFSIZE-1);
  buff[buffsize] = '\0';
  //reset strin buffer
  stream.str(buff);
  stream.seekg(0, ios::beg);
  stream.clear();
  done_get = false;
}

///////////////////////////////////////////////////////////
// QPimstream
//////////////////////////////////////////////////////////

QPimstream::QPimstream(icmHandle handle)
  : QPStream(IMSTREAM), 
    stream(""),
    sender_handle(handle), 
    done_get(false) 
{ }

bool
QPimstream::msgReady(void) 
{ 
  return !message_strings.empty(); 
}

void 
QPimstream::pushString(string* st) 
{ 
  message_strings.push_back(st); 
}

bool 
QPimstream::get(char& ch)
{
  if (done_get && eof())
    {
      get_read();
    }
  done_get = true;
  
  return (!stream.get(ch).fail());
}

int 
QPimstream::get(void)
{
  if (done_get && eof())
    {
      get_read();
    }
  done_get = true;
  
  return (stream.get());
}

icmHandle 
QPimstream::getSenderHandle(void)
{ 
  return sender_handle; 
}

bool
QPimstream::isReady(void)
{
#ifdef ICM_DEF
  
  if (done_get && !eof()) return true;

  if ( message_strings.empty())
    {
      return false;
    }
  else
    {
      get_read();
      return true;
    }

#else // ICM_DEF
      return false;
#endif // ICM_DEF
}

void
QPimstream::get_read(void)
{
#ifdef ICM_DEF
  while (message_strings.empty())
    {
      fd_set rfds, wfds;
      FD_ZERO(&rfds);
      FD_ZERO(&wfds);
      int max_fd = 0;
      icm_channel->updateFDSETS(&rfds, &wfds, max_fd);
      select(max_fd + 1, &rfds, &wfds, NULL, NULL);
      icm_channel->ShuffleMessages();
    }
  DEBUG_ASSERT(!message_strings.empty());
  
  string* msg = message_strings.front();
  stream.str(*msg);
  message_strings.pop_front();
  delete msg;

  stream.seekg(0, ios::beg);
  stream.clear();
  done_get = false;

#endif // ICM_DEF
}

///////////////////////////////////////////////////////////
// QPostream
//////////////////////////////////////////////////////////

QPostream::QPostream(const char* file, ios::openmode mode)
  : QPStream(OSTREAM), 
    can_delete(true) 
{
  stream = new ofstream(file, mode);
}
QPostream::QPostream(ostream* strmptr)
  : QPStream(OSTREAM),
    can_delete(false) 
{
  stream = strmptr;
}

///////////////////////////////////////////////////////////
// QPostringstream
//////////////////////////////////////////////////////////

QPostringstream::QPostringstream(): QPStream(OSTRSTREAM) {}

///////////////////////////////////////////////////////////
// QPofstream
//////////////////////////////////////////////////////////

QPofdstream::QPofdstream(int n)
  : QPStream(OFDSTREAM), 
    fd(n), 
    auto_flush(false) 
{}

bool 
QPofdstream::put(char ch)
{
  if (stream.put(ch).fail())
    {
      return false;
    }
  if (auto_flush || (ch == '\n'))
    {
      send();
    }
  return true;
}

void 
QPofdstream::operator<<(const char c)
{
  stream << c;
  if (auto_flush || (c == '\n'))
    {
      send();
    }
}

void 
QPofdstream::operator<<(const char* s)
{
  if (auto_flush)
    {
      stream << s;
      send();
    }
  else
    {
      char* ptr = strrchr(s, '\n');
      if (ptr == NULL)
	{
	  stream << s;
	}
      else if ((ptr - s) == ((int)strlen(s) + 1))
	{
	  stream << s;
	  send();
	}
      else
	{
	  int len = ptr-s+1;
	  char tmpbuff[len+1];
	  strncpy(tmpbuff, s, len);
	  tmpbuff[len] = '\0';
	  stream << tmpbuff;
	  send();
	  stream << (ptr+1);
	}
    }
}

void 
QPofdstream::operator<<(const int n)
{
  stream << n;
  if (auto_flush) send();
}

const string 
QPofdstream::str(void)
{
  return stream.str();
}

void 
QPofdstream::flush(void)
{
  if (!auto_flush && (stream.str().length() != 0)) send();
}

bool 
QPofdstream::set_autoflush(void)
{
  auto_flush = true;
  return true;
}

void
QPofdstream::send(void)
{
  if (fd == NO_FD) return;
  write(fd, stream.str().data(), stream.str().length());
  stream.str("");
}


///////////////////////////////////////////////////////////
// QPomstream
//////////////////////////////////////////////////////////

QPomstream::QPomstream(icmHandle handle, Thread* thread, 
		       ICMEnvironment* icm_env)
  : QPStream(OMSTREAM),
    to_handle(handle), 
    sender_thread(thread), 
    icm_environment(icm_env), 
    auto_flush(false) 
{}

bool 
QPomstream::put(char ch)
{
  if (stream.put(ch).fail())
    {
      return false;
    }
  if (auto_flush || (ch == '\n'))
    {
      send();
    }
  return true;
}

void 
QPomstream::operator<<(const char c)
{
  stream << c;
  if (auto_flush || (c == '\n'))
    {
      send();
    }
}

void 
QPomstream::operator<<(const char* s)
{
  if (auto_flush)
    {
      stream << s;
      send();
    }
  else
    {
      char* ptr = strrchr(s, '\n');
      if (ptr == NULL)
	{
	  stream << s;
	}
      else if ((ptr - s) == ((int)strlen(s) + 1))
	{
	  stream << s;
	  send();
	}
      else
	{
	  int len = ptr-s+1;
	  char tmpbuff[len+1];
	  strncpy(tmpbuff, s, len);
	  tmpbuff[len] = '\0';
	  stream << tmpbuff;
	  send();
	  stream << (ptr+1);
	}
    }
}

void 
QPomstream::operator<<(const int n)
{
  stream << n;
  if (auto_flush) send();
}

const string 
QPomstream::str(void)
{
  return stream.str();
}

void 
QPomstream::flush(void)
{
  if (!auto_flush && (stream.str().length() != 0)) send();
}

bool 
QPomstream::set_autoflush(void)
{
  auto_flush = true;
  return true;
}

void
QPomstream::send(void)
{
#ifdef ICM_DEF
  icmStatus status;
  string str = stream.str();
  int size = str.length();

  icmDataRec data = { size, const_cast<char*>(str.c_str()) };
  icmMsg message = icmFormatMsg(NULL, "%S", &data);

  status = icmSendMsg(icm_environment->Conn(),
		      to_handle,
		      icm_thread_handle(*icm_environment, *sender_thread),
		      NULL,
		      message);
  DEBUG_ASSERT(status == icmOk);
  stream.str("");
#endif // ICM_DEF
}


///////////////////////////////////////////////////////////
// IOManager
//////////////////////////////////////////////////////////

IOManager::IOManager(QPStream *in, QPStream *out, QPStream *error)
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

bool
IOManager::updateStreamMessages(icmHandle sender, icmMsg message)
{
#ifdef ICM_DEF
  for (u_int i = 0; i < NUM_OPEN_STREAMS; i++)
    {
      if (open_streams[i] != NULL 
	  && open_streams[i]->Type() == IMSTREAM
	  && icmSameHandle(sender, 
			   open_streams[i]->getSenderHandle()) == icmOk)
	{
	  // Found stream for from handle - extract message
	  // and push onto stream message list
	  icmDataRec data;
	  icmStatus status = icmScanMsg(message, "%S", &data);
	  if (status == icmOk)
	    {
	      // Nothing.
	    }
	  else if (status == icmFailed)
	    {
	      Fatal(__FUNCTION__, "Format of message doesn't match QP message format");
	    }
	  else if (status == icmError)
	    {
	      Fatal(__FUNCTION__, "icmScanMsg() returned icmError");
	    }	
	  string* new_string = new string(data.data, data.size);
	  open_streams[i]->pushString(new_string);
	  free(data.data);
	  return true;
	}
    }
#endif // ICM_DEF
  return false;
}

int 
IOManager::OpenStream(QPStream* strm)
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

bool 
IOManager::CloseStream(u_int i)
{
  DEBUG_ASSERT(i >= 0 && i < NUM_OPEN_STREAMS);
  DEBUG_ASSERT(open_streams[i] != NULL);
  if (i < 3) return false; // Can't close std streams
  delete open_streams[i];
  open_streams[i] = NULL;
  return true;
}
  
QPStream* 
IOManager::GetStream(u_int i)
{
  DEBUG_ASSERT(i >= 0 && i < NUM_OPEN_STREAMS);
  return (open_streams[i]);
}

bool 
IOManager::set_std_stream(int stdstrm, u_int i)
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
      open_streams[stdstrm]->setFD(stdstrm);
      open_streams[i] = NULL;
      return true;
    }
  return false;
}

bool 
IOManager::reset_std_stream(int stdstrm)
{
  switch (stdstrm)
    {
    case 0:
      if (open_streams[0] == save_stdin)
	{
	  return false;
	}
      delete open_streams[0];
      open_streams[0] = save_stdin;
      break;
    case 1:
      if (open_streams[1] == save_stdout)
	{
	  return false;
	}
      delete open_streams[1];
      open_streams[1] = save_stdout;
      break;
    case 2:
      if (open_streams[2] == save_stderr)
	{
	  return false;
	}
      delete open_streams[2];
      open_streams[2] = save_stderr;
      break;
    default:
      DEBUG_ASSERT(false);
      return false;
    }
  return true;
}





bool
is_ready(const int fd, const IOType type)
{
  fd_set fds;

  FD_ZERO(&fds);
  FD_SET(fd, &fds);

  // Set up the time value to indicate a poll
  timeval tv = { 0, 0 };

  int result = 0;
  switch (type)
    {
    case IFDSTREAM:
      result = select(fd + 1, &fds, (fd_set *) NULL, (fd_set *) NULL, &tv);
      break;
    case OFDSTREAM:
      result = select(fd + 1, (fd_set *) NULL, &fds, (fd_set *) NULL, &tv);
      break;
    case SOCKET:
      result = select(fd + 1, &fds, (fd_set *) NULL, (fd_set *) NULL, &tv);
      break;
    default:
      DEBUG_ASSERT(false);
      result = 0;
      break;
    }

#ifdef DEBUG_IO
  cerr.form("%s result = %ld FD_ISSET(%ld, ...) = %ld\n",
	    __FUNCTION__, result, fd, FD_ISSET(fd, &fds));
#endif
  return result && FD_ISSET(fd, &fds);

}


