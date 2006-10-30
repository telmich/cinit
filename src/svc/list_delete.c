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

/* ... */
int list_delete(char *path)
{
   struct listitem *tmp;

   tmp = list_search(path);

   if( tmp == NULL ) {
      return 0;
   }

   tmp->after->before = tmp->before;
   tmp->before->after = tmp->after;
   free(tmp->abs_path);
   free(tmp);
   return 1;
}
