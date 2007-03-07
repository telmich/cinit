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

   char        *abs_path;        /* name of service                           */
   long int    status;           /* current status                            */
   pid_t       pid;              /* pid of service / respawn watcher          */


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
//int            list_display_all(); /* debug only */


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
void              svc_start(struct listitem *li);
void              shutdown_services(void);


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
   ST_SH_ONCE     = 0x1,     /* service SHould be started once            */
   ST_SH_RESPAWN  = 0x2,     /* service SHould respawn                    */
   ST_ONCE_OK     = 0x4,     /* service was successfully started once     */
   ST_ONCE_FAIL   = 0x8,     /* service failed to start                   */
   ST_RESPAWNING  = 0x10,    /* service is respawning                     */
   ST_NEED_FAILD  = 0x20,    /* this service is not started, need failed  */
   ST_IN_LIST     = 0x40,    /* this service is being started (= in list) */
   ST_BAD_ERR     = 0x80,    /* some kind of error that SHOULD NOT happen */
   ST_ONCE_RUN    = 0x100    /* the once process is currently running     */
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
