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
 *    sends data from the client to cinit
 *
 */

#include "ipc.h"        /* IPC                     */
#include "cinit.h"      /* struct cinit_message    */

int cinit_send_to(struct cinit_question *data, struct cinit_answer *res)
{
   if(!cinit_ipc_logon())        return 0;
   if(!cinit_ipc_csend(data))    return 0;
   if(!cinit_ipc_cread(res))     return 0;
   if(!cinit_ipc_logoff())       return 0;
   return 1;
}
