/***********************************************************************
 *
 *    2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Return status of the needs of this service
 */

#include <stdio.h>      /* NULL                    */
#include "svc.h"        /* service information     */

int svc_needs_status(struct listitem *svc)
{
   int         retval   = SNS_NEEDS_STARTED;
   struct dep  *deps    = svc->needs;

   if(deps == NULL) return SNS_NEEDS_STARTED;    /* no needs, everything fine */

   do {
      /* worst case: need failed */
      if((deps->svc->status & ST_NEED_FAILD) ||
         (deps->svc->status & ST_ONCE_FAIL)  ||
         (deps->svc->status & ST_BAD_ERR)    ){
            retval = SNS_NEEDS_FAILED;
            break;
      }
      /* services are being started */
      if((deps->svc->status & ST_SH_ONCE)    ||
         (deps->svc->status & ST_SH_RESPAWN) ||
         (deps->svc->status & ST_ONCE_RUN)   ){
            retval = SNS_NEEDS_UNFINISHED;
      }
      deps = deps->next;
   } while(deps != svc->needs);
   
   return retval;
}
