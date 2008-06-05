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
 *    List handling
 */

#include <stdlib.h>     /* free        */
#include "intern.h"     /* list_search */
#include "svc-intern.h" /* listitem    */

/* ... */
int list_delete(char *path)
{
   struct listitem *tmp;

   tmp = list_search(path);

   if(tmp == NULL) {
      return 0;
   }

   tmp->next->prev = tmp->prev;
   tmp->prev->next = tmp->next;

   free(tmp);

   return 1;
}
