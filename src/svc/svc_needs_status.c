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
#include "svc-intern.h" /* service information     */

int svc_needs_status(struct listitem *svc)
{
   int         retval   = CINIT_SNS_NEEDS_STARTED;
   struct dep  *deps    = svc->needs;

   if(deps == NULL) return CINIT_SNS_NEEDS_STARTED;    /* no needs, everything fine */

   do {
      /* worst case: need failed */
      if((deps->svc->status & CINIT_ST_NEED_FAILD) ||
         (deps->svc->status & CINIT_ST_ONCE_FAIL)  ||
         (deps->svc->status & CINIT_ST_BAD_ERR)    ){
            retval = CINIT_SNS_NEEDS_FAILED;
            break;
      }
      /* services are being started */
      if((deps->svc->status & CINIT_ST_SH_ONCE)    ||
         (deps->svc->status & CINIT_ST_SH_RESPAWN) ||
         (deps->svc->status & CINIT_ST_ONCE_RUN)   ){
  //          printf("%s (%ld) waits for %s (%ld)\n",svc->abs_path, svc->status, deps->svc->abs_path, deps->svc->status);
            retval = CINIT_SNS_NEEDS_UNFINISHED;
      }
      deps = deps->next;
   } while(deps != svc->needs);
   
   return retval;
}
