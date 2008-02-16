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
 *    Show all list elements - mainly for debugging
 */

#include <stdio.h>         /* NULL     */

#include "messages.h"      /* D_PRINTF */
#include "svc.h"

int list_display_all()
{
   struct listitem *tmp;

   if(svc_list == NULL) {
      return 0;
   } else {
      tmp = svc_list;
   }

   do {
      D_PRINTF("Service: ");
      D_PRINTF(tmp->abs_path);
      D_PRINTF("\n");

      tmp = tmp->prev;
   } while(tmp != svc_list);
   
   return 1;
}
