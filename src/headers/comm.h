/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Communication defines
 */

#ifndef CINIT_COMM_HEADER
#define CINIT_COMM_HEADER

/***********************************************************************
 * Commands the clients may issue to us
 * maximum number of commands: 2^8 = 256
 */
enum commands {
   CMD_START_SVC=1,  /* the client wants US to start a service    */
   CMD_STOP_SVC,     /* the clients wants us to stop the service  */
   CMD_STOP_SVC_REC, /* stop service and all depending services   */
   CMD_CHG_STAT,     /* the client reports a status change        */
   CMD_RESCUE,       /* we should start the rescue mode           */
   CMD_HALT,         /* halt the system                           */
   CMD_REBOOT,       /* reboot the system                         */
   CMD_POWEROFF,     /* poweroff the system                       */
   CMD_WBOOT,        /* shutdown and restart everything           */
   CMD_INFO          /* send information about that service       */
};

/***********************************************************************
 * status of a service and return codes - errors and success
 */
enum svc_status {
   ST_TMPNOW=1,     /* the client is now starting the service     */
   RT_ERR_COMM,     /* communication failed */
   RT_ERR,          /* service starting failed */
   RT_SVC_FAILED,   /* tried earlier, service failed, won't retry */
   RT_UNSPEC,       /* some kind of error, unspecified */
   RT_SUCCESS,      /* successfully started: respawning or once */
   RT_NOTEXIST,     /* service does not exist */

   ST_NEED_FAIL,    /* failed to start a need for this service */
   ST_FAIL,         /* failed to start service */
   ST_OFF,          /* service is off */

   ST_TMP,          /* currently working on it */
   ST_ONCE,         /* executed once */
   ST_RESPAWN       /* running and respawning */
};

/***********************************************************************
 * messages from the client
 */
struct msg_client {
   pid_t pid;           /* pid of the telling client        */
   char cmd;            /* which cmd is issued to us        */
   char status;         /* status of the service            */
   char cmdstatus       /* both in one byte?                */
   char name[PATH_MAX]; /* name of the service              */
};

/***********************************************************************
 * messages from the server
 */
struct msg_server {


};

#endif
