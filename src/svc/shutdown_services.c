
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
 *    Shutdown all services: This is more or less the negative
 *    version of 'tree_exec()'
 */

#include "svc-intern.h"         /* struct */
#include "svc.h"                /* defines */

void shutdown_services(struct listitem *svc)
{
   /*
    * The shutdown procedure:
    *
    * - take the list of running services
    * - begin at the first (could be any) service and
    *    - shutdown all services that depend on that service
    *    --> recursive
    * - take the next service (if there is still one ;-)
    */

   while(svc) {
      svc_stop_deps(svc, CINIT_SSSO_COMPLETE);
      svc = svc->next;
      list_delete_bypointer(svc->prev);
   }

   return;
}
