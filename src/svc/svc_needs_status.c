/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Return status of the needs of this service
 */

#include <stdio.h>      /* NULL                    */
#include "svc.h"        /* service information     */

int svc_needs_status(struct listitem *svc)
{
   struct dep *deps;

   deps = svc->needs;

   if(deps == NULL) return SNS_NEED_STARTED;    /* no needs, everything fine */

   do {
      deps = deps->next;
   } while(deps != svc->needs);
}
