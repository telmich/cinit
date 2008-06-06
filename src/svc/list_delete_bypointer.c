
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

#include <stdlib.h>             /* free */
#include "svc-intern.h"         /* listitem */

int list_delete_bypointer(struct listitem *li)
{
   /* FIXME: add warning? this case should not happen */
   if(li == NULL) {
      return 0;
   }

   li->next->prev = li->prev;
   li->prev->next = li->next;

   free(li);

   return 1;
}
