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
#include "svc-intern.h"    /* struct *          */
#include "messages.h"      /* MSG_*             */
#include "intern.h"        /* execute_sth       */
#include "cinit.h"         /* CINIT_DATA_LEN    */

extern int svc_lock;

//void svc_start(struct listitem *li, int strict)
void svc_start(struct listitem *li, int delay)
{
   char buf[CINIT_DATA_LEN];
   struct timespec ts;

   /* set global lock to avoid race condition */
   svc_lock = 1;

   /* first update status before forking ! */
   if(li->status & CINIT_ST_SH_ONCE)
      li->status = CINIT_ST_ONCE_RUN;
   else
      li->status = CINIT_ST_RESPAWNING;

   /* set start time */
   li->start = time(NULL);

   /* FIXME: All cleanup must go here
    * close(fds);
    * reset signals
    * reset env?
    *
    * FIXME: Add logging possibility to here
    * open (0,1,2) to other processes, if specified */

   /* BUG:
    *    the following child may return _before_ 
    *    the fork returns in the parent.
    *    Thus this pid may not be registered.
    *
    *    And that's the reason why we need the global svc_lock!
    */
   li->pid = fork();
   
   /**********************      parent     ************************/
   if(li->pid > 0) {
      svc_lock = 0;
      printf("%s is at %d\n", li->abs_path, li->pid);
      return;
   }

   /**********************      Error      ************************/
   if(li->pid < 0) {
      svc_report_status(li->abs_path, MSG_SVC_FORK, strerror(errno));
      svc_set_status(li, CINIT_ST_BAD_ERR);
      return;
   }
   
   /********************** Client / fork() ************************/
   /* sleep, if necesseray */
   if(delay) {
      ts.tv_sec   = delay;
      ts.tv_nsec  = 0;

      /* FIXME: also report value; int2char */
      printf("Delay: %d\n", delay);
      svc_report_status(li->abs_path, MSG_SVC_SLEEP, NULL);

      /* do not need to check for errors, because we can continue anyway */
      /* WRONG: FIXME: look whether to sleep again */
      nanosleep(&ts, NULL);
   }
   svc_report_status(li->abs_path, MSG_SVC_START, NULL);

   cinit_cp_data(buf, li->abs_path);
   if(!path_append(buf, C_ON)) return;

   /* Check for existence */
   li->status = file_exists(buf);

   if(li->status == FE_NOT) {
      /* FIXME: remove later */
      printf("********************\n");
      printf("WO/EXE: %s\n",li->abs_path);
      printf("********************\n");
      /* probably a problem: we exit too fast, cinit does not
       * yet have us in the process list. is that possible?
       * => catch with sleep */
      //sleep(2);
      _exit(0);  /* nothing there? fine! */
   }

   if(li->status == FE_FILE) {
      /* FIXME: reset signals: Is this necessary? Or does fork clean it anyway? */
      set_signals(ACT_CLIENT);

      /* and now, fire it up */
      execute_sth(buf);
   } else {
      /* FIXME: report? */
      /* either no file or an error */
      _exit(1);
   }
}
