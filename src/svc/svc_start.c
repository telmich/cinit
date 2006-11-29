/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Start a service
 */

#include <stdio.h>        /* DEBUG        */

#include <unistd.h>        /* fork        */
#include <string.h>        /* strerror    */
#include <errno.h>         /* errno       */
#include <limits.h>        /* PATH_MAX    */
#include "svc.h"           /* struct *    */
#include "messages.h"      /* MSG_*       */
#include "cinit.h"         /* execute_sth */

void svc_start(struct listitem *li)
{
   char buf[PATH_MAX+1];

   /* FIXME: All cleanup must go here
    * close(fds);
    * reset signals
    * reset env?
    *
    * FIXME: Add logging possibility to here
    * open (0,1,2) to other processes, if specified */
   li->pid = fork();

   if(li->pid < 0) {
      svc_report_status(li->abs_path,MSG_SVC_FORK,strerror(errno));
      svc_set_status(li,ST_BAD_ERR);
      return;
   }
   if(li->pid > 0) {
      if(li->status & ST_SH_ONCE)
         li->status = ST_ONCE_OK;
      else
         li->status = ST_RESPAWNING;
      return;
   }

   /* FIXME: check for valid length!
    * strlen(abs_path) + strlen(SLASH) + strlen(C_ON) */
   /* misuse status field (doesn't matter in fork) for strlen */
   li->status = strlen(li->abs_path);
   strncpy(buf,li->abs_path,li->status);
   buf[li->status] = '\0';
   strncat(buf,SLASH,PATH_MAX);
   strncat(buf,C_ON,PATH_MAX);

   execute_sth(buf);
}
