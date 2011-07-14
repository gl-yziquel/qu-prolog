// system_support.cc 
//
// Functions for general system support

//
// ##Copyright##
// 
// Copyright (C) 2000-2011 
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
// $Id: system_support.cc,v 1.3 2006/03/30 22:50:31 qp Exp $

// PORT
#include "system_support.h"
#include <cstdlib>
#include <iostream>
#ifdef WIN32
#include <direct.h>
#endif //WIN32

using namespace std;

void wordexp(string& str)
{
  

#ifdef WIN32
  // expand environment variables
  size_t pos;
  pos = str.find("%");
  while (pos != string::npos)
    {
      size_t end = str.find("%", pos+1);
      if (end != string::npos)
        {
          string env = string(str, pos+1, end-pos-1);
          char* expenv = getenv(env.c_str());
          if (expenv == NULL)
            {
              str.replace(pos, end-pos+1, "");
            }
          else
            {
              str.replace(pos, end-pos+1, expenv);
            }
          pos = end;
        }
      pos = str.find("%", pos+1);
    }
  pos = str.find("/");
  if (pos == 0)
    {
      str.replace(0, 1, "C:\\");
    }
  // replace /   
  pos = str.find("/");
  while (pos != string::npos)
    {
      str.replace(pos, 1, "\\");
      pos = str.find("/");
    }

  if (str == ".")
    {
      char path[256];
      if (_getcwd(path, 255) != NULL)
        str.replace(0,1,path);
    }
  // process ".."
  pos = str.find("..");
  while (pos != string::npos)
    {
      if (str[pos-1] != '\\')
        break;
      size_t slashpos = str.rfind("\\", pos-2);
      if (slashpos == string::npos)
        break;
      str.replace(slashpos, pos+2-slashpos, "");
      pos = str.find("..");
    }

  pos = str.find("\\.\\");
  while (pos != string::npos)
    {
      str.replace(pos, 2, "");
      pos = str.find("\\.\\");
    }

#else //UNIX STUFF HERE
  
  // expand environment variables
  size_t pos;
  pos = str.find("$");
  while (pos != string::npos)
    {
      size_t end = str.find("/", pos);
      if (end == string::npos)
        {
          end = str.size();
        }
      string env = string(str, pos+1, end-pos-1);
      char* expenv = getenv(env.c_str());
      if (expenv == NULL)
        {
	  str.replace(pos, end-pos, "");
        }
      else
        {
	  str.replace(pos, end-pos, expenv);
        }
      pos = str.find("$");
    }
  // expand leading ~ to home dir
  pos = str.find("~/");
  if (pos == 0)
    {
      str.replace(0,1, getenv("HOME"));
    }
  // expand "~"
  if (str == "~")
    {
      str.replace(0,1,getenv("HOME"));
    }
  // replace "." by current dir
  if (str == ".")
    {
      char path[256];
      if (getcwd(path, 255) != NULL)
        str.replace(0,1,path);
    }
  // add full path if path doesn't start with /
  pos = str.find("/");
  if (pos != 0)
    {
      char path[256];
      if (getcwd(path, 255) != NULL)
        {
          str.insert(0, "/");
          str.insert(0, path);
        }
    }
  // remove //
  pos = str.find("//");
  while (pos != string::npos)
    {
      str.replace(pos, pos+1, "/");
      pos = str.find("//");
    }
  // process ".."
  pos = str.find("..");
  while (pos != string::npos)
    {
      if (str[pos-1] != '/')
        break;
      size_t slashpos = str.rfind("/", pos-2);
      if (slashpos == string::npos)
        break;
      str.replace(slashpos, pos+2-slashpos, "");
      pos = str.find("..");
    }
  // replace "/./" with "/"
  pos = str.find("/./");
  while (pos != string::npos)
    {
      str.replace(pos, 2, "");
      pos = str.find("/./");
    }

#endif
}
