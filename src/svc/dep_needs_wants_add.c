/***********************************************************************
 * 
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    Add all wants and needs from a specific service to dep list
 */

#include <stdio.h>         /* NULL     */
#include "svc.h"

/*
 * list: pointer to the list
 * svc:  pointer to data to the service
 */
int dep_needs_wants_add(struct dep **list, struct listitem *svc)
{

   struct dep *tmp, *new;

   /* first add needs, then add wants
    * but only add the services, if they are still a virgin
    */
   /* check status   */


   /* check needs    */
   tmp = svc->needed;
   if(tmp != NULL) {
      do {
         if(((tmp->svc->status   & ST_SH_ONCE)     ||
            (tmp->svc->status    & ST_SH_RESPAWN)) &&
            !(tmp->svc->status   & ST_IN_LIST)) {
               new = dep_create(tmp->svc);
               if(!new) return 0;
               dep_entry_add(list,new);
            }
      } while(tmp != svc->needed);
   }

   /* check wants    */

   return 1;
}
