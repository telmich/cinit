/*******************************************************************************
 *
 * 2007-2008 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Disable a service (with or without dependencies)
 *
 */

#include "cinit.h"              /* structure: cinit_answer */

int answer_svc_stop(char *svc, struct cinit_answer *asr)
{
   struct listitem *tmp;

   tmp = list_search(svc);
   if(!tmp) {
      asr->ret = CINIT_ASW_SVC_UNKNOWN;
   } else {
      if(tmp->status & (CINIT_ST_RESPAWNING | CINIT_ST_ONCE_RUN)) {
         asr->ret = svc_disable(tmp);
      } else { /* not running, nothing todo */
         asr->ret = CINIT_ASW_OK;
      }
   }

   return 1;
}
