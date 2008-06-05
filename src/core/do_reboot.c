
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
 *    Reboot: includes shutdown, reboot and poweroff
 */

#include <signal.h>             /* kill() */
#include <unistd.h>             /* exit */

#include "signals.h"            /* signal handling */
#include "reboot.h"             /* cinit_poweroff&co */
#include "messages.h"           /* messages */
#include "svc-intern.h"         /* shutdown_services */
#include "intern.h"             /* many functions */
#include "ipc.h"                /* disable ipc */

void do_reboot(int signal)
{
   /*
    * do not listen to client requests anymore 
    * and tell the user what happens 
    */
   LOG(MSG_SHUTDOWN_START);
   cinit_ipc_destroy();
   set_signals(SIGSTAGE_REBOOT);

   /*
    * shutdown all services: take care about the dependency tree 
    */
   LOG(MSG_SHUTDOWN_SVC);
   shutdown_services(svc_list);

   /*
    * now: all services are down, let's kill all other processes 
    */
   LOG(MSG_SHUTDOWN_TERM);
   if(kill(-1, SIGTERM) == -1) {
      print_errno(MSG_TERMKILL);
   }

   sleep_before_kill();

   LOG(MSG_SHUTDOWN_KILL);
   if(kill(-1, SIGKILL) == -1) {
      print_errno(MSG_KILLBILL);
   }

   /*
    * Execute the last command 
    */
   LOG(MSG_SHUTDOWN_LAST);
   execute_and_wait(CINIT_LAST);

   /*
    * do what we really wanted to do 
    */
   switch (signal) {
      case SIGTERM:            /* power off */
         LOG(MSG_POWER_OFF);
         cinit_poweroff();
         break;
      case SIGHUP:             /* reboot */
         LOG(MSG_REBOOT);
         cinit_reboot();
         break;
      case SIGUSR1:            /* halt */
         LOG(MSG_HALT);
         cinit_halt();
         break;
   }
   /*
    * FIXME: should we exit? 
    */
   _exit(0);
}
