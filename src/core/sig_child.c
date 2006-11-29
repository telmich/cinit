/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    The child handler
 *
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#include <signal.h>     /* sigaction */
#include "cinit.h"
#include "svc.h"        /* list_search_pid   */

/***********************************************************************
 * sig_child
 * collect the children
 * FIXME: check whether we've race conditions when reciieving multiiple
 * signals
 * Perhaps disable listening to sig_child in meantime?
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
   struct listitem *svc;
   struct sigaction sa;

   /* do not interrupt us or anything we might call */
   sa.sa_handler = SIG_IGN;
   sigaction(SIGCHLD,&sa,NULL);

   while((tmp = waitpid(-1, &tmp, WNOHANG)) > 0) {
      /* check if it's a watched child */
      
      /* restart service, if we are watching it */
      svc = list_search_pid((pid_t) tmp);

      mini_printf("SC::",1);
      if(svc != NULL) {
         mini_printf(svc->abs_path,1);
         if(WIFEXITED(tmp) && !WEXITSTATUS(tmp)) {
            mini_printf("::JUHU::",1);
            /* process successfully terminated */
            svc_success(svc);
            if(svc->status == ST_RESPAWNING) {
               /* respawn: restart */
               svc_start(svc);
            } else { /* FIXME: SET PID = 0, so it's not found later again
            }
         } else {
            mini_printf("::FAILED::",1);
            //svc_report_status(svc->abs_path,"FAILED",NULL);
            /* FAILED */
            svc_fail(svc);
            if(svc->status == ST_RESPAWNING) {
               mini_printf("::RESPAWN::",1);
               /* respawn: restart */
               svc_start(svc);
            }
         }
      } else {
         mini_printf("Cleanup: reparenting",1);
      }
      mini_printf("\n",1);
   }

   sa.sa_handler = sig_child;
   sigaction(SIGCHLD,&sa,NULL);
}
