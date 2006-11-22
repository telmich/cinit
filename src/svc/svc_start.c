/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Start a service
 */

#include <unistd.h>        /* fork     */
#include "svc.h"

void svc_start(struct listitem *li)
{
   li->pid = fork();

   if(li->pid < 0) {
      /* FIXME: print descriptive error message */
      return;
   }
   if(li->pid > 0) {
      /* FIXME: Update status: Being started */
   if(li->status & ST_SH_ONCE)
      li->status = ST_ONCE_OK;
   else
      li->status = ST_RESPAWNING;
      return;
   }
   /* Client */
   if(li->pid == 0) {
      execute_sth(li->abs_path);
   }
}
