/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Start a service
 */

#include <stdio.h>         /* NULL              */
#include <unistd.h>        /* fork              */
#include <string.h>        /* strerror          */
#include <errno.h>         /* errno             */
#include <limits.h>        /* PATH_MAX          */
#include <time.h>          /* nanosleep()       */
//#include <sys/time.h>      /* gettimeofday()    */

#include "svc.h"           /* struct *          */
#include "messages.h"      /* MSG_*             */
#include "intern.h"        /* execute_sth       */

//void svc_start(struct listitem *li, int strict)
void svc_start(struct listitem *li, int delay)
{
   char buf[PATH_MAX+1];
   struct timespec ts;

   /* FIXME: All cleanup must go here
    * close(fds);
    * reset signals
    * reset env?
    *
    * FIXME: Add logging possibility to here
    * open (0,1,2) to other processes, if specified */
   D_PRINTF("VORM Fork()\n");
   li->pid = fork();
   
   /**********************      Error      ************************/
   if(li->pid < 0) {
      svc_report_status(li->abs_path,MSG_SVC_FORK,strerror(errno));
      svc_set_status(li,ST_BAD_ERR);
      return;
   }
   /**********************      parent     ************************/
   if(li->pid > 0) {
      D_PRINTF("ELTERN\n");
      /* set start time */
      li->start = time(NULL);

      if(li->status & ST_SH_ONCE)
         li->status = ST_ONCE_RUN;
      else
         li->status = ST_RESPAWNING;
      return;
   }
   
   /********************** Client / fork() ************************/
   /* sleep, if necesseray */
   printf("Delay: %d\n", delay);
   if(delay) {
      ts.tv_sec   = delay;
      ts.tv_nsec  = 0;

      /* FIXME: also report value; int2char */
      svc_report_status(li->abs_path,MSG_SVC_SLEEP,NULL);

      /* do not need to check for errors, because we can continue anyway */
      nanosleep(&ts,NULL);
   }
   svc_report_status(li->abs_path,MSG_SVC_START,NULL);

   /* length check is done by path_append */
   strcpy(buf,li->abs_path);
   if(!path_append(buf,C_ON)) return;

   /* Check for existence */
   li->status = file_exists(buf);

   if(li->status == FE_NOT) {
      _exit(0);  /* nothing there? fine! */
   }

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
