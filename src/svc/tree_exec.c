/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Start the service tree we created
 */

#include <stdio.h>               /* NULL        */
#include "cinit.h"            
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
 * - After successfully starting the service we start the service that
 *   need or want that service
 *
 *
 *
 */

int tree_exec(struct dep *start)
{
   struct dep *tmp;
   
   tmp = start;

   mini_printf("========> tree_exec() \n",1);
   /* the main starting loop: All services in this list should be
    * started, but it is possible that dependent services are in the
    * list. In this case simply skip the current service 
    */
   do {
      /* FIXME debug */
      mini_printf("TEX::",1);
      mini_printf(tmp->svc->abs_path,1);
      mini_printf("\n",1);
      {
         struct dep *tmp2;
         tmp2=tmp->svc->needs;
         if(tmp2) {
            do {
               mini_printf("::",1);
               mini_printf(tmp2->svc->abs_path,1);
      mini_printf("\n",1);
               fprintf(stderr,"%s: <<%d>>\n",tmp2->svc->abs_path,tmp2->svc->status);
               tmp2 = tmp2->next;
            } while (tmp2 != tmp->svc->needs);
         }
      }

      switch(svc_needs_status(tmp->svc)) {
         case SNS_NEEDS_STARTED:
            mini_printf("abhaengigkeiten gestartet, exec; add wants, needs\n",1);
            svc_start(tmp->svc);

            /* execute service, remowe from list */
            /* FIXME check return code? */
            if(!dep_needs_wants_add(&tmp,tmp->svc,DEP_NEEDS)) return 0;
            if(!dep_needs_wants_add(&tmp,tmp->svc,DEP_WANTS)) return 0;

            /* delete service from list */
            tmp = dep_entry_del(tmp);
            break;

         case SNS_NEEDS_FAILED:
            /* mark service as NEED_FAILD and delete from list */
            svc_report_status(tmp->svc->abs_path,MSG_SVC_NEED_FAIL,NULL);
            svc_set_status(tmp->svc,ST_NEED_FAILD);
            tmp = dep_entry_del(tmp);
            break;

         case SNS_NEEDS_UNFINISHED:
            /* continue with the next item */
            tmp = tmp->next;
            break;
      }

   } while(tmp != NULL);

   return 1;
}
