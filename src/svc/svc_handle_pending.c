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
 *    Handle pending services
 *
 */

#include <time.h>               /* NULL */

#include <stdio.h>              /* NULL */
#include "intern.h"             /* mini_printf */
#include "messages.h"           /* messages */
#include "svc.h"                /* svc_init */
#include "svc-intern.h"         /* svc_init */

/***********************************************************************
 * go through the pending list and exit at the end.
 * we will be called again after something changed:
 * svc_status_changed() is triggered by the death of one or more children
 * and sets up changes
 */
int svc_handle_pending(struct dep *pending)
{
   struct dep *tmp = pending;
   struct dep *hack;
   struct timespec ts;

   mini_printf(MSG_TREE_EXEC, 1);

   /* apply changes to changed services */
   while(tmp != NULL) {
      /* to be started */
      if(tmp->svc->status & (CINIT_ST_SH_ONCE | CINIT_ST_SH_RESPAWN)) {
         svc_start(tmp->svc);
         tmp = dep_entry_del(tmp);
      }

      switch(svc_needs_status(tmp->svc)) {
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
   }

   return 1;
}
