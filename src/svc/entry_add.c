/***********************************************************************
 * 
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    List handling
 */

#include <stdlib.h>
#include <string.h>
#include "cinit.h"
#include "messages.h"

/*
 * list: pointer to the list
 * new:  pointer to data to insert (already filled up)
 * size: size of an element in the list (for initialisation)
 */
int entry_add(void *list, void *new)
{
   if( list == NULL ) {       /* new list          */
      list        = new;
      list->prev  = list;
      list->next  = list;
   } else {                   /* already existing  */
      new->next         = list;           /* new-> first    */
      new->prev         = list->prev;     /* last <- new    */
      list->prev->next  = new;            /* last -> new    */
      list->prev        = new;            /* new <- first   */
   }

   return 1;
}
