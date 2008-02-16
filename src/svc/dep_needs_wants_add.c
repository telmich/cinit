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
 *    Add all wants or needs from a specific service to dep list
 *       -> this builds the needs and needed_by and
 *       -> or this builds the wants and wanted_by and
 *
 *    This function is used to fillup the starting list with dependencies
 *    after a service has sucessfully been executed.
 */

#include <stdio.h>         /* NULL        */
#include "svc-intern.h"    /* struct *dep */
#include "svc.h"           /* struct *dep */

/*
 * list: pointer to the list
 * svc:  pointer to data to the service
 */

int dep_needs_wants_add(struct dep **list, struct listitem *svc, int type)
{
   struct dep *tmp, *new, *end;

   if(type == DEP_NEEDS) {
      end = svc->needed_by;
   } else {
      end = svc->wanted_by;
   }

   /* Place to the first dependency of this service */
   tmp = end;
   if(tmp != NULL) {
      do {
         /* Add service to the starter list, which
          *    - should be started once
          *    - should be respawned (both VIRGIN services!)
          *    - and which are not already in the list!
          */
         if(((tmp->svc->status   & CINIT_ST_SH_ONCE)     ||
             (tmp->svc->status   & CINIT_ST_SH_RESPAWN)) &&
            !(tmp->svc->status   & CINIT_ST_IN_LIST)) {
               new = dep_create(tmp->svc);
               if(!new) return 0;
               tmp->svc->status |= CINIT_ST_IN_LIST;
               dep_entry_add(list, new);
            }
         /* FIXME: Clearify if we should go forward or backwards?
          * this decision will influence starting order
          * and may thereby add a minimal mount of speed enhancement
          *
          * As far as I can see it is not predictable, which way is
          * better, because it heavily depends on the other services.
          *
          * If you know better, provide me with a patch ;-)
          */
         tmp = tmp->next;
      } while(tmp != end);
   }

   return 1;
}
