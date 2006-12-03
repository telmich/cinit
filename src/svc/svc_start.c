/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Start a service
 */

#include <stdio.h>         /* NULL        */
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
         li->status = ST_ONCE_RUN;
      else
         li->status = ST_RESPAWNING;
      return;
   }
   
   /********* Client ***********/
   
   svc_report_status(li->abs_path,MSG_SVC_START,NULL);

   /* FIXME: reset signals: Is this necessary? Or does fork clean it anyway? */
   set_signals(ACT_CLIENT);

   /* length check is done by path_append */
   strcpy(buf,li->abs_path);
   if(!path_append(buf,C_ON)) return;

   execute_sth(buf);
}
