/***************************************************************************
                          icm_env.h - ICM management 
                             -------------------
    begin                : Sat Dec 14 2002
    copyright            : (C) 2002 by Peter Robinson
    email                : pjr@itee.uq.edu.au
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

// $Id: icm_env.h,v 1.1 2004/05/12 23:58:54 qp Exp $

#ifndef ICM_ENV_H
#define ICM_ENV_H

#include "icm.h"
#include <string>
#define HANDLE_NAME_SIZE 1024

using namespace std;

class ICMEnvironment
{
 private:
  icmConn conn;
  icmHandle handle;
  icmHandle ourHandle;
  char process_symbol[256];
  int comm_fd;
  long seqNo;

 public:
  ICMEnvironment(char*, int, char*);
  ~ICMEnvironment(void);

  int getCommFD(void) { return comm_fd; }
  bool msgAvail(void);
  void getMsg(bool& compressed, string& msg, 
	      string& sender_name, string& replyto_name);
  void sendMsg(bool compressed, string msg, string to, string replyto);
};

#endif

