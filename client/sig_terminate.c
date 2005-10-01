/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * terminate: terminate our watching pid
 * part of cinit
 */

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <errno.h>
#include "cinit.h"

/* ********************************************************************** 
 * terminate the watching service
 */
void sig_terminate(int signal)
{
   struct timespec ts;
   int status;
   
   /* FIXME: only send SIGTERM, if not_kill does not exist */
   if( kill(cpid,SIGTERM) == -1) {
      if(errno != ESRCH) {
         perror(MSG_TERMKILL);
      }
   }

   /* variabel delay */
   if(sock > 0) {
      ts.tv_sec = sock;
   } else {
      ts.tv_sec = SLEEP_KILL_SVC; /* defined in conf/sleep_kill_svc */
   }

   /* if it still exists...  */
   if(kill(cpid,0) != -1) {
      /* kill if there is a delay */
      if(sock != 0) {
         nanosleep(&ts,NULL);
         status = kill(cpid,SIGKILL);
         if( status == -1) {
            if(errno != ESRCH) {
               perror(MSG_TERMKILL);
            }
         }
      }
   }
   
   /* remove zombie if killed, if delay is zero wait for it */
   waitpid(cpid,&status,0);

   /* reset the watching pid to zero (NOT THE WATCHER's!) */
   cpid = 0;
   
   D_PRINTF("muesste weg sein");
   return;
}
