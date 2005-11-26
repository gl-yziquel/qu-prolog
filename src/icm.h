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

#ifndef _ICM_H_
#define _ICM_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <sys/types.h>
#ifdef WIN32
#include <io.h>
#include <time.h>
#define _WINSOCKAPI_
#include <windows.h>
typedef unsigned long u_long;
#else
#include <netinet/in.h>
#include <sys/time.h>
#endif

#include <pthread.h> /* We are supposed to be thread-safe */

/* Our version of logical */
typedef enum {icmNo = 0, icmYes = 1} icmTruth;

/* Our integers are bigger and better */
typedef long long llong;	/* 64 bit number */

/* Status return type ... most API functions return one of these */
typedef enum {icmOk, icmFailed, icmEndFile, icmError} icmStatus;

/* Opaque handle pointer type */
typedef struct _icmHandle_ *icmHandle;

/* Opaque connection pointer type */
typedef struct _icmConnection_  *icmConn;

/* Opaque message structure pointer type */
typedef struct _icmMessage_ *icmMsg;

/* Unicode character types */
#ifdef WIN32
typedef unsigned long uniChar;  /* should be 32 bits */
#else
typedef u_long uniChar; /* should be 32 bits */
#endif

/* General message contents structure */
typedef struct {
  long size;			/* length - in bytes - of data block */
  char *data;			/* pointer to the data block */
} icmDataRec, *icmDataPo;

typedef struct {
  char *name;
  icmDataPo val;
}  icmOpaqueRec, *icmOpaquePo;


/* options enumerated code */
typedef enum {icmLeaseTime, icmReplyto, icmReceiptRequest, icmAuditTrail } icmOpt;

/* option structure */
typedef struct _icm_msg_option_ *icmOption;

#include "icmIo.h"		/* Access the I/O headers */

/* Idle procedure type */
typedef icmStatus (*icmIdleProc)(icmConn conn,void *client);

/* Callback function type */
typedef icmStatus (*icmMsgProc)(icmConn conn,
				icmHandle recip,icmHandle sender,
				icmOption opt,
				icmMsg msg, void *client);

/* termination hook ... called when a handle is deleted */
typedef icmStatus (*icmTerminProc)(icmHandle h);


/* Handle management functions */
icmHandle icmMakeHandle(char *decoration,char *name,char *home,int count,char **location);
icmHandle icmCommServerHandle(char *host);
icmHandle icmDummyHandle();
icmStatus icmReleaseHandle(icmHandle handle);
icmHandle icmParseHandle(char *buffer);
icmStatus icmKeepHandle(icmHandle h);

/* Analyse a handle into its components */
icmStatus icmAnalyseHandle(icmHandle handle,
			   char **decor,char **name,
			   char **host,char ***locations, int *count);
icmStatus icmSameAgentHandle(icmHandle h1,icmHandle h2);
icmStatus icmSameHandle(icmHandle h1,icmHandle h2);

icmStatus icmHandleName(icmHandle handle,char *buffer,int buffsize);
icmStatus icmMonitorHandle(icmConn conn,icmHandle handle,icmMsgProc proc,void *cl);
icmStatus icmUnmonitorHandle(icmConn conn,icmHandle handle);
icmStatus icmMonitorAgent(icmConn conn,icmHandle client,icmHandle agent);
icmStatus icmUnMonitorAgent(icmConn conn,icmHandle ourH,icmHandle agent);

/* Manage communications with the commserver */
icmStatus icmInitComms(int port,char *host,icmConn *conn);
int icmCommSocket(icmConn con);
icmHandle icmCommserver(icmConn conn);
icmStatus icmCloseComms(icmConn conn);
icmStatus icmDisconnect(icmConn conn);
icmStatus icmReconnect(icmConn conn);
icmStatus icmDetachComms(icmConn conn);
icmStatus icmReattachComms(icmConn conn);

/* Agent registration and de-registration */
icmStatus icmRegisterAgent(icmConn conn,icmHandle agent,icmOption opts,
			   icmHandle *real);
icmStatus icmDeregisterAgent(icmConn conn,icmHandle handle);
icmStatus icmDetachAgent(icmConn conn,icmHandle agent,icmOption opts);
icmStatus icmAttachAgent(icmConn conn,icmHandle agent, icmOption opts);

