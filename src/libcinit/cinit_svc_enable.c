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

#include <stdint.h>     /* integers             */
#include "cinit.h"      /* header for clients   */

uint32_t cinit_svc_enable(char *svc, uint32_t flag)
{
   struct cinit_question qsn;
   struct cinit_answer   asr;

   cinit_prepare_comm(&qsn, &asr, CINIT_QSN_SVC_START);
   cinit_cp_data((qsn.data), svc);

   qsn.opt = flag;

   if(!cinit_send_to(&qsn, &asr)) return CINIT_ASW_IPC_ERROR;

   /* add logic to display started services here
    * or:
    * add logic to start dependend services in here:
    * want to start a -> cinit returns needs b
    */ 

   return CINIT_ASW_IPC_ERROR;
}
