/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Create new queues: One for recieving, one for sending
 *
 */

#ifndef CINIT_IPC_HEADER
#define CINIT_IPC_HEADER

#define MSGQ_PATHNAME      "/cinit"       /* identifier              */

/***********************************************************************
 * structures
 */

/* messages _from_ the client _to_ the server */
struct msgq_client {
    long mtype;
    pid_t pid;
    struct msg_client msg;
};

/* messages _from_ the server _to_ the client */
struct msgq_server_short {
    long mtype;
    struct asw_sstatus answer;
};

/***********************************************************************
 * Messages
 */

#define MSG_MSGQ_DESTROY      "msgq-destroy"

#endif
