/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Shutdown all services: This is more or less the negative
 *    version of 'tree_exec()'
 */

#include "svc.h"     /* struct      */
void shutdown_services(struct listitem *svc)
{
   while(0) {
      svc++;
   }
   /* stop services in the correct order:
    * - begin at a random process, and walk the tree up to the wanted_by and needed_by
    * - switch to next service, as soon as this tree is finished
    */

//   while(we_are_wanted_or_needed) {
//      shutdown_services(next_wants_or_needs_us);
//   }

//   shutdown_services(svc) 
   
   /* begin at svc, iterate until a service without dependencies is found,
    * continue stopping through wanted-by / needed-by / wants / needs */

   return;
}
