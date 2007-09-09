/***********************************************************************
 *
 *    2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    The child handler
 *
 */

#include <sys/wait.h>   /* waitpid           */
#include <stdio.h>      /* NULL              */
#include <sys/time.h>   /* gettimeofday()    */ /* FIXME: CHECK POSIX */
#include <time.h>       /* time(),gettime..  */ /* FIXME: CHECK POSIX */

#include "intern.h"     /* mini_printf       */
#include "svc.h"        /* list_search_pid   */
#include "messages.h"   /* messages/D_PRINTF */

/***********************************************************************
 * sig_child: (c)collect the children
 */
void sig_child(int tmp)
{
   /* New code:
    * - search for pid in service list
    *   * if (respawn) -> start new
    *    - insert delay? if exit code is non-zero? if uptime too less?
    *   * if (once) -> update service status
    *   * else ignore, but reap away
    */
   pid_t             pid;
   int               delay;
   struct listitem   *svc;
//   struct timeval    now;

   while((pid = waitpid(-1, &tmp, WNOHANG)) > 0) {
      /* check if it's a watched child */
      svc = list_search_pid((pid_t) pid);

      if(svc != NULL) {
         /* Check, that we are operating on it =. that it is no normal child */
         if(svc->status & ST_ONCE_RUN
         || svc->status & ST_RESPAWNING) {
            printf("CHILD: %s bekannt!\n",svc->abs_path);
            if(WIFEXITED(tmp) && !WEXITSTATUS(tmp)) {
               svc_success(svc);
            } else {
               svc_fail(svc);
            }
         }
         // may not happen, svc_start sets it to ST_RESPAWNING!
         //|| svc->status & ST_SH_RESPAWN

         //mini_printf("WHILE: Vorm respawn!\n",1);
         /* respawn: restart: FIXME Delay for regular dying services */
         if(svc->status == ST_RESPAWNING) {
            svc_report_status(svc->abs_path,MSG_SVC_RESTART,NULL);

            //delay = MAX_DELAY / (time(NULL) - svc->start);
            /* if(gettimeofday(&now,NULL) == -1) {
               print_errno(MSG_GETTIMEOFDAY);;
               delay = 0;
            } else {
               delay = MAX_DELAY / (now.tv_sec - svc->start);
            } */

            delay = 5;

            /* int test = time(NULL);
            test++;
            D_PRINTF("WHILE: IM respawn / for printf!\n");
            printf("sig_child: %d, %d, %d, %d\n",
                  MAX_DELAY,
                  (int) time(NULL),
                  (int) svc->start,
                  (int) (test - svc->start)
                  ); */

            svc_start(svc,delay);
         }
      }
   }
}
