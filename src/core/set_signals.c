/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Define signal handlers
 */


#include <signal.h>        /* sigaction, sigemtpyset  */
#include <stdio.h>         /* NULL                    */
#include "cinit.h"         /* defines                 */

void set_signals(int action)
{
   struct sigaction sa;
   
   sigemptyset(&sa.sa_mask);        /* no other signals should be blocked */
   sa.sa_flags = 0;

   if(action == ACT_SERV) {
      sa.sa_handler  = sig_child;
      sa.sa_flags    = SA_NOCLDSTOP; 
   } else {
      sa.sa_handler  =  SIG_DFL;
   }

   sigaction(SIGCHLD,&sa,NULL);     /* what todo when a child exited    */

   sa.sa_flags = 0;                 /* reset flags */
   if(action == ACT_SERV) {
      sa.sa_handler = do_reboot;
   }
   sigaction(SIGHUP,  &sa, NULL);   /* reboot    */
   sigaction(SIGTERM, &sa, NULL);   /* poweroff  */
   sigaction(SIGUSR1, &sa, NULL);   /* halt      */
}
