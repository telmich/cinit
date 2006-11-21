/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Set the status of a service
 */

#include "svc.h"

void svc_success(struct listitem *li)
{
   if(li->status & ST_SH_ONCE)
      li->status = ST_ONCE_OK;
   else
      li->status = ST_RESPAWNING;
}
