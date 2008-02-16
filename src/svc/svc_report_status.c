/*******************************************************************************
 *
 * 2006-2008 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Tell the world what happened to the service
 */

#include "intern.h"        /* mini_printf    */
#include "messages.h"      /* MSG_INTRO_SVC  */

void svc_report_status(char *svc, char *msg, char *err)
{
   mini_printf(MSG_INTRO_SVC,1);
   mini_printf(svc,1);
   mini_printf(": ",1);
   mini_printf(msg,1);
   if(err) {
      mini_printf(" (",1);
      mini_printf(err,1);
      mini_printf(")",1);
   }
   mini_printf("\n",1);
}
