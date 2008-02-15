/*******************************************************************************
 *
 * 2006-2008 Nico Schottelius (nico-cinit at schottelius.org)
 *
 * This file is part of cinit.

 * cinit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cinit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cinit.  If not, see <http://www.gnu.org/licenses/>.

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
   struct      listitem *prev;   /* previous item                             */
   struct      listitem *next;   /* next item                                 */

   char        *abs_path;        /* name of service                           */
   uint32_t    status;           /* current status                            */
   pid_t       pid;              /* pid of service / respawn watcher          */
   time_t      start;            /* time the process was started last time    */


   struct   dep      *wanted_by; /* list of services that want this service   */
   struct   dep      *needed_by; /* list of services that need this service   */

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
struct         listitem *list_insert(char *path, uint_32t status);
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
void              shutdown_services(struct listitem *start);

void              svc_start(struct listitem *,     int);
void              svc_stop(struct listitem *);
void              svc_stop_deps(struct listitem *, int);



/***********************************************************************
 * to decide whether to operate on needs or wants
 */
enum dep_types {
   DEP_WANTS,
   DEP_NEEDS
};

#endif   /* _CINIT_SVC_INTERN_H */
