/***********************************************************************
 * 
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    Add all wants or needs from a specific service to dep list
 *       -> this builds the needs and needed_by and
 *       -> or this builds the wants and wanted_by and
 *
 *    This function is used to fillup the starting list with dependencies
 *    after a service has sucessfully been executed.
 */

#include <stdio.h>         /* NULL        */
#include "svc-intern.h"    /* struct *dep */
#include "svc.h"          /* struct *dep */

/*
 * list: pointer to the list
 * svc:  pointer to data to the service
 */

int dep_needs_wants_add(struct dep **list, struct listitem *svc, int type)
{
   struct dep *tmp, *new, *end;

   if(type == DEP_NEEDS) {
      end = svc->needed;
   } else {
      end = svc->wanted;
   }

   /* Place to the first dependency of this service */
   tmp = end;
   if(tmp != NULL) {
      do {
         /* Add service to the starter list, which
          *    - should be started once
          *    - should be respawned (both VIRGIN services!)
          *    - and which are not already in the list!
          */
         if(((tmp->svc->status   & CINIT_ST_SH_ONCE)     ||
            (tmp->svc->status    & CINIT_ST_SH_RESPAWN)) &&
            !(tmp->svc->status   & CINIT_ST_IN_LIST)) {
               new = dep_create(tmp->svc);
               if(!new) return 0;
               tmp->svc->status |= CINIT_ST_IN_LIST;
               dep_entry_add(list,new);
            }
         /* FIXME: Clearify if we should go forward or backwards?
          * this decision will influence starting order
          * and may thereby add a minimal mount of speed enhancement
          *
          * As far as I can see it is not predictable, which way is
          * better, because it heavily depends on the other services.
          *
          * If you know better, provide me with a patch ;-)
          */
         tmp = tmp->next;
      } while(tmp != end);
   }

   return 1;
}
