/*******************************************************************************
 *
 * 2008     Nico Schottelius (nico-cinit at schottelius.org)
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
 *    disables a service
 *
 */

#include "svc-intern.h"         /* list_search */
#include "cinit.h"              /* structure: cinit_answer */


/**
 * Returns the answer to the disable request to the client.
 */
int answer_svc_disable(char *svc, struct cinit_answer *asr)
{
   struct listitem *tmp;

   tmp = list_search(svc);
   if(!tmp) {
      asr->ret = CINIT_ASW_SVC_UNKNOWN;
   } else {
      asr->ret = svc_disable(tmp);
      asr->opt = 0;
   }

   return 1;
}
