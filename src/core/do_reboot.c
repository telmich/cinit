/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit //@\\ schottelius.org)
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
#include "cinit.h"
#include "os.h"
#include "messages.h"

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
   
   /* FIXME: pre-shutdown? not senseful, can be implemented outside. */

   /* do not listen to client requests anymore */
   cinit_ipc_destroy();

   /* FIXME: ignore signals now! */

   /* shutdown all services: take care about the dependency tree */
   //cinit_svc_shutdown();

   /* now: all services are down, let's kill all other processes */
   if(kill(-1,SIGTERM) == -1) {
      print_errno(MSG_TERMKILL);
   }

   sleep_before_kill();

   if(kill(-1,SIGKILL) == -1) {
      print_errno(MSG_KILLBILL);
   }

   /* Execute umount and wait for its termination */
   execute_and_wait(CINIT_UMOUNT);

   /* do what we really wanted to do */
   switch(signal) {
      case SIGTERM: /* power off */
         LOG(MSG_POWER_OFF);
         cinit_poweroff();
         break;
      case SIGHUP: /* reboot */
         LOG(MSG_REBOOT);
         cinit_reboot();
         break;
      case SIGUSR1: /* halt */
         LOG(MSG_HALT);
         cinit_halt();
         break;
   }
}
