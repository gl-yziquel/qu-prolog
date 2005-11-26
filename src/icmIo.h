/***********************************************************************
(c) 1998-1999 F.G. McCabe, Imperial College and Fujitsu Labs

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
/*
 * header file for ICM I/O library
 * This duplicates some of the standard UNIX I/O but then we get complete control
 */
#ifndef _ICM_IO_H_
#define _ICM_IO_H_

#ifdef __cplusplus
extern "C" {
#endif 

typedef struct _file_rec_ *filePo;	/* Our file pointer */
typedef enum {turnOffBlocking, turnOnBlocking, enableAsynch,disableAsynch
             }icmIoConfigOpt;
typedef enum {ioFile, ioChar, ioBlock, ioDir, ioPipe, ioString, ioLog } ioType;

#include "icm.h"
#include "icmLocal.h"			/* Localization header */

void initICMIo(void);			/* Initialise the IO table */
void closeICMIo(void);		/* Close down all io */

long fileNo(filePo f);
filePo filePtr(long n);
int icmFileData(filePo f);
void *icmFileClient(filePo f);
void icmSetFileClient(filePo f,void *c);
char *icmFileName(filePo f);
ioType icmFileType(filePo f);	/* Indicates the type of file */
long icmFilePos(filePo f);
long icmFileOutPos(filePo f);
long icmFileLineNo(filePo f);

int fileData(filePo f);
void *fileClient(filePo f);
void setFileClient(filePo f,void *c);
char *fileName(filePo f);
ioType fileType(filePo f);	/* Indicates the type of file */
long filePos(filePo f);
long fileOutPos(filePo f);
long fileLineNo(filePo f);

icmStatus icmIsOpenFile(filePo f);	/* True if file is open */
icmStatus icmIsReadingFile(filePo f); /* True if a read-enabled file */
icmStatus icmIsWritingFile(filePo f); /* True if a write-enabled file */
icmStatus icmIsInReady(filePo fe);
icmStatus icmIsOutReady(filePo fe);
icmStatus icmIsFileOpen(filePo f);	/* True if the file is open */
filePo icmCloneIo(filePo f,icmTruth mode);	/* clone a file descriptor */

icmStatus openFile(filePo f);	/* True if file is open */
icmStatus readingFile(filePo f); /* True if a read-enabled file */
icmStatus writingFile(filePo f); /* True if a write-enabled file */
icmStatus inReady(filePo fe);
icmStatus outReady(filePo fe);
icmStatus fileOpen(filePo f);	/* True if the file is open */

void icmFlushOutChannels(void);
icmStatus icmConfigureIo(filePo io,icmIoConfigOpt mode);

icmStatus configureIo(filePo io,icmIoConfigOpt mode);
void flushOutChannels(void);

int filePrintDepth(filePo f);	/* Current print depth */
int setFilePrintDepth(filePo f,int depth);/* Current print depth */

int icmInCh(filePo f);		/* read character from a file */
icmStatus icmInChar(filePo f,char *chP); /* Read a char and return result */
icmStatus icmUnGetCh(filePo f,int ch); /* put a single character back */
icmStatus icmIsCharsWaiting(filePo f); /* true if data available */
icmStatus icmSkipBlanks(filePo f);
icmStatus icmInBlock(filePo in,char *where,long count); /* Read a block */
icmStatus icmInBlck(filePo f,char *buffer,long len,long *ret);
icmStatus icmInLine(filePo f,char *buffer,long len,char *term);
icmStatus icmIsFileAtEof(filePo f);		/* True if at end of file */

icmStatus icmOutCh(filePo cl,int ch);	/* Write a character to output */
icmStatus icmOutChar(filePo f,int ch); /* Non-blocking version */
icmStatus icmUnOutCh(filePo f,long i); /* `unwrite' if possible */
icmStatus icmOutStr(filePo cl,char *str); /* write a C string to a file */
icmStatus icmOutString(filePo f,char *str,int len,int width,int precision,
			      char pad,icmTruth leftPad,char *prefix);
icmStatus icmOutInt(filePo f,llong i);	/* Write an integer to a file */
icmStatus icmOutInteger(filePo f,llong i,int base,int width,int precision,
			char pad,icmTruth left,char *prefix,icmTruth sign);
icmStatus icmOutFloat(filePo out,double x);	/* Write a floating point value */
icmStatus icmOutDouble(filePo out,double x,char mode,int width,int precision,
		    char pad,icmTruth left,char *prefix,icmTruth sign);
icmStatus icmOutBlock(filePo f,char *data,long len);
icmStatus icmOutBlck(filePo f,char *data,long len,long *actual);
icmStatus icmOutMsg(filePo f,char *fmt,...);
icmStatus icmFlushFile(filePo f);		/* Flush a file */


int inCh(filePo f);			/* read character from a file */
icmStatus inChar(filePo f,char *chP); /* Read a char and return result */
int unGetCh(filePo f,int ch);		/* put a single character back */
icmStatus charsWaiting(filePo f);		/* true if data available */
icmStatus skipBlanks(filePo f);
icmStatus inBlock(filePo in,char *where,long count); /* Read a block */
icmStatus inBlck(filePo f,char *buffer,long len,long *ret);
icmStatus inLine(filePo f,char *buffer,long len,char *term);
icmStatus fileAtEof(filePo f);		/* True if at end of file */

icmStatus outCh(filePo cl,int ch);	/* Write a character to output */
icmStatus outChar(filePo f,int ch); /* Non-blocking version */
icmStatus unOutCh(filePo f,long i); /* `unwrite' if possible */
icmStatus outStr(filePo cl,char *str); 	/* write a C string to a file */
icmStatus outString(filePo f,char *str,int len,int width,int precision,
			      char pad,icmTruth leftPad,char *prefix);
icmStatus outInt(filePo f,llong i);	/* Write an integer to a file */
icmStatus outInteger(filePo f,llong i,int base,int width,int precision,
		     char pad,icmTruth left,char *prefix,icmTruth sign);
icmStatus outFloat(filePo out,double x);	/* Write a floating point value */
icmStatus outDouble(filePo out,double x,char mode,int width,int precision,
		    char pad,icmTruth left,char *prefix,icmTruth sign);
icmStatus outBlock(filePo f,char *data,long len);
icmStatus outBlck(filePo f,char *data,long len,long *actual);
icmStatus outMsg(filePo f,char *fmt,...);
icmStatus flushFile(filePo f);		/* Flush a file */

icmStatus int2Str(llong i,char *buff,long len);

icmStatus icmInitLogfile(char *name);
void icmLogMsg(char *fmt,...);
void logMsg(filePo out,char *fmt,...);

#ifndef EOF
#define EOF (-1)
#endif

#ifdef __cplusplus
}; /* end of extern "C" */
#endif

#endif
