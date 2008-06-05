
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
 *    Define signal handlers / actions for the different internal stages
 */

#include <signal.h>
#include "signals.h"
#include "reboot.h"
#include "intern.h"

void signal_init_map(struct sigaction sigstages[SIGSTAGE_END][SIGCINIT_END],
                     int cinit_signals[SIGCINIT_END])
{
   /*
    * First map signals to index 
    */
   cinit_signals[SIGCINIT_HALT] = SIGUSR1;
   cinit_signals[SIGCINIT_POWEROFF] = SIGTERM;
   cinit_signals[SIGCINIT_REBOOT] = SIGHUP;
   cinit_signals[SIGCINIT_CHILD] = SIGCHLD;

   /*
    * Then add the actions for daemon 
    */
   sigstages[SIGSTAGE_DAEMON][SIGCINIT_HALT].sa_handler = do_reboot;
   sigstages[SIGSTAGE_DAEMON][SIGCINIT_POWEROFF].sa_handler = do_reboot;
   sigstages[SIGSTAGE_DAEMON][SIGCINIT_REBOOT].sa_handler = do_reboot;

   sigstages[SIGSTAGE_DAEMON][SIGCINIT_CHILD].sa_handler = sig_child;
   sigstages[SIGSTAGE_DAEMON][SIGCINIT_CHILD].sa_flags = SA_NOCLDSTOP;

   /*
    * Then add the actions for client (=fork> 
    */
   sigstages[SIGSTAGE_CLIENT][SIGCINIT_HALT].sa_handler = SIG_DFL;
   sigstages[SIGSTAGE_CLIENT][SIGCINIT_POWEROFF].sa_handler = SIG_DFL;
   sigstages[SIGSTAGE_CLIENT][SIGCINIT_REBOOT].sa_handler = SIG_DFL;
   sigstages[SIGSTAGE_CLIENT][SIGCINIT_CHILD].sa_handler = SIG_DFL;

   /*
    * Then add the actions for shutdown 
    */
   sigstages[SIGSTAGE_REBOOT][SIGCINIT_HALT].sa_handler = SIG_IGN;
   sigstages[SIGSTAGE_REBOOT][SIGCINIT_POWEROFF].sa_handler = SIG_IGN;
   sigstages[SIGSTAGE_REBOOT][SIGCINIT_REBOOT].sa_handler = SIG_IGN;
   sigstages[SIGSTAGE_REBOOT][SIGCINIT_CHILD].sa_handler = SIG_IGN;
}
