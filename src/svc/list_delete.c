/***********************************************************************
 * 
 *    (c) 2005 Marcus Przyklink (downhill-clinux (at) burningchaos.org)
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    List handling
 */

#include <stdlib.h>     /* free        */
#include "intern.h"     /* list_search */
#include "svc.h"        /* listitem    */

/* ... */
int list_delete(char *path)
{
   struct listitem *tmp;

   tmp = list_search(path);

   if(tmp == NULL) {
      return 0;
   }

   tmp->next->prev = tmp->prev;
   tmp->prev->next = tmp->next;

   free(tmp->abs_path);
   free(tmp);

   return 1;
}
