/***********************************************************************
(c) 1994-1999 F.G. McCabe, Imperial College and Fujitsu Labs

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Library General Public
License as published by the Free Software Foundation; either
version 2 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
Library General Public License for more details.

You should have received a copy of the GNU Library General Public
License along with this library; if not, write to the
Free Software Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA  02111-1307, USA.

Contact: fgm@fla.fujitsu.com
***********************************************************************/

#ifndef _ICMLOCAL_H_
#define _ICMLOCAL_H_

#ifdef __cplusplus
extern "C" {
#endif 

/* Localization for specific operating systems */

#ifdef _WIN32				/* Windows95 version */
#define ACCESS_MODE _A_NORMAL
#define DIR_SEP "\\"			/* directory separator in file names */
#endif

/* define escape sequences for bold highlighting */
#ifdef __QNX__
#define BOLD_ESC_ON "\033<"
#define BOLD_ESC_OFF "\033>"
#endif

/* Code warrior specific definitions */
#ifdef __MWERKS__
#define APRILDIR ""		/* This should be changed */
#define DIR_SEP ":"		/* directory separator in file names */
#define ACCESS_MODE 0		/* dummy for Macintosh */
#include <winsock2.h>		/* Access winsock library */
#define NEW_LINE '\r'		/* Mac has a different idea of new line */

int access(const char *filename,int mode); /* We must provide this function */
#endif

/* Defaults */
#ifndef BOLD_ESC_ON
#define BOLD_ESC_ON "\033[31m"
#define BOLD_ESC_OFF "\033[30m"
#endif

#ifndef ACCESS_MODE
#define ACCESS_MODE F_OK|R_OK
#endif

#ifndef DIR_SEP
#define DIR_SEP "/"
#endif

#ifndef NEW_LINE
#define NEW_LINE '\n'
#endif

#ifdef __cplusplus
}; /* end of extern "C" */
#endif

#endif
