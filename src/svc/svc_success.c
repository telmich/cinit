/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Set the status of a service
 */

#include <stdio.h>      /* NULL */

#include "svc.h"        /* listitem, svc_report_status */
#include "svc-intern.h" /* listitem, svc_report_status */
#include "messages.h"   /* messages */

void svc_success(struct listitem *li)
{
   if(li->status & CINIT_ST_ONCE_RUN) {
      svc_report_status(li->abs_path,MSG_SVC_OK_ONCE,NULL);
      li->status = CINIT_ST_ONCE_OK;
   } else {
      svc_report_status(li->abs_path,MSG_SVC_OK_RESPAWN,NULL);
      li->status = CINIT_ST_RESPAWNING;
   }
}
