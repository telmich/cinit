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
 * new:  pointer to insert
 * size: size of an element in the list (for initialisation)
 */
int entry_add(void *list, void *new, size_t size)
{
   struct listitem *tmp;

   tmp = malloc( sizeof(struct listitem) );

   if( list == NULL ) {
      return 0;
   }

   if( tmp == NULL ) {
      return 0;
   }

   if( list == NULL ) { /* list is empty, we have to init it */
      list = tmp;
      list->after    = list;
      list->before   = list;
   } else {                                  /* list has members,add this one */
      tmp->after           = list;           /* begin after the new element   */
      tmp->before          = list->before;   /* change to the ex-last         */
      list->before->after  = tmp;            /* change last element           */
      list->before         = tmp;            /* first refers to previous now  */
   }

   tmp->abs_path = malloc( strlen(path) + 1);
   if( tmp->abs_path == NULL ) {
      LOG(MSG_ERR_ALLOC);
      return 0;
   }

   strcpy(tmp->abs_path,path);
   tmp->status = status;
   tmp->pid    = 0;
   
   return 1;
}
