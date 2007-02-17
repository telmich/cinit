/***********************************************************************
 *
 *    2006-2006 Nico Schottelius (nico-cinit //@\\ schottelius.org)
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

   /* If you want to have fun with glibc, comment out the three lines that
    * initialise sa.sa_flags and cinit will segfault when sig_child
    * exits. "Works" on glibc 2.3-2.5 ;-)
    */
   if(action == ACT_SERV) {
      sa.sa_handler  = sig_child;
      sa.sa_flags    = SA_NOCLDSTOP; 
   } else {
      sa.sa_handler  =  SIG_DFL;
      sa.sa_flags    =  0;
   }
   sigemptyset(&sa.sa_mask);

   sigaction(SIGCHLD,&sa,NULL);     /* what todo when a child exited    */

   sa.sa_flags = 0;                 /* reset flags */
   if(action == ACT_SERV) {
      sa.sa_handler = do_reboot;
   }
   sigaction(SIGHUP,  &sa, NULL);   /* reboot    */
   sigaction(SIGTERM, &sa, NULL);   /* poweroff  */
   sigaction(SIGUSR1, &sa, NULL);   /* halt      */
}
