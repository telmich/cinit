
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
 *    This function reads the full service tree and generates
 *    a list of services to begin shutdown (those that are not
 *    wanted or needed by any other service).
 */

#include <stdio.h>              /* NULL */

#include "svc-intern.h"         /* structs */
#include "intern.h"             /* structs */

struct dep *gen_halt_list(struct listitem *svc_tree)
{
   struct dep *list = NULL, *new = NULL;
   struct listitem *tmp;

   /*
    * no tree? nothing to shutdown. 
    */
   if(!svc_tree) {
      return NULL;
   }

   /*
    * find all services that do not depend on other services: - empty wants?
    * (currently ignore them) - empty needs! 
    */
   tmp = svc_tree;
   do {
      if(tmp->needs == NULL) {
         /*
          * create new dependency 
          */
         new = dep_create(tmp);
         if(!new)
            return NULL;

         dep_entry_add(&list, new);
      }
      tmp = tmp->next;
   } while(tmp != svc_tree);

   return list;
}
