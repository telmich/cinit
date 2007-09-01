/***********************************************************************
 * 
 *    2005 Marcus Przyklink      (downhill-clinux (at) burningchaos.org)
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    List handling
 */

#include <stdio.h>         /* NULL              */
#include <string.h>        /* strcmp            */
#include "svc.h"           /* struct listitem   */

/* search for an entry by path, reverse: from end to the beginning */
struct listitem *list_search(char *path)
{
   struct listitem *tmp;

   if(svc_list == NULL) { /* think positive */
      return NULL;
   } else {
      tmp = svc_list;
   }

   do {
      if(!strcmp(path, tmp->abs_path)) {
         return tmp;
      }
      tmp = tmp->prev;
   } while(tmp != svc_list);
   
   return NULL;
}
