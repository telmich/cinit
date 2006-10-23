/***********************************************************************
 * 
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    Show all list elements - mainly for debugging
 */

#include "cinit.h"

/* search for an entry by path, reverse: from end to the beginning */
int list_display_all()
{
   struct listitem *tmp;

   if( list == NULL ) {
      return 0;
   } else {
      tmp = list;
   }

   do {
      mini_pprintf(tmp->abs_path,1);
      tmp = tmp->before;
   } while(tmp != list);
   
   return 1;
}
