/* 
 * (c) 2006 Nico Schottelius (nico-linux-cinit //@\\ schottelius.org)
 * part of cinit
 */

#ifndef CINIT_IPC_HEADER
#define CINIT_IPC_HEADER
/* FIXME: add _cinit_ to it, we may be in client namespace now! */

//#include <comm.h>                         /* structures              */
#include <cinit.h>                         /* structures              */

/***********************************************************************
 * configuration
 */

#define MSGQ_PATHNAME      "/bin/sh"      /* should be on every *nix */
#define MSGQ_TO_SERVER     'i'            /* also for ftok           */
#define MSGQ_TO_CLIENT     'o'            /* also for ftok           */
#define MSGQ_PERMS         0660           /* queue permissions       */

/***********************************************************************
 * global variables: FIXME: rename, we're in client namespace!
 */
int               __cinit_mq_in;    /* input    */
int               __cinit_mq_out;   /* output   */

/***********************************************************************
 * structures
 */

/* messages _from_ the client _to_ the server */
struct msgq_client {
    long mtype;
    struct cinit_question qsn;
};

/* messages _from_ the server _to_ the client */
struct msgq_server {
    long mtype;
    struct cinit_answer asr;
};

/***********************************************************************
 * Messages
 */

#define MSG_MSGQ_FTOK         "ftok"
#define MSG_MSGQ_MSGGET       "msgget"
#define MSG_MSGQ_MSGRCV       "msgrcv"
#define MSG_MSGQ_DESTROY      "msgq-destroy"

#endif
