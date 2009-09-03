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
 *    Pre calculate the service tree (recursive calling)
 */

#include <stdlib.h>

#include "intern.h"             /* functions */
#include "svc.h"                /* constants */
#include "svc-intern.h"         /* functions */

struct listitem *gen_svc_tree(char *svc)
{
   struct listitem *li;
   struct dep *deps;

   /* only do something if the service is not already known */
   if((li = list_search(svc))) return li;

   /* create a template, so other instances won't try to recreate us */
   if(!(li = svc_create(svc))) return NULL;

   /* add dependencies */
   if(!check_add_deps(li, DEP_NEEDS)) return NULL;
   if(!check_add_deps(li, DEP_WANTS)) return NULL;

   /* If it has no dependencies, then the service is a start service. */
   if(!li->wants && !li->needs) {
      deps = dep_create(li);
      if(!deps) return NULL;
      dep_entry_add(&deps_pending, deps);

      /*
       * Mark it as being in the startup list, so it does not get added again
       * in a dep_needs_wants_add call 
       */
      li->status |= CINIT_ST_IN_LIST;
   }

   return li;
}
