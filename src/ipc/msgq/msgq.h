/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    header of message queuing interface
 *
 */

#ifndef __CINIT_IPC_HEADER
#define __CINIT_IPC_HEADER

#include <cinit.h>                         /* structures              */

/***********************************************************************
 * configuration
 */

#define __CINIT_MSGQ_PATHNAME      "/bin/sh"      /* should be on every *nix */
#define __CINIT_MSGQ_TO_SERVER     'i'            /* also for ftok           */
#define __CINIT_MSGQ_TO_CLIENT     'o'            /* also for ftok           */
#define __CINIT_MSGQ_PERMS         0660           /* queue permissions       */

/***********************************************************************
 * global variables: FIXME: rename, we're in client namespace!
 */
int               __cinit_mq_in;    /* input    */
int               __cinit_mq_out;   /* output   */

/***********************************************************************
 * structures
 */

/* messages _from_ the client _to_ the server */
struct cinit_msgq_client {
    long mtype;
    struct cinit_question qsn;
};

/* messages _from_ the server _to_ the client */
struct cinit_msgq_server {
    long mtype;
    struct cinit_answer asr;
};

/***********************************************************************
 * Messages
 */

#define __CINIT_MSG_MSGQ_FTOK         "ftok"
#define __CINIT_MSG_MSGQ_MSGGET       "msgget"
#define __CINIT_MSG_MSGQ_MSGCTL       "msgctl"
#define __CINIT_MSG_MSGQ_MSGSEND      "msgsend"
#define __CINIT_MSG_MSGQ_MSGRCV       "msgrcv"
#define __CINIT_MSG_MSGQ_DESTROY      "msgq-destroy"

#endif
