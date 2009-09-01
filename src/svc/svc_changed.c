/*******************************************************************************
 *
 * 2009 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Handle changed services
 *
 */

#include <sys/wait.h>            /* Macros for waitpid   */
#include <stdio.h>               /* NULL                 */
//#include <sys/time.h>            /* gettimeofday()    */ /* FIXME: CHECK POSIX */
//#include <time.h>                /* time(),gettime..  */ /* FIXME: CHECK POSIX */

#include "svc-intern.h"          /* listem               */
#include "svc.h"                 /* service status       */
#include "intern.h"              /* mini_printf          */
//#include "messages.h"            /* messages/D_PRINTF */


/***********************************************************************
 * sig_child: (c)collect the children
 */
int svc_changed()
{
   int success;
   int changes = 0;
   struct listitem *svc;

   while(changelist.changed) {
      /* get next element and unset the changed attribute */
      svc = changelist.changed;
      changelist.changed = svc->changed;
      svc->changed = NULL;

      success = (WIFEXITED(svc->waitpid) && !WEXITSTATUS(svc->waitpid)) ? 1 : 0;


      /************************************************************************
       * Status translation table
       */
      switch(svc->status) {
         case CINIT_ST_ONCE_RUN:
            svc->status = success ? CINIT_ST_ONCE_OK : CINIT_ST_ONCE_FAIL;
         break;
         case CINIT_ST_RESPAWNING:
//            svc_start(svc, svc->
         break;
         default:
            mini_printf("BUG: Status was not allowed to exit", 2);
         break;
      }

      /*
       * respawn: restart: FIXME Delay for regular dying services 
      if(svc->status == CINIT_ST_RESPAWNING) {
         svc_report_status(svc->abs_path, MSG_SVC_RESTART, NULL);

         // delay = MAX_DELAY / (time(NULL) - svc->start);
          * if(gettimeofday(&now,NULL) == -1) {
          * print_errno(MSG_GETTIMEOFDAY);; delay = 0; } else { delay =
          * MAX_DELAY / (now.tv_sec - svc->start); } 
          */

         //delay = 5;

         /*
          * int test = time(NULL); test++; D_PRINTF("WHILE: IM respawn / for 
          * printf!\n"); printf("sig_child: %d, %d, %d, %d\n", MAX_DELAY,
          * (int) time(NULL), (int) svc->start, (int) (test - svc->start) ); 
          */

//         svc_start(svc, delay);
/*      }
      if(svc->status == CINIT_ST_STOPPING) {
         if(WIFEXITED(tmp) && !WEXITSTATUS(tmp)) {
            svc_set_status(svc, CINIT_ST_STOPPED);
         } else {
            svc_set_status(svc, CINIT_ST_STOP_FAIL);
         }
      } */
   }

   return changes;
}
