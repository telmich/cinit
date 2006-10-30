/***********************************************************************
 * 
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    Show all list elements - mainly for debugging
 */

#include <stdio.h>         /* NULL     */
#include "cinit.h"
#include "svc.h"

int list_display_all()
{
   struct listitem *tmp;

   if( list == NULL ) {
      return 0;
   } else {
      tmp = list;
   }

   do {
      mini_printf("Service: ",1);
      mini_printf(tmp->abs_path,1);
      mini_printf("\n",1);
      tmp = tmp->before;
   } while(tmp != list);
   
   return 1;
}
