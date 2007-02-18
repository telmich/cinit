/***********************************************************************
 * 
 *    (c) 2005 Marcus Przyklink (downhill-clinux (at) burningchaos.org)
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    List handling
 */

#include <stdlib.h>        /* malloc               */
#include <string.h>        /* bzero / memset       */
#include "svc.h"           /* the list pointer     */

struct listitem *list_insert(char *path, int status)
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

   tmp->abs_path = malloc(strlen(path) + 1);
   if(tmp->abs_path == NULL) return NULL;

   strcpy(tmp->abs_path,path);
   tmp->status = status;
   tmp->pid    = 0;
   
   return tmp;
}
