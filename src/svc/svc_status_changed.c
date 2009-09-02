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
int svc_status_changed()
{
   int success;
   int tmp = 0;
   struct listitem *svc;
   pid_t pid;

   while((pid = waitpid(-1, &tmp, WNOHANG)) > 0) {
      svc = list_search_pid(pid);

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
   }

   return tmp;
}
