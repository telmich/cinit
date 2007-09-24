/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 *
 *    Internal service specifics
 */ 


#ifndef __CINIT_SVC_INTERN_H
#define __CINIT_SVC_INTERN_H

/* includes */
#include <sys/types.h>  /* pid_t */
#include "config.h"     /* paths, socket options, etc. */

/* service list */
struct listitem {
   struct   listitem *prev;      /* previous item                             */
   struct   listitem *next;      /* next item                                 */

   char        *abs_path;        /* name of service                           */
   long int    status;           /* current status                            */
   pid_t       pid;              /* pid of service / respawn watcher          */
   time_t      start;            /* time the process was started last time    */


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
extern struct  dep      *svc_init;  /* the services to start            */
extern struct  listitem *svc_list;  /* the list of services             */

/* list functions */
struct         listitem *list_insert(char *path, int status);
int            list_delete(char *path);
int            list_modify(char *path, int new_status, pid_t new_pid);
struct         listitem *list_search(char *path);
struct         listitem *list_search_pid(pid_t pid);

/* service */
struct listitem  *svc_create(char *svc);
struct listitem  *gen_svc_tree(char *svc);
int               check_add_deps(struct listitem *svc, int type);
void              dep_entry_add(struct dep **list, struct dep *new);
struct dep       *dep_entry_del(struct dep *del);
int               tree_exec(struct dep *start);
int               svc_set_status(struct listitem *li, int status);
int               svc_should_respawn(struct listitem *li);
int               svc_needs_status(struct listitem *li);
int               dep_needs_wants_add(struct dep **list, struct listitem *svc, int type);
struct dep        *dep_create(struct listitem *svc);
void              svc_success(struct listitem *li);
void              svc_fail(struct listitem *li);
void              svc_report_status(char *svc, char *msg, char *err);
void              svc_start(struct listitem *li, int delay);
void              shutdown_services(struct listitem *start);



/***********************************************************************
 * to decide whether to operate on needs or wants
 */
enum dep_types {
   DEP_WANTS,
   DEP_NEEDS
};

#endif   /* _CINIT_SVC_INTERN_H */
