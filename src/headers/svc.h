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
   struct   listitem *prev;      /* previous item                             */
   struct   listitem *next;      /* next item                                 */

   struct   dep      *wants;     /* list of services that want this service   */
   struct   dep      *needs;     /* list of services that need this service   */
};

/* list of dependencies */
struct dep {
   struct listitem   *svc;
   struct dep        *prev;
   struct dep        *next;
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
int check_add_deps(char *svc, int type);

enum dep_types {
   DEP_WANTS,
   DEP_NEEDS
};

#endif   /* _CINIT_SVC_H */
