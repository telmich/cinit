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

#include <stdint.h>        /* uint32_t             */
#include <stdlib.h>        /* malloc               */
#include <string.h>        /* bzero / memset       */
#include "svc-intern.h"    /* the list pointer     */

struct listitem *list_insert(char *path, uint32_t status)
{
   struct listitem *tmp;

   tmp = malloc(sizeof(struct listitem));
   if(tmp == NULL) return NULL;
   memset(tmp, '\0', sizeof(struct listitem));

   if(svc_list == NULL) { /* list is empty, we have to init it */
      svc_list             = tmp;
      svc_list->next       = svc_list;
      svc_list->prev       = svc_list;
   } else {                                  /* list has members,add this one */
      tmp->next            = svc_list;       /* begin after the new element   */
      tmp->prev            = svc_list->prev; /* change to the ex-last         */
      svc_list->prev->next = tmp;            /* change last element           */
      svc_list->prev       = tmp;            /* first refers to previous now  */
   }

   cinit_cp_data(tmp->abs_path, path);

   tmp->status = status;
   tmp->pid    = 0;
   
   return tmp;
}
