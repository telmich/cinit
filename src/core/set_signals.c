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

void     sig_child(int signal) { signal=2; } /* HACK */

void set_signals(int action)
{
   struct sigaction sa;

   if(action == ACT_SERV) {
      sa.sa_handler=sig_child;
   } 
   sigaction(SIGCHLD,&sa,NULL);     /* what todo when a child exited    */

   if(action == ACT_SERV) {
      sa.sa_handler=do_reboot;
   }
   sigaction(SIGHUP,&sa,NULL);      /* reboot                           */
   sigaction(SIGTERM,&sa,NULL);     /* poweroff                         */
   sigaction(SIGUSR1,&sa,NULL);     /* halt                             */
}
