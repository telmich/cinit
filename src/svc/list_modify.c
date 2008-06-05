
/*******************************************************************************
 *
 * 2005      Marcus Przyklink (downhill-clinux (at) burningchaos.org)
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
 *    OBSOLETED. Not in use anymore.
 * 
 *    List handling
 */

#error "NOT IN USE"

#include <stdlib.h>
#include <string.h>
#include "cinit.h"
#include "comm.h"               /* for ST_OFF */
#include "svc.h"                /* for ST_OFF */

/* change pid and status of a process */
int list_modify(char *path, int new_status, pid_t new_pid)
{
   struct listitem *tmp;

   tmp = list_search(path);
   if(tmp == NULL) {
      return 0;
   }

   /*
    * delete objects, which are killed 
    */
   if(new_status == ST_OFF) {
      return list_delete(path);
   } else {
      tmp->status = new_status;
      tmp->pid = new_pid;
   }

   return 1;
}
