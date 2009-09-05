/*******************************************************************************
 *
 * 2007-2009 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Stop a service
 *
 *    Status: Written, looks finished, but untested.
 *
 * respawn:
 *    - disable respawning: set status to ST_RESPAWN_STOP
 *    - send term signal? no => can be done in "off"
 *       => set environment CINIT_SVC_PID
 * once and respawn:
 *    - look for 'off' binary, execute if present
 *    - mark service as off or delete it?
 */

#include <stdio.h>              /* NULL */
#include <unistd.h>             /* fork */
#include <string.h>             /* strerror */
#include <errno.h>              /* errno */
#include <limits.h>             /* PATH_MAX */
#include <sys/wait.h>           /* waitpid */

#include "svc.h"                /* struct * */
#include "svc-intern.h"         /* struct * */
#include "messages.h"           /* MSG_* */
#include "intern.h"             /* execute_sth */
#include "cinit.h"              /* CINIT_DATA_LEN */
#include "signals.h"            /* signal handling */

uint32_t svc_disable(struct listitem *li)
{
   char buf[CINIT_DATA_LEN];

   svc_set_status(li, CINIT_ST_SH_STOP);

   li->pid = fork();

   /**********************      Error      ************************/
   if(li->pid < 0) {
      svc_report_status(li->abs_path, MSG_SVC_FORK, strerror(errno));
      svc_set_status(li, CINIT_ST_BAD_ERR);
      return CINIT_ASW_ERR_INTERN;
   }

   /********************** Parent / fork() ************************/
   if(li->pid > 0) {
      /* FIXME: why duplicate? */
      svc_set_status(li, CINIT_ST_SH_STOP);
      return CINIT_ASW_OK;
   }

   /********************** Client / fork() ************************/
   svc_report_status(li->abs_path, MSG_SVC_STOP, NULL);

   cinit_cp_data(buf, li->abs_path);
   if(!path_append(buf, C_OFF)) _exit(1);

   /*
    * Check for existence 
    */
   li->status = file_exists(buf);

   if(li->status == FE_NOT) {
      _exit(0);
   }

   if(li->status == FE_FILE) {
      /*
       * FIXME: reset signals: Is this necessary? Or does fork clean it anyway? 
       */
      set_signals(SIGSTAGE_CLIENT);

      /*
       * and now, fire it up 
       */
      execute_sth(buf);
   } else {
      /*
       * FIXME: report? 
       */
      /*
       * either no file or an error 
       */
      _exit(1);
   }

   /* FIXME: we will never return ... */
   return CINIT_ASW_OK;
}
