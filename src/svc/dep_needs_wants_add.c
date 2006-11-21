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
#include "cinit.h"         /* FIXME: debug */

/*
 * list: pointer to the list
 * svc:  pointer to data to the service
 */

/* FIXME unfinished (wants) and possibly not adding all? */
int dep_needs_wants_add(struct dep **list, struct listitem *svc)
{

   struct dep *tmp, *new;

   /* first add needs, then add wants
    * but only add the services, if they are still a virgin
    */
   /* check status   */

   mini_printf("dep_needs_wants_add::",1);
   mini_printf(svc->abs_path,1);


   /* check needs    */
   tmp = svc->needed;
   if(tmp != NULL) {
      do {
         mini_printf(" ",1);
         if(((tmp->svc->status   & ST_SH_ONCE)     ||
            (tmp->svc->status    & ST_SH_RESPAWN)) &&
            !(tmp->svc->status   & ST_IN_LIST)) {
               mini_printf(" add: (",1);
               mini_printf(tmp->svc->abs_path,1);
               new = dep_create(tmp->svc);
               if(!new) return 0;
               dep_entry_add(list,new);
               mini_printf(") ",1);
            }
      } while(tmp != svc->needed);
   }
   mini_printf("\n",1);

   /* check wants    */

   return 1;
}
