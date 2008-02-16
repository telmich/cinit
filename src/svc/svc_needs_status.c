/*******************************************************************************
 *
 * 2005-2008 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Return status of the needs of this service
 */

#include <stdio.h>      /* NULL                    */
#include "svc.h"        /* service information     */
#include "svc-intern.h" /* service information     */

int svc_needs_status(struct listitem *svc)
{
   int         retval   = CINIT_SNS_NEEDS_STARTED;
   struct dep  *deps    = svc->needs;

   if(deps == NULL) return CINIT_SNS_NEEDS_STARTED;    /* no needs, everything fine */

   do {
      /* worst case: need failed */
      if((deps->svc->status & CINIT_ST_NEED_FAILD) ||
         (deps->svc->status & CINIT_ST_ONCE_FAIL)  ||
         (deps->svc->status & CINIT_ST_BAD_ERR)    ){
            retval = CINIT_SNS_NEEDS_FAILED;
            break;
      }
      /* services are being started */
      if((deps->svc->status & CINIT_ST_SH_ONCE)    ||
         (deps->svc->status & CINIT_ST_SH_RESPAWN) ||
         (deps->svc->status & CINIT_ST_ONCE_RUN)   ){
  //          printf("%s (%ld) waits for %s (%ld)\n",svc->abs_path, svc->status, deps->svc->abs_path, deps->svc->status);
            retval = CINIT_SNS_NEEDS_UNFINISHED;
      }
      deps = deps->next;
   } while(deps != svc->needs);
   
   return retval;
}
