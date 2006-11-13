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

#include <limits.h>     /* PATH_MAX                                  */

/***********************************************************************
 * Commands the clients may issue to us
 * maximum number of commands: 2^8 = 256
 */
enum commands {
   CMD_START_SVC=1,     /* the client wants US to start a service    */
   CMD_START_SVC_ONLY,  /* start this service without dependencies   */
   CMD_STOP_SVC,        /* stop svc and all svcs that need it        */
   CMD_STOP_SVC_ONLY,   /* we should stop _only_ this service        */
   CMD_STOP_SVC_WANTS,  /* stop svc, all svcs that need or want it   */
   CMD_CHG_STAT,        /* the client reports a status change        */
   CMD_RESCUE,          /* we should start the rescue mode           */
   CMD_HALT,            /* halt the system                           */
   CMD_REBOOT,          /* reboot the system                         */
   CMD_POWEROFF,        /* poweroff the system                       */
   CMD_WBOOT,           /* shutdown and restart everything           */
   CMD_INFO             /* send information about that service       */
};

/* old
   RT_ERR_COMM,     * communication failed *
   RT_ERR,          * service starting failed *
   RT_UNSPEC,       * some kind of error, unspecified                  *
   RT_SUCCESS,      * successfully started: respawning or once         *
   RT_SVC_FAILED,   * tried earlier, service failed, won't retry       *

*/

/***********************************************************************
 * messages from the client
 * Prefix: qst_ (question)
 */
struct msg_client {
   pid_t pid;                 /* pid of the telling client              */
   char cmd;                  /* which cmd is issued to us              */
   char status;               /* status of the service                  */
   char svc[PATH_MAX];        /* name of the service                    */
   char svc_orig[PATH_MAX];   /* the service, which wants to start us   */
};

/***********************************************************************
 * messages from the server
 * Prefix: asw_ (answer)
 */

/***********************************************************************
 * return short status
 */
struct asw_sstatus {
   long  mtype;
   char  status;
   char  msg[PATH_MAX];
};

#endif
