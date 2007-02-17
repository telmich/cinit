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

//void svc_start(struct listitem *li, int strict)
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
   
   /**********************      Error      ************************/
   if(li->pid < 0) {
      svc_report_status(li->abs_path,MSG_SVC_FORK,strerror(errno));
      svc_set_status(li,ST_BAD_ERR);
      return;
   }
   /**********************      parent     ************************/
   if(li->pid > 0) {
      if(li->status & ST_SH_ONCE)
         li->status = ST_ONCE_RUN;
      else
         li->status = ST_RESPAWNING;
      return;
   }
   
   /********************** Client / fork() ************************/
   svc_report_status(li->abs_path,MSG_SVC_START,NULL);

   /* length check is done by path_append */
   strcpy(buf,li->abs_path);
   if(!path_append(buf,C_ON)) return;

   /* Check for existence */
   li->status = file_exists(buf);

   if(li->status == FE_NOT) _exit(0);  /* nothing there? fine! */

   if(li->status == FE_FILE) {
      /* FIXME: reset signals: Is this necessary? Or does fork clean it anyway? */
      set_signals(ACT_CLIENT);

      /* and now, fire it up */
      execute_sth(buf);
   } else {
      /* either no file or an error */
      _exit(1);
   }
}
