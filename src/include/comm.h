/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit (at) schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Communication defines
 */

#ifndef CINIT_COMM_HEADER
#define CINIT_COMM_HEADER

#include <limits.h>     /* PATH_MAX                                  */
#include <sys/types.h>  /* pid_t                                     */

/***********************************************************************
 * Commands the clients may issue to us
 * maximum number of commands: 2^8 = 256
 */
enum commands {
   CMD_MIN='A',         /* minimum command number                    */
   CMD_SVC_START,       /* the client wants US to start a service    */
   CMD_SVC_START_ONLY,  /* start this service without dependencies   */
   CMD_SVC_START_NEEDS, /* start this service, needs, but no wants   */
   CMD_SVC_STOP,        /* stop svc and all svcs that need it        */
   CMD_SVC_STOP_ONLY,   /* we should stop _only_ this service        */
   CMD_SVC_STOP_WANTS,  /* stop svc, all svcs that need or want it   */
   CMD_CHG_STAT,        /* the client reports a status change        */ /* FIXME: NEEDED? */
   CMD_RESCUE,          /* we should start the rescue mode           */ /* UNIMPLEMENTED  */
   CMD_HALT,            /* halt the system                           */
   CMD_REBOOT,          /* reboot the system                         */
   CMD_POWEROFF,        /* poweroff the system                       */
   CMD_WBOOT,           /* shutdown and restart everything           */ /* UNIMPLEMENTED  */
   CMD_INFO,            /* send information about that service       */ /* UNIMPLEMENTED  */
   CMD_MAX  ,           /* maximum command number                    */
};

/* old
   RT_ERR_COMM,     * communication failed *
   RT_ERR,          * service starting failed *
   RT_UNSPEC,       * some kind of error, unspecified                  *
   RT_SUCCESS,      * successfully started: respawning or once         *
   RT_SVC_FAILED,   * tried earlier, service failed, won't retry       *

*/

/***********************************************************************
 * client issues a command: start_command
 */
struct s_cmd {
   char cmd;
   pid_t pid;
};

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
