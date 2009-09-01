/*******************************************************************************
 *
 * 2005-2009 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    The child handler (may *not* exec other functions!)
 *
 */

#include <sys/wait.h>            /* waitpid           */

#include "intern.h"              /* mini_printf       */
#include "svc-intern.h"          /* list_search_pid   */

/***********************************************************************
 * sig_child: (c)collect the children
 */
void sig_child(int tmp)
{
   /*
    * New code: - search for pid in service list * if (respawn) -> start new -
    * insert delay? if exit code is non-zero? if uptime too less? * if (once)
    * -> update service status * else ignore, but reap away 
    */
   pid_t pid;
   struct listitem *svc;

   while((pid = waitpid(-1, &tmp, WNOHANG)) > 0) {
      /* check if process was a service */
      svc = list_search_pid(pid);

      if(!svc) continue; /* ignore crap that was not caught by others */

      svc->pid     = 0;
      svc->waitpid = tmp;
      svc->changed = changelist.changed;  /* save end of list     */
      changelist.changed = svc;           /* insert as first item */
   }
}
