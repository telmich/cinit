/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Communication defines
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "ipc.h"

/* cleaned up own headers */
#include "cinit.h"               /* set_signals       */
#include "svc.h"                 /* shutdown_services */
#include "messages.h"            /* messages          */
#include "reboot.h"              /* cinit_poweroff&co */

/* cleaned headers */
#include <signal.h>              /* kill()            */

/***********************************************************************
 * sig_reboot
 * Shutdown the system 
 */

void do_reboot(int signal)
{
   //struct listitem *tmp;
   //char **cmd;
   //int   i;
   
   /*
    * New code:
    * 0. close user ipc
    *    - notify user!
    *    - do not allow user interupt anymore
    * 1. shutdown services
    *    - notify user!
    * 2. kill -TERM all processes
    *    - notify user!
    * 3. kill -KILL all processes
    *    - notify user!
    * 4. execute /etc/cinit/conf/{halt,reboot,poweroff}
    *    - notify user!
    */

   /* do not listen to client requests anymore */
   /* and tell the user what happens */
   LOG(MSG_SHUTDOWN_START);
   cinit_ipc_destroy();
   set_signals(ACT_CLIENT);               /* reset signal handlers */

   /* shutdown all services: take care about the dependency tree */
   LOG(MSG_SHUTDOWN_SVC);
   shutdown_services(svc_list);

   LOG(MSG_SHUTDOWN_KILL);
   /* now: all services are down, let's kill all other processes */
   if(kill(-1,SIGTERM) == -1) {
      print_errno(MSG_TERMKILL);
   }

   sleep_before_kill();

   if(kill(-1,SIGKILL) == -1) {
      print_errno(MSG_KILLBILL);
   }

   /* Execute the last command         */
   LOG(MSG_SHUTDOWN_LAST);
   execute_and_wait(CINIT_LAST);

   /* do what we really wanted to do   */
   switch(signal) {
      case SIGTERM:  /* power off      */
         LOG(MSG_POWER_OFF);
         cinit_poweroff();
         break;
      case SIGHUP:   /* reboot         */
         LOG(MSG_REBOOT);
         cinit_reboot();
         break;
      case SIGUSR1:  /* halt           */
         LOG(MSG_HALT);
         cinit_halt();
         break;
   }
   /* FIXME: should we exit? */
   _exit(0);
}
