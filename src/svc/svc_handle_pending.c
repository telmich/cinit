/*******************************************************************************
 *
 * 2006-2009 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Start the service tree we created
 */

#include <time.h>               /* NULL */

#include <stdio.h>              /* NULL */
#include "intern.h"             /* mini_printf */
#include "messages.h"           /* messages */
#include "svc.h"                /* svc_init */
#include "svc-intern.h"         /* svc_init */

/* some thoughts...
 *
 * - we already generated the tree, now we need to start it from
 *   the endings
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
   struct dep *hack;
   struct timespec ts;

   mini_printf(MSG_TREE_EXEC, 1);

   /*
    * the main starting loop: All services in this list should be started, but
    * it is possible that dependent services are in the list. In this case
    * simply skip the current service 
    */
   do {
      switch (svc_needs_status(tmp->svc)) {
         case CINIT_SNS_NEEDS_STARTED:
            /*
             * FIXME: MSG_* 
             */
            svc_report_status(tmp->svc->abs_path, "Finished needs.", NULL);

            /* execute service, add dependencies, remove from list */
            svc_start(tmp->svc);
            if(!dep_needs_wants_add(&tmp, tmp->svc, DEP_NEEDS)) return 0;
            if(!dep_needs_wants_add(&tmp, tmp->svc, DEP_WANTS)) return 0;
            tmp = dep_entry_del(tmp);
            break;

         case CINIT_SNS_NEEDS_FAILED:
            /*
             * mark service as NEED_FAILD and delete from list 
             */
            /* FIXME: reporting moved to svc_needs_status.c */
            //svc_report_status(tmp->svc->abs_path, MSG_SVC_NEED_FAIL, NULL);
            svc_set_status(tmp->svc, CINIT_ST_NEED_FAILD);
            tmp = dep_entry_del(tmp);
            break;

         case CINIT_SNS_NEEDS_UNFINISHED:
            /*
             * FIXME: continue here! 
             */

            hack = tmp->svc->needs;
            do {
               // get needs
//               printf("%s waits for %s",tmp->svc->abs_path,hack->svc->abs_path);
               // display status of needs
               // printf("%s: %ld\n",hack->svc->abs_path,hack->svc->status);
               hack = hack->next;
            } while(hack != tmp->svc->needs);

            tmp = tmp->next;    /* continue with the next item */
            ts.tv_sec = 2;
            ts.tv_nsec = 0;
            nanosleep(&ts, NULL);
            break;
      }
      /*
       * This case happens, if it's the last service waiting for something 
       */
      /*
       * if(tmp == tmp->next) {
       * 
       * nanosleep()? printf("BUUUUUUUUUUUUUG, exit\n"); break; } 
       */
   } while(tmp != NULL);

   return 1;
}
