/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 */

#ifndef _CINIT_H
#define _CINIT_H

/* includes */
#include <sys/types.h>  /* pid_t */
#include "config.h"     /* paths, socket options, etc. */

/***********************************************************************
 * Defines
 */
#define SLASH "/"
#define CINIT_CONFDIR   CINIT_DIR SLASH C_CONFDIR
#define CINIT_PANIC  CINIT_CONFDIR SLASH C_PANIC

enum {         /* FIXME: there are some default defines somewhere for that */
   FD_IN=0,
   FD_OUT=1,
   FD_ERR=2
};

enum {         /* returns of openreadclose */
   ORC_OK,
   ORC_ERR_NONEXISTENT,
   ORC_ERR_OPEN,
   ORC_ERR_READ,
   ORC_ERR_CLOSE,
   ORC_ERR_MEM
};

/* values for execute_sth:
 * STRICT: print and error, if .../on does not exist
 * NOSTRICT: no .../on is fine
 */
enum {
   EXEC_STRICT,
   EXEC_NOSTRICT
};

enum {
   FE_FILE,       /* file exists and is a file     */
   FE_OTHER,      /* file exists, but is no file   */
   FE_NOT,        /* file does not exist           */
   FE_ERR         /* some error occured            */
};

/***********************************************************************
 * Paths
 */
#define CINIT_SVCDIR CINIT_DIR SLASH SVCDIR
#define CINIT_INIT CINIT_SVCDIR SLASH C_INIT
#define CINIT_TMNT CINIT_DIR SLASH C_TMP
#define CINIT_SOCK CINIT_TMNT SLASH C_SOCK
#define CINIT_BIN  PREFIX SLASH "sbin" SLASH "cinit"

#define CINIT_CONFDIR   CINIT_DIR SLASH C_CONFDIR
#define CINIT_PANIC     CINIT_CONFDIR SLASH C_PANIC
#define CINIT_UMOUNT    CINIT_CONFDIR SLASH C_UMOUNT

/* actions for i/o handlers (see comm/do_*) */
#define ACT_SERV     0
#define ACT_CLIENT   1

/* functions (used by server and client) */
int   run_svc(char *rpath);
void  mini_printf(char *str, int fd);
void  set_signals(int action);
void  usage(char *banner, char *stext);

int   do_svc_name(int sock2, char *svc, int action);
int   do_change_status(char *svc, char *status, pid_t *pid, int sock2, int action);
char  do_result(int sock2, char *value);

/* core functions */
void     do_reboot(int signal);
void     panic(void);
void     sig_child(int signal);

/* client / message functions */
int      msg_svc_on_off(char *svc, char action);
int      msg_change_status(char *svc, char status, pid_t pid);
int      begin_msg(char cmd);

/* client functions */
pid_t    respawn_svc(char *abspath);
char     **read_file(char *file);
void     sig_terminate(int signal);

/* generic */
void execute_sth(char *basename);
int path_append(char *path, char *append);
int path_absolute(char *relpath, char *buf, size_t size);
int openreadclose(char *filename, char **where);
char *strip_final_newline(char *str);
int file_exists(char *filename);

/* util */
int      msg_reboot(char cmd);
void     print_errno(char *text);

/* os-functions */
void cinit_reboot(void);
void cinit_halt(void);
void cinit_poweroff(void);

#endif   /* _CINIT_H */
