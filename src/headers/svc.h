/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 */

#ifndef _CINIT_SVC_H
#define _CINIT_SVC_H

/* includes */
#include <sys/types.h>  /* pid_t */
#include "config.h"     /* paths, socket options, etc. */

/* service list */
struct listitem {
   char     *abs_path;           /* name of service                           */
   int      status;              /* current status                            */
   pid_t    pid;                 /* pid of service / respawn watcher          */
   struct   listitem *before;    /* previous item                             */
   struct   listitem *after;     /* next item                                 */
   struct   listitem *wanted;    /* list of services that want this service   */
   struct   listitem *needed;    /* list of services that need this service   */
};

/* variables */
extern struct  listitem *list;   /* the process linked chain                  */

/* list functions */
int      list_insert(char *path, int status);
int      list_delete(char *path);
int      list_modify(char *path, int new_status, pid_t new_pid);
struct   listitem *list_search(char *path);
inline struct   listitem *list_search_pid(pid_t pid);
int      list_display_all();


/* service */
int svc_known(char *svc);
int svc_create(char *svc);
int gen_svc_tree(char *svc);

#endif   /* _CINIT_SVC_H */
