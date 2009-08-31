/*******************************************************************************
 *
 * 2005      Marcus Przyklink      (downhill-clinux (at) burningchaos.org)
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
 *    List handling
 */

#include <stdio.h>              /* NULL */
#include <string.h>             /* strcmp */
#include "svc-intern.h"         /* struct listitem */

/* search for an entry by path, reverse: from end to the beginning */
struct listitem *list_search(char *path)
{
   struct listitem *tmp;

   if(svc_list == NULL) return NULL;
   
   tmp = svc_list;

   do {
      if(!strcmp(path, tmp->abs_path)) {
         return tmp;
      }
      tmp = tmp->prev;
   } while(tmp != svc_list);

   return NULL;
}
