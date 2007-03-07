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

#include "cinit.h"      /*                   */
#include "svc.h"        /* list_search_pid   */
#include "messages.h"   /* messages          */

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
   struct listitem   *svc;

   while((pid = waitpid(-1, &tmp, WNOHANG)) > 0) {
      /* check if it's a watched child */
      svc = list_search_pid((pid_t) pid);

      if(svc != NULL) {
         /* Check, that we are operating on it =. that it is no normal child */
         if(svc->status & ST_ONCE_RUN
         || svc->status & ST_SH_RESPAWN
         || svc->status & ST_RESPAWNING) {
            if(WIFEXITED(tmp) && !WEXITSTATUS(tmp)) {
               svc_success(svc);
            } else {
               svc_fail(svc);
            }
         }

         /* respawn: restart: FIXME Delay for regular dying services */
         if(svc->status == ST_RESPAWNING) {
            svc_report_status(svc->abs_path,MSG_SVC_RESTART,NULL);
            svc_start(svc);
         }
      } else {
         /* FIXME remove in production version */
         mini_printf("Cleanup: reparenting\n",1);
      }
   }
}
