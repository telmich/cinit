/***********************************************************************
 *
 *    2006-2006 Nico Schottelius (nico-linux-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Define signal handlers
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
   sigaction(SIGINT,&sa,NULL);      /* ignore ctr+c == ctr+alt+del      */
   sigaction(SIGPIPE,&sa,NULL);     /* what todo when pipe/fifo closed  */
   sigaction(SIGTTIN,&sa,NULL);     /* just ignore                      */
   sigaction(SIGTTOU,&sa,NULL);     /* just ignore                      */
   sigaction(SIGSTOP,&sa,NULL);     /* just ignore                      */
   sigaction(SIGQUIT,&sa,NULL);     /* just ignore                      */

   /* cleaning dead processes - only process 1 */
   if(action == ACT_SERV) {
      sa.sa_handler=sig_child;
   } 
   sigaction(SIGCHLD,&sa,NULL);     /* what todo when a child exited    */

   /* signal handlers to do special things with: reboot */
   if(action == ACT_SERV) {
      sa.sa_handler=do_reboot;
   }
   sigaction(SIGHUP,&sa,NULL);      /* reboot */
   sigaction(SIGTERM,&sa,NULL);     /* poweroff */
   sigaction(SIGUSR1,&sa,NULL);     /* halt */
}