/* Message handling and eventloop managment */
icmStatus icmEventLoop(icmConn conn,icmMsgProc proc,void *client);
icmStatus icmSetIdleProc(icmConn conn,icmIdleProc proc,void *client);
void icmTerminateEventLoop(icmConn conn);

icmStatus icmSendMsg(icmConn conn,icmHandle recip,icmHandle sender,icmOption opts,
		     icmMsg msg);
icmStatus icmFmtSendMsg(icmConn conn,icmHandle recip,icmHandle sender,
			icmOption opts,char *fmt,...);
icmStatus icmGetMsg(icmConn conn,icmHandle *recip,icmHandle *sndr,
		    icmOption *opts,icmMsg *m,long *seqNo);
icmStatus icmReplaceMsg(icmConn conn,icmHandle recip,icmHandle sndr,
			icmOption opts,icmMsg m,
		    long seqNo);
icmStatus icmWaitMsg(icmConn conn,icmHandle *recip,icmHandle *sndr,
		     icmOption *opt,char *fmt,...);
icmStatus icmMsgAvail(icmConn conn,long from);
icmStatus icmReleaseMsg(icmMsg msg);
icmStatus icmCmpMsg(icmMsg m1,icmMsg m2);
icmMsg icmDupMsg(icmMsg m);

icmMsg icmFormatMsg(icmStatus *ret,char *fmt,...);
icmStatus icmScanMsg(icmMsg msg, char *fmt, ...);
icmStatus icmReadMsg(filePo in,icmMsg msg);
icmStatus icmXScanMsg(icmMsg msg,long start,long *exit,char *fmt, ...);

/* Message rerouting and aliasing */
icmStatus icmRequestAlias(icmConn conn, icmHandle h1,icmHandle h2);
icmStatus icmClearAlias(icmConn conn,icmHandle h1,icmHandle h2);
icmStatus icmLookupAlias(icmConn conn,icmHandle handle,icmHandle *alias);
icmStatus icmPingAgent(icmConn conn,icmHandle us,icmHandle agent,icmHandle *real);

/* option processing */
icmOption icmNewOpt(icmOption prev,icmOpt o,...);
icmStatus icmReleaseOptions(icmOption opts);
icmStatus icmIsOption(icmOption opts,icmOpt o,...);

/* Agent status */
icmStatus icmListAgents(icmConn conn,icmHandle agent,icmHandle *agents,long *max);

/* Low-level message parsing */
typedef enum {icmInt=0x10, icmFlt=0x20, icmNegFlt=0x30, icmSym=0x40, icmHdl=0x50,
	      icmData=0x60, icmCode=0x70, icmNil=0x80, icmList=0x81, 
              icmApply=0x82, icmTuple=0x90,icmTag=0xa0, 
              icmRef=0xb0, icmShort=0xc0,
              icmSigned=0xd0, icmOpaque=0xe0} icmElTag;


icmStatus icmMsgElType(icmMsg msg, long index, icmElTag *type);
icmStatus icmMsgElSize(icmMsg msg,long index,long *size);
icmStatus icmExpectInt(icmMsg msg, long x, long *newx, llong *result);
icmStatus icmExpectFlt(icmMsg msg, long x, long *newx, double *result);
icmStatus icmExpectSym(icmMsg msg, long x, long *newx, char *result,long len);
icmStatus icmExpectHandle(icmMsg msg,long index,long *newx,icmHandle *handle);
icmStatus icmExpectData(icmMsg msg,long index,long *newx,void *buffer,long *len,long max);
icmStatus icmExpectCode(icmMsg msg,long index,long *newx,void *buffer,long *len,long max);
icmStatus icmExpectNil(icmMsg msg, long x, long *newx);
icmStatus icmExpectList(icmMsg msg, long x, long *newx);
icmStatus icmExpectApply(icmMsg msg, long x, long *newx);
icmStatus icmExpectTuple(icmMsg msg, long x, long *newx,long *arity);
icmStatus icmExpectSigned(icmMsg msg,long x,long *newx,char *sig,long *max);
icmStatus icmExpectTag(icmMsg msg, long x, long *newx,long *tag);
icmStatus icmExpectRef(icmMsg msg, long x, long *newx,long *tag);
icmStatus icmExpectShort(icmMsg msg,long index,long *newx,long *tag);
icmStatus icmExpectAny(icmMsg msg,long x,long *nx,icmMsg *m);
icmStatus icmExpectOpaque(icmMsg msg,long index,long *newx);
icmStatus icmSkipElement(icmMsg msg, long x, long *newx);

