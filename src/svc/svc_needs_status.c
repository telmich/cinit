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

// DEBUG #include "cinit.h"        /* service information     */

int svc_needs_status(struct listitem *svc)
{
   int         retval   = SNS_NEEDS_STARTED;
   struct dep  *deps    = svc->needs;

/* DEBUG   mini_printf("sns: ",1);
   mini_printf(svc->abs_path,1);
   mini_printf("\n",1); */

   if(deps == NULL) return SNS_NEEDS_STARTED;    /* no needs, everything fine */

   do {
      /* worst case: need failed */
      if((deps->svc->status & ST_NEED_FAILD) ||
         (deps->svc->status & ST_ONCE_FAIL)) {
            retval = SNS_NEEDS_FAILED;
            break;
      }
      /* services are being started */
      if((deps->svc->status & ST_SH_ONCE) ||
         (deps->svc->status & ST_SH_RESPAWN)) {
            retval = SNS_NEEDS_UNFINISHED;
      }
      deps = deps->next;
   } while(deps != svc->needs);
   
   return retval;
}
