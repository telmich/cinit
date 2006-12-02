/***********************************************************************
 *
 *    2006-2006 Nico Schottelius (nico-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Define signal handlers
 */


#include <signal.h>        /* sigaction      */
#include <stdio.h>         /* NULL           */
#include "cinit.h"         /* defines        */

void set_signals(int action)
{
   struct sigaction sa;

   if(action == ACT_SERV) {
      sa.sa_handler=sig_child;
   } else {
      sa.sa_handler=SIG_DFL;
   }
   sigaction(SIGCHLD,&sa,NULL);     /* what todo when a child exited    */

   if(action == ACT_SERV) {
      sa.sa_handler=do_reboot;
   }
   sigaction(SIGHUP,&sa,NULL);      /* reboot                           */
   sigaction(SIGTERM,&sa,NULL);     /* poweroff                         */
   sigaction(SIGUSR1,&sa,NULL);     /* halt                             */
}
