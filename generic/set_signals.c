/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * cinit.c
 * part of cLinux/cinit
 */

#include <signal.h>
#include <stdio.h>
#include "cinit.h"

void set_signals(int action)
{
   struct sigaction sa;

   if(action == ACT_SERV) {
      sa.sa_handler=SIG_IGN;
   } else {
      sa.sa_handler=SIG_DFL;
   }
   sigaction(SIGINT,&sa,NULL);      /* ignore ctr+c and ctr+alt+del     */
   sigaction(SIGPIPE,&sa,NULL);     /* what todo when pipe/fifo closed  */
   sigaction(SIGTTIN,&sa,NULL);
   sigaction(SIGTTOU,&sa,NULL);
   sigaction(SIGSTOP,&sa,NULL);

   sigaction(SIGQUIT,&sa,NULL);     /* warm reboot??? */

   /* cleaning dead processes */
//   if(action == ACT_SERV) {
      sa.sa_handler=sig_child;
//   } 
   /* server and client need sig_chld */
   sigaction(SIGCHLD,&sa,NULL);     /* what todo when a child exited    */

   /* sigio is called to act on the socket */
/*   if(action == ACT_SERV) {
      sa.sa_handler=sigio;
   }
   sigaction(SIGIO,&sa,NULL); This should not be needed anymore */

   /* signal handlers to do special things with: reboot */
   if(action == ACT_SERV) {
      sa.sa_handler=sig_reboot;
   }
   sigaction(SIGUSR1,&sa,NULL);     /* halt */
   sigaction(SIGUSR2,&sa,NULL);     /* Rescue */
   sigaction(SIGTERM,&sa,NULL);     /* poweroff */
   sigaction(SIGHUP,&sa,NULL);      /* reboot */
   sigaction(SIGCONT,&sa,NULL);     /* update */

}
