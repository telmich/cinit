
/*******************************************************************************
 *
 * 2008      Nico Schottelius (nico-cinit at schottelius.org)
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
 *    cinit reads a command sent by a client, called by ipc listener
 *
 */

#include "cinit.h"              /* structures */
#include "intern.h"             /* answer_svc_status() */

int read_command(struct cinit_question qsn, struct cinit_answer *asr)
{
   switch (qsn.cmd) {
      case CINIT_QSN_GET_VERSION:
         if(!answer_version(asr))
            return 0;
         break;

      case CINIT_QSN_GET_STATUS:
         if(!answer_svc_status(qsn.data, asr))
            return 0;
         break;

      case CINIT_QSN_GET_PID:
         if(!answer_svc_pid(qsn.data, asr))
            return 0;
         break;

      case CINIT_QSN_SVC_DISABLE:
         if(!answer_svc_disable(qsn.data, asr))
            return 0;
         break;

         /*
          * FIXME: stopped here case CINIT_MSG_SVC_ENABLE:
          * if(!answer_svc_enable(qsn.data, asr)) return 0; break; 
          */

         /*
          * Unknown command: should not happen :-) 
          */
      default:
         return 0;
         break;
   }

   return 1;
}
