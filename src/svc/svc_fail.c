/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Mark the service as being failed
 */

#include "svc.h"

void svc_fail(struct listitem *li)
{
   if(li->status & ST_ONCE_RUN)
      li->status = ST_ONCE_FAIL;
   else {
      /* FIXME: do something senseful, record time of dead? */
      li->status = ST_RESPAWNING;
   }
}
