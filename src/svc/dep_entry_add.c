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

#include <stdio.h>         /* NULL     */
#include "svc-intern.h"    /* types    */

/*
 * list: pointer to the list
 * new:  pointer to data to insert (already filled up)
 *
 * We add the new element BEFORE the existing element!
 */
void dep_entry_add(struct dep **deplist, struct dep *new)
{
   if(*deplist == NULL) {                          /* new list          */
      *deplist                = new;
      (*deplist)->prev        = *deplist;
      (*deplist)->next        = *deplist;
   } else {                                        /* already existing  */
      new->next               = *deplist;          /* new-> first       */
      new->prev               = (*deplist)->prev;  /* last <- new       */
      (*deplist)->prev->next  = new;               /* last -> new       */
      (*deplist)->prev        = new;               /* new <- first      */
   }
}
