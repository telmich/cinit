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
   if( *list == NULL ) {       /* new list          */
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
