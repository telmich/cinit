/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Set the status of a service
 */

#include "svc.h"

void svc_success(struct listitem *li)
{
   if(li->status & ST_ONCE_RUN)
      li->status = ST_ONCE_OK;
   else
      li->status = ST_RESPAWNING;
}
