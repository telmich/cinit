/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Mark the service as being failed
 */

#include "svc.h"
#include "svc-intern.h"

void svc_fail(struct listitem *li)
{
   if(li->status & CINIT_ST_ONCE_RUN)
      li->status = CINIT_ST_ONCE_FAIL;
   else {
      /* FIXME: do something senseful, record time of dead? */
      li->status = CINIT_ST_RESPAWNING;
   }
}
