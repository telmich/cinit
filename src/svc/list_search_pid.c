/***********************************************************************
 * 
 *    (c) 2005 Marcus Przyklink (downhill-clinux (at) burningchaos.org)
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    List handling
 */

#include <stdlib.h>
#include <string.h>
#include "cinit.h"
#include "svc.h"

/* find service by pid, needs to be online because it is called
 * by a signal handler
 */
inline struct listitem *list_search_pid(pid_t pid)
{
   struct listitem *tmp;

   if( svc_list == NULL ) {
      return NULL;
   } else {
      tmp = svc_list;
   }

   do {
      if( pid == tmp->pid) {
         return tmp;
      }
      tmp = tmp->prev;
   } while(tmp != svc_list);
   
   return NULL;
}
