/***********************************************************************
 * 
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    List handling: Add a new item to a (non-)empty list
 */

#include <stdio.h>         /* NULL     */
#include <stdlib.h>        /* free()   */
#include "svc.h"

/*
 * tmp:  pointer to data to remove (must not be NULL)
 *
 * Returns either the next object or NULL if there's no next object
 */
struct dep *dep_entry_del(struct dep *del)
{  
   struct dep *tmp;

   /* last service in the list */
   if(del->next == del && del->prev == del) {
      tmp=NULL;
   } else {
      /* remove from list */
      del->prev->next = del->next;
      del->next->prev = del->prev;
      tmp = del->next;
   }

   free(del);

   return tmp;
}
