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
 *    Retrieves pid of a service
 *
 */

#include "cinit.h"      /* header for clients   */

/* returns either the status (>0)
 * or -1 on memory error
 */
pid_t cinit_svc_get_pid(char *name)
{
   struct cinit_question qsn;
   struct cinit_answer   asr;

   qsn.cmd = CINIT_MSG_GET_PID;
   cinit_cp_data((qsn.data), name);
   qsn.options = 0;

   if(!cinit_send_to(&qsn, &asr)) return -1;

   if(asr.ret == CINIT_MSG_OK) {
      return (pid_t) asr.options;
   } else {
      return (pid_t) 0;
   }
}
