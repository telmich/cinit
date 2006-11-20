/***********************************************************************
 * 
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    Add all wants and needs from a specific service to dep list
 */

#include <stdio.h>         /* NULL     */
#include "svc.h"

/*
 * list: pointer to the list
 * svc:  pointer to data to the service
 */
int dep_needs_wants_add(struct dep **list, struct listitem *svc)
{

   struct dep *tmp;

   /* first add needs, then add wants
    * but only add the service, if it's still a virgin
    */
   tmp = svc->needed;
   if(tmp != NULL) {
      do {
         if((tmp->svc->status & ST_SH_ONCE) ||
            (tmp->svc->status & ST_SH_RESPAWN))
               /* FIXME: add entry */
      } while(tmp != svc->needed);
   }
   
   dep_entry_add(
   f( *list == NULL ) {       /* new list          */
      *list          = new;
      (*list)->prev  = *list;
      (*list)->next  = *list;
   } else {                                     /* already existing  */
      new->next            = *list;             /* new-> first       */
      new->prev            = (*list)->prev;     /* last <- new       */
      (*list)->prev->next  = new;               /* last -> new       */
      (*list)->prev        = new;               /* new <- first      */
   }

   return 1;
}
