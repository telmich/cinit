/***********************************************************************
 * 
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    List handling: Add a new item to a (non-)empty list
 */

#include <stdio.h>         /* NULL     */
#include "svc.h"

/*
 * tmp:  pointer to data to remove (must not be NULL)
 *    -> perhaps work on the pointer to the pointer?
 *
 * Returns either the next object or NULL if there's no next object
 */
struct dep *dep_entry_del(struct dep **tmp)
{  
   /* last service in the list */
   if((*tmp)->next == (*tmp) && (*tmp)->prev == (*tmp)) {
      free(tmp);
      return NULL;
   } else {
      /* remove from list */
      tmp->prev->next = tmp->next;
      tmp->next->prev = tmp->prev;
   }

   /* remove from memory */
   free(tmp);

   return 1;
}
