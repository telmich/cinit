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
 *    List handling: Add a new item to a (non-)empty list
 */

#include <stdio.h>         /* NULL           */
#include <stdlib.h>        /* free()         */
#include "svc-intern.h"    /* struct *dep    */

/*
 * tmp:  pointer to data to remove (must not be NULL)
 *
 * Returns either the next object or NULL if there's no next object
 */
struct dep *dep_entry_del(struct dep *del)
{  
   struct dep *tmp;

   /* last service in the list */
   if(del->next == del && del->prev == del) {
      tmp = NULL;
   } else {
      /* remove from list */
      del->prev->next = del->next;
      del->next->prev = del->prev;
      tmp = del->next;
   }

   free(del);

   return tmp;
}
