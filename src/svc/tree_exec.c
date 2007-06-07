/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Start the service tree we created
 */

#include <stdio.h>               /* NULL        */

#include "intern.h"              /* mini_printf */
#include "svc.h"                 /* svc_init    */
#include "messages.h"            /* messages    */

/* some thoughts...
 *
 * - we already generated the tree, we now need to start it from
 *   the ends
 *
 * - after starting the first service we have to care about SIG_CHILD
 *   to record changes
 *
 * - we execute all services in parallel without problems, because of
 *   SIG_CHILD notification
 * 
 * - After successfully starting the service we start the services that
 *   need or want that service
 */
int tree_exec(struct dep *start)
{
   struct dep *tmp = start;

   mini_printf(MSG_TREE_EXEC,1);

   /* the main starting loop: All services in this list should be
    * started, but it is possible that dependent services are in the
    * list. In this case simply skip the current service 
    */
   do {
      switch(svc_needs_status(tmp->svc)) {
         case SNS_NEEDS_STARTED:
            svc_report_status(tmp->svc->abs_path,"Needs sind durch",NULL);
            /* execute service, add dependencies, remowe from list */
            svc_start(tmp->svc,0);
            if(!dep_needs_wants_add(&tmp,tmp->svc,DEP_NEEDS)) return 0;
            if(!dep_needs_wants_add(&tmp,tmp->svc,DEP_WANTS)) return 0;
            tmp = dep_entry_del(tmp);
            break;

         case SNS_NEEDS_FAILED:
            /* mark service as NEED_FAILD and delete from list */
            svc_report_status(tmp->svc->abs_path,MSG_SVC_NEED_FAIL,NULL);
            svc_set_status(tmp->svc,ST_NEED_FAILD);
            tmp = dep_entry_del(tmp);
            break;

         case SNS_NEEDS_UNFINISHED:
            svc_report_status(tmp->svc->abs_path,"Needs am abarbeiten",NULL);
            /* continue with the next item */
            tmp = tmp->next;
            break;
      }
   } while(tmp != NULL);

   return 1;
}
