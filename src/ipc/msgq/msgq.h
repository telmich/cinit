/* 
 * (c) 2006 Nico Schottelius (nico-linux-cinit //@\\ schottelius.org)
 * part of cinit
 */

#ifndef CINIT_IPC_HEADER
#define CINIT_IPC_HEADER

int mq_server;                   /* to the server           */
int mq_client;                   /* to the clients          */

/* messages _from_ the client _to_ the server */
struct msg_client {
    long mtype;
    char text[MSG_SIZE];
    pid_t pid;
};

/* messages _from_ the server _to_ the client */
struct msg_server {
    long mtype;
    char text[MSG_SIZE];
};

/***********************************************************************
 * Messages
 */

#define MSG_MSGQ_FTOK         "ftok"
#define MSG_MSGQ_MSGGET       "msgget"

#endif
