/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Start a service
 */

#include <unistd.h>        /* fork        */
#include <string.h>        /* strerror    */
#include <errno.h>         /* errno       */
#include <limits.h>        /* PATH_MAX    */
#include "svc.h"           /* struct *    */
#include "messages.h"      /* MSG_*       */
#include "cinit.h"         /* execute_sth */

void svc_start(struct listitem *li)
{
   char              buf[PATH_MAX+1];

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

   /* Client: FIXME: check for valid length! */
   /* misuse status field (doesn't matter in fork) for strlen */
   li->status = strlen(li->abs_path);
   strncpy(buf,li->abs_path,li->status);
   strncat(buf,SLASH,PATH_MAX);
   strncat(buf,C_ON,PATH_MAX);
   execute_sth(buf);
}
