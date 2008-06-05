
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
 *    OBSOLETED!
 * 
 *    List handling
 */

#error "NOT IN USE"

#include "cinit.h"
#include "messages.h"

int svc_add_needs(char *needs, char *is_needed)
{
   struct listitem *svc_needs, *svc_is_needed;

   /*
    * retrieve service entries in global service list 
    */
   svc_needs = svc_is_needed = NULL;
   svc_needs = list_search(needs);
   svc_is_needed = list_search(is_needed);

   /*
    * and exit if one is missing 
    */
   if(!svc_needs || !svc_is_needed) {
      return 0;
   }

   /*
    * first add needs 
    */

   /*
    * now add needed_by 
    */

   malloc...                    /* for adding */
      if(svc->needs == NULL) {
      svc->needs = neu;
   } else {
      svc->next = neu;
   }

   /*
    * write generic function for dependencies or even all lists 
    */
   dep_entry_add(list_pointer, new_entry);

   if(list == NULL) {           /* list is empty, we have to init it */
      list = tmp;
      list->after = list;
      list->before = list;
   } else {                     /* list has members,add this one */
      tmp->after = list;        /* begin after the new element */
      tmp->before = list->before;       /* change to the ex-last */
      list->before->after = tmp;        /* change last element */
      list->before = tmp;       /* first refers to previous now */
   }

   tmp->abs_path = malloc(strlen(path) + 1);
   if(tmp->abs_path == NULL) {
      LOG(MSG_ERR_ALLOC);
      return 0;
   }

   strcpy(tmp->abs_path, path);
   tmp->status = status;
   tmp->pid = 0;

   return 1;
}
