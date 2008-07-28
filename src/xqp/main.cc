/***************************************************************************
                          main.cc  -  QT interface to qp
                             -------------------
    begin                : April 2004
    copyright            : (C) 2004 by Peter Robinson
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

// $Id: main.cc,v 1.2 2004/05/25 02:14:30 qp Exp $

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>

#include "xqp.h"

using namespace std;

// Create 2 sockets for unidirectional communication to and from qp
int socket_main_to_qp[2], socket_qp_to_main[2];


int main(int argc, char *argv[])
{

  if (socketpair(AF_LOCAL, SOCK_STREAM, 0, socket_main_to_qp))
    {
      cerr << "Fail to open socket" << endl;
      exit(1);
    }
  if (socketpair(AF_LOCAL, SOCK_STREAM, 0, socket_qp_to_main))
    {
      cerr << "Fail to open socket" << endl;
      exit(1);
    }

  // fork child process that will exec qp
  pid_t PID = fork();
  
  if (PID == 0)
    {
      // In child -
      // close write end of socket_main_to_qp
      close(socket_main_to_qp[1]);
      // close read end of socket_qp_to_main
      close(socket_qp_to_main[0]);
      
      if (dup2(socket_qp_to_main[1], STDOUT_FILENO) == -1)
	{
          cerr << "Fail to dup socket_qp_to_main" << endl;
          exit(1);  
	}
      if (dup2(socket_qp_to_main[1], STDERR_FILENO) == -1)
	{
          cerr << "Fail to dup socket_qp_to_main" << endl;
          exit(1);  
	}
      if (dup2(socket_main_to_qp[0], STDIN_FILENO) == -1)
	{
          cerr << "Fail to dup socket_main_to_qp" << endl;
          exit(1);  
	}

      // exec qp
      char* qp_args[argc+1];
      char* qpstr = new char[strlen("qp")+1];
      strcpy(qpstr, "qp");
      qp_args[0] = qpstr;
      for (int i = 1; i < argc; i++) 
	{
	  qp_args[i] = argv[i];
	}
      qp_args[argc] = NULL;
      execvp("qp", qp_args);
    }
  else
    {
      // In parent - 
      // close read end of socket_main_to_qp
      close(socket_main_to_qp[0]);
      // close write end of socket_qp_to_main
      close(socket_qp_to_main[1]);

      // Set up the GUI

      QApplication a(argc, argv);
      Xqp *xqp = new Xqp(socket_qp_to_main[0],
			 socket_main_to_qp[1], PID);
      xqp->show();  

      int exitval =  a.exec();
      delete xqp;
      return exitval;
    }
}
