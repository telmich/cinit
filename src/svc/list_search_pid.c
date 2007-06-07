/***********************************************************************
 * 
 *    (c) 2005 Marcus Przyklink (downhill-clinux (at) burningchaos.org)
 *        2006 Nico Schottelius (nico-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    List handling: Search by pid
 */

#include <stdio.h>      /* NULL              */
#include <sys/types.h>  /* pid_t             */

#include "svc.h"        /* struct listitem   */

struct listitem *list_search_pid(pid_t pid)
{
   struct listitem *tmp;

   if(svc_list == NULL) {
      return NULL;
   } else {
      tmp = svc_list;
   }

   do {
      if(pid == tmp->pid) {
         return tmp;
      }
      tmp = tmp->prev;
   } while(tmp != svc_list);

   return NULL;
}
