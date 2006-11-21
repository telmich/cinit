/***********************************************************************
 *
 *    2006,2006 Nico Schottelius (nico-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 *
 *    Start the service tree we created
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
extern struct  dep      *svc_init;  /* the services to start            */
extern struct  listitem *svc_list;  /* the list of services             */

/* list functions */
struct         listitem *list_insert(char *path, int status);
int            list_delete(char *path);
int            list_modify(char *path, int new_status, pid_t new_pid);
struct         listitem *list_search(char *path);
inline struct  listitem *list_search_pid(pid_t pid);
int            list_display_all();


/* service */
struct listitem  *svc_create(char *svc);
struct listitem  *gen_svc_tree(char *svc);
int               check_add_deps(struct listitem *svc, int type);
int               dep_entry_add(struct dep **list, struct dep *new);
struct dep       *dep_entry_del(struct dep *del);
int               tree_exec(struct dep *start);
int               svc_set_status(struct listitem *li, int status);
int               svc_should_respawn(struct listitem *li);
int               svc_needs_status(struct listitem *li);
int               dep_needs_wants_add(struct dep **list, struct listitem *svc);
struct dep        *dep_create(struct listitem *svc);
void              svc_success(struct listitem *li);


/***********************************************************************
 * to decide whether to operate on needs or wants
 */
enum dep_types {
   DEP_WANTS,
   DEP_NEEDS
};

/***********************************************************************
 * status of a service and return codes - errors and success
 */
enum svc_status_old {
   ST_TMPNOW=1,     /* the client is now starting the service NEEDED??? */
   ST_NOTEXIST,     /* service does not exist                           */

   ST_NEED_FAIL,    /* failed to start a need for this service          */
   ST_FAIL,         /* failed to start service                          */

   ST_OFF,          /* service is off                                   */
   ST_OFF_ALL,      /* service and those that need it are off           */
   ST_OFF_ALL_F,    /* same, but something failed                       */
   ST_OFF_WANTS,    /* service + those that need or want it are off     */
   ST_OFF_WANTS_F,  /* same, but something failed                       */

   ST_TMP,          /* currently working on it                          */
   ST_ONCE,         /* executed once                                    */
   ST_RESPAWN       /* running and respawning                           */
};

/***********************************************************************
 * The real status types a service may have (ignore above)
 * We have 32 Bits, we should use them ;-)
 */
enum svc_status {
   /* first define basics */
   ST_SH_ONCE     = 1,     /* service SHould be started once            */
   ST_SH_RESPAWN  = 2,     /* service SHould respawn                    */
   ST_ONCE_OK     = 4,     /* service was successfully started once     */
   ST_ONCE_FAIL   = 8,     /* service failed to start                   */
   ST_RESPAWNING  = 16,    /* service is respawning                     */
   ST_NEED_FAILD  = 32,    /* this service is not started, need failed  */
   ST_IN_LIST     = 64     /* this service is being started (= in list) */
};

/***********************************************************************
 * Possibilities the needs of a service may have
 */
enum svc_needs_status {
   SNS_NEEDS_STARTED = 1,  /* all needs are started. We may start, too  */
   SNS_NEEDS_FAILED,       /* one ore more needs failed                 */
   SNS_NEEDS_UNFINISHED    /* one ore more needs are not yet started    */
};
#endif   /* _CINIT_SVC_H */
