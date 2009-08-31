/*******************************************************************************
 *
 * 2006-2009 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Set the status of a service
 */

#include <stdio.h>              /* NULL */

#include "svc.h"                /* listitem, svc_report_status */
#include "svc-intern.h"         /* listitem, svc_report_status */
#include "messages.h"           /* messages */

void svc_success(struct listitem *li)
{
   if(li->status & CINIT_ST_ONCE_RUN) {
      svc_report_status(li->abs_path, MSG_SVC_OK_ONCE, NULL);
      li->status = CINIT_ST_ONCE_OK;
   } else {
      svc_report_status(li->abs_path, MSG_SVC_OK_RESPAWN, NULL);
      li->status = CINIT_ST_RESPAWNING;
   }
}