/* low-level message formatting */
icmStatus icmNewMsg(icmMsg *msg);
icmStatus icmPlaceInt(icmMsg msg,llong i);
icmStatus icmPlaceFlt(icmMsg msg,double f);
icmStatus icmPlaceSym(icmMsg msg,char *sym);
icmStatus icmPlaceHandle(icmMsg msg,icmHandle handle);
icmStatus icmPlaceData(icmMsg msg,void *data, long size);
icmStatus icmPlaceCode(icmMsg msg,void *code, long size);
icmStatus icmPlaceNil(icmMsg msg);
icmStatus icmPlaceList(icmMsg msg);
icmStatus icmPlaceApply(icmMsg msg);
icmStatus icmPlaceTuple(icmMsg msg,long arity);
icmStatus icmPlaceSigned(icmMsg msg,char *sig,long sigLen);
icmStatus icmPlaceOpaque(icmMsg msg);
icmStatus icmPlaceTag(icmMsg msg,long tag);
icmStatus icmPlaceRef(icmMsg msg,long tag);
icmStatus icmPlaceShort(icmMsg msg,long tag);
icmStatus icmPlaceMsg(icmMsg msg,icmMsg sub);
icmStatus icmCopyMsg(icmMsg msg,icmMsg from,long x,long *nx);

icmStatus icmCmpMsg(icmMsg msg1,icmMsg msg2);


/* Host name management and interface */

void icmIPToStr(const struct in_addr *ip, char *addr,long len);
char *icmGetHostname(char *name);
struct in_addr *icmGetHostIP(char *name);
char *icmGetNthHostIP(char *name,long i,char *buffer,long len);
char *icmMachineName(void);
char *icmMachineIP(void);
icmStatus icmIsIPofHost(char *name,u_long ip);


// PORT
//#include "icmHash.h"   /* Hash table interface */

/* Data structure pool management */
typedef struct _poolbase_ *icmPoolBase;


icmPoolBase icmInitPool(size_t elsize, int initial);
icmTruth icmEmptyPool(icmPoolBase base);

void* icmAllocPool(icmPoolBase base); /* allocate an element from the pool */
void icmFreePool(icmPoolBase base, void *el); /* free an element back to the pool */
void icmVerifyPool(icmPoolBase base);

/*
 * mutex and thread management wrappers 
 */

void icmCreateMutex(pthread_mutex_t *mutex);
void icmDestroyMutex(pthread_mutex_t *mutex);
void icmLockMutex(pthread_mutex_t *mutex);
void icmUnlockMutex(pthread_mutex_t *mutex);
void icmWaitCond(pthread_cond_t *cond,pthread_mutex_t *mutex);
void icmSignalCond(pthread_cond_t *cond);
void icmBroadcastCond(pthread_cond_t *cond);

/*
 * Reader/Writer locks
 */

typedef struct _rw_lock_ *icmLockPo;

icmLockPo icmNewLock(void);
void icmReleaseLock(icmLockPo lock);
void icmReadLock(icmLockPo lock);
void icmReadUnLock(icmLockPo lock);
void icmWriteLock(icmLockPo lock);
void icmWriteUnLock(icmLockPo lock);

/* Miscelleneous string functions */

char *icmDataData(icmDataPo str);
long icmDataLength(icmDataPo str);
char *icmCstring(icmDataPo str,char *buff,long len);

char *icmDupStr(char *n);
void icmFreeStr(char *n);
char *icmStrNCpy(char *dest,char *src,long count);
char *icmStrNCat(char *dest,register char *s,long count);
char *icmLowerStr(char *buffer,const char *orig,long count);

char *icmStrMsg(char *buffer,long len,char *fmt,...);

/*
 * Command line options processing 
 */

typedef icmStatus (*icmOptionCallback)(char opt,char *optarg,void *client);

int icmGetOptions(int argc,char **argv,char *fmt,icmOptionCallback opt,
		  void *client);


/*
 * Some default values 
 */
#ifndef ICM_COMMS_PORT
#define ICM_COMMS_PORT 4549
#endif

#ifdef __cplusplus
}; /* end of extern "C" */
#endif

#endif
