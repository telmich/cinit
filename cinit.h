/* 
 * cinit
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * header of cinit
 */

/* includes */
#include <sys/types.h>  /* pid_t */
#include "config.h"     /* paths, socket options, etc. */

/* paths */
#define C_ONARG   C_ON  C_PARAMS
#define C_OFFARG  C_OFF C_PARAMS
#define C_ONENV   C_ON  C_ENV
#define C_OFFENV  C_OFF C_ENV

#define SLASH     "/"
#define MSG_DP    ": "

#define CINIT_INIT CINIT_DIR SLASH C_INIT
#define CINIT_TMNT CINIT_DIR SLASH C_TMP
#define CINIT_SOCK CINIT_TMNT SLASH C_SOCK
#define CINIT_BIN  PREFIX SLASH "sbin" SLASH "cinit"

/* commands (maximum: 2^8 = 256, because we use a single byte)*/
enum commands {   CMD_START_SVC=1, 
                  CMD_STOP_SVC,
                  CMD_CHG_STATUS,
                  CMD_RESCUE,
                  CMD_HALT,
                  CMD_REBOOT,
                  CMD_POWEROFF,
                  CMD_UPDATE,
                  CMD_WBOOT };

/* status of a service and return codes - errors and success */
enum svc_status {  RT_TMPNOW=1,     /* now you are on it - only for clients */
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


/* actions for i/o handlers (see comm/do_*) */
#define ACT_SERV     0
#define ACT_CLIENT   1

/* Messages to the outside */
#define MSG_CINIT          "cinit-0.2: Booting from "
#define MSG_NOT_ONE        "cinit should not be started directly, but by your kernel."
#define MSG_USAGE          "cinit: [cprofile:profile]\n"
#define MSG_ERR_OPEN       "open"
#define MSG_ERR_READ       "read"
#define MSG_ERR_IO         "i/o"
#define MSG_ERR_PIPE       "pipe"
#define MSG_ERR_FORK       "fork"
#define MSG_BIND           "bind"
#define MSG_LISTEN         "listen"
#define MSG_SOCKET         "socket"
#define MSG_CONNECT        "connect"
#define MSG_FCNTL          "fcntl"
#define MSG_ERR_EXECVE     "execve"
#define MSG_ERR_ALLOC      "memory allocation"
#define MSG_ERR_UMOUNT     "umount"
#define MSG_ERR_MOUNT      "mount"
#define MSG_TERMKILL       "sigterm"
#define MSG_KILLBILL       "sigkill"
#define MSG_NOT_DIR        "not a directory"
#define MSG_CHDIR          "chdir"
#define MSG_READLINK       "readlink"
#define MSG_ERR_ADD_SVC    "Adding service failed"
#define MSG_CMD_UNKNOWN    "Unknown command"
#define MSG_ERR_DEPS       "Too many dependencies"
#define MSG_ERR_ACCEPT     "accept"
#define MSG_ERR_WAITPID    "waitpid"
#define MSG_ERR_POLL       "poll"
#define MSG_ERR_MODIFY     "modify list failed"
#define MSG_ERR_COMM       "Communication failed"

#define MSG_ERR_LESS_ARGS  "Too less arguments!"
#define MSG_ERR_BAD_ARGS   "Wrong arguments / parameter"
#define MSG_ERR_ARGS_LEN   "Wrong parameter length"

#define LOG_SVC_STOPED     "Service stoped"
#define LOG_SVC_ONCE       "Started once"
#define LOG_SVC_RESPAWN    "Respawns now"
#define LOG_SVC_FAIL       "Service failed"
#define LOG_NEED_FAIL      "One or more need failed"
#define LOG_SVC_FAILED     "Service already failed, not starting."
#define LOG_SVC_NOTEXIST   "Service does not exist"

#define MSG_START_SVC      "Starting "
#define MSG_STOP_SVC       "Stoping "
#define MSG_EXEC_FAILED    "Failed to execute "

#define MSG_POWER_OFF      "Powering off..."
#define MSG_HALT           "Halting system ..."
#define MSG_REBOOT         "Rebooting ..."
#define MSG_RESCUE         "Switching to rescue mode ..."
#define MSG_UPDATE         "Updating cinit ..."
#define MSG_HOT_REBOOT     "Hot reboot in progress ..."

#define MSG_SHOULD_NOT_HAPPEN "This should not happen, I do not know what todo!"


struct listitem {
   char     *abs_path;           /* name of service */
   int      status;              /* current status */
   pid_t    pid;                 /* pid of service / respawn watcher */
   struct   listitem *before;    /* previous item */
   struct   listitem *after;     /* next item */
};

/* variables */
extern struct  listitem *list;   /* the process linked chain */
extern int     sock;             /* current writing/reading socket */
extern pid_t   cpid;             /* used by main() and reused be respaw_svc() */

/* functions (used by server and client) */
int   run_svc(char *rpath);
void  mini_printf(char *str, int fd);
void  set_signals(int action);
void  usage(char *banner, char *stext);

int   do_svc_name(int sock2, char *svc, int action);
int   do_change_status(char *svc, char *status, pid_t *pid, int sock2, int action);
char  do_result(int sock2, char *value);

/* server functions */
int      list_insert(char *path, int status);
struct   listitem *list_search(char *path);
int      list_delete(char *path);
int      run_init_svc(char *cinit_svc);
void     sigio(int socket);
void     sig_reboot(int signal);
void     panic(void);
void     sig_child(int signal);

/* client / message functions */
int      msg_svc_on_off(char *svc, char action);
int      msg_change_status(char *svc, char status, pid_t pid);
int      begin_msg(char cmd);

/* client functions */
int      run_run_svcs(char *abspath);
pid_t    exec_svc(char *abspath, int on);
pid_t    respawn_svc(char *abspath);
int      connect_sock(int socke);
char     **read_file(char *file);
void     sig_terminate(int signal);

/* listing functions (server only) */
int      list_insert(char *path, int status);
struct   listitem *list_search(char *path);
int      list_delete(char *path);
int      list_modify(char *path, int new_status, pid_t new_pid);

/* util */
int      msg_reboot(char cmd);

/* DEBUG */
#ifdef DEBUG
# define D_PRINTF(x)  ( printf("[%s:%d]: %s\n",__FILE__,__LINE__,x) )
#else 
# define D_PRINTF(x)  if(0)
#endif

/* macros */
#define SERVICE_LOG(svc,message) {  \
   mini_printf(svc,1);              \
   mini_printf(MSG_DP,1);           \
   mini_printf(message,1);          \
   mini_printf("\n",1);             \
}
#define LOG(s) {                    \
   mini_printf(s,1);                \
   mini_printf("\n",1);             \
}
#define P_START_SERVICE(name) { mini_printf(MSG_START_SVC,1); mini_printf(name,1); mini_printf("\n",1); }
#define P_EXEC_FAILED(name) { mini_printf(MSG_EXEC_FAILED,1); mini_printf(name,1); mini_printf("\n",1); }
