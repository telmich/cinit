/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 */

#ifndef _CINIT_H
#define _CINIT_H

/* includes */
#include <sys/types.h>  /* pid_t */
#include "config.h"     /* paths, socket options, etc. */

/* paths */
#define C_ONARG   C_ON  C_PARAMS
#define C_OFFARG  C_OFF C_PARAMS
#define C_ONENV   C_ON  C_ENV
#define C_OFFENV  C_OFF C_ENV

#define CINIT_INIT CINIT_DIR SLASH C_INIT
#define CINIT_TMNT CINIT_DIR SLASH C_TMP
#define CINIT_SOCK CINIT_TMNT SLASH C_SOCK
#define CINIT_BIN  PREFIX SLASH "sbin" SLASH "cinit"

/* commands (maximum: 2^8 = 256, because we use a single byte) */
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
void     do_reboot(int signal);
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
int      list_delete(char *path);
int      list_modify(char *path, int new_status, pid_t new_pid);
struct   listitem *list_search(char *path);
inline struct   listitem *list_search_pid(pid_t pid);

/* util */
int      msg_reboot(char cmd);

/* os-functions */

void cinit_reboot(void);
void cinit_halt(void);
void cinit_poweroff(void);

#endif   /* _CINIT_H */
