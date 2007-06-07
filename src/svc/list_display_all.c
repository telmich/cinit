/***********************************************************************
 * 
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    Show all list elements - mainly for debugging
 */

#include <stdio.h>         /* NULL     */

#include "messages.h"      /* D_PRINTF */
#include "svc.h"

int list_display_all()
{
   struct listitem *tmp;

   if(svc_list == NULL) {
      return 0;
   } else {
      tmp = svc_list;
   }

   do {
      D_PRINTF("Service: ");
      D_PRINTF(tmp->abs_path);
      D_PRINTF("\n");

      tmp = tmp->prev;
   } while(tmp != svc_list);
   
   return 1;
}
