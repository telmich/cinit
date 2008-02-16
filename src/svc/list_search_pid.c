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
 *    List handling: Search by pid
 */

#include <stdio.h>      /* NULL              */
#include <sys/types.h>  /* pid_t             */
#include "svc-intern.h" /* struct listitem   */

struct listitem *list_search_pid(pid_t pid)
{
   struct listitem *tmp;

   if(svc_list == NULL) {
      return NULL;
   } else {
      tmp = svc_list;
   }

   do {
      if(pid == tmp->pid) {
         return tmp;
      }
      tmp = tmp->prev;
   } while(tmp != svc_list);

   return NULL;
}
