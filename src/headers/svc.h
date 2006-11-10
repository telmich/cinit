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
   struct   listitem *prev;      /* previous item                             */
   struct   listitem *next;      /* next item                                 */

   char     *abs_path;           /* name of service                           */
   int      status;              /* current status                            */
   pid_t    pid;                 /* pid of service / respawn watcher          */


   struct   dep      *wanted;    /* list of services that want this service   */
   struct   dep      *needed;    /* list of services that need this service   */

   struct   dep      *wants;     /* list of services that this service wants  */
   struct   dep      *needs;     /* list of services that this service needs  */
};

/* list of dependencies */
struct dep {
   struct dep        *prev;
   struct dep        *next;
   struct listitem   *svc;
};

/* variables */
extern struct  listitem *svc_list;  /* the process linked chain         */
extern struct  dep      *svc_init;  /* the services to start            */

/* list functions */
struct         listitem *list_insert(char *path, int status);
int            list_delete(char *path);
int            list_modify(char *path, int new_status, pid_t new_pid);
struct         listitem *list_search(char *path);
inline struct  listitem *list_search_pid(pid_t pid);
int            list_display_all();


/* service */
int               svc_known(char *svc);
struct listitem  *svc_create(char *svc);
int               gen_svc_tree(char *svc);
int               check_add_deps(struct listitem *svc, int type);
int               dep_entry_add(struct dep **list, struct dep *new);
int               tree_exec(struct dep *start);


enum dep_types {
   DEP_WANTS,
   DEP_NEEDS
};

#endif   /* _CINIT_SVC_H */
