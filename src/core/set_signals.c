
/*******************************************************************************
 *
 * 2006-2008 Nico Schottelius (nico-cinit at schottelius.org)
 *
 * This file is part of cinit.

 * cinit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cinit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cinit.  If not, see <http://www.gnu.org/licenses/>.

 *
 *    Set signal handlers
 */

#include <signal.h>             /* sigaction, sigemtpyset */
#include <stdio.h>              /* NULL */

//#include "intern.h"        /* defines                 */
//#include "reboot.h"        /* reboot related          */
#include "signals.h"            /* reboot related */

void set_signals(int stage)
{
   int i;

   for(i = 0; i < SIGCINIT_END; i++) {
      sigaction(cinit_global_signals[i], &sigstages[stage][i], NULL);   /* what 
                                                                         * todo 
                                                                         * when 
                                                                         * a
                                                                         * child 
                                                                         * exited 
                                                                         */
   }

//   struct sigaction sa;
   // sigemptyset(&sa.sa_mask); /* no other signals should be blocked */
   // sa.sa_flags = 0;
//   if(action == ACT_SERV) {
//      sa.sa_handler  = sig_child;
//      sa.sa_flags    = SA_NOCLDSTOP; 
//   } else {
//      sa.sa_handler  =  SIG_DFL;
//   }

//   sigaction(SIGCHLD,&sa,NULL);     /* what todo when a child exited    */

//   sa.sa_flags = 0;                 /* reset flags */
//   if(action == ACT_SERV) {
//      sa.sa_handler = do_reboot;
//   }
//   sigaction(SIG_CINIT_HALT,     &sa, NULL);   /* halt      */
//   sigaction(SIG_CINIT_POWEROFF, &sa, NULL);   /* poweroff  */
//   sigaction(SIG_CINIT_REBOOT,   &sa, NULL);   /* reboot    */
}
