/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Communication defines
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "ipc.h"
#include "cinit.h"
#include "os.h"
#include "messages.h"

/***********************************************************************
 * sig_reboot
 * Shutdown the system 
 */

void do_reboot(int signal)
{
   //struct listitem *tmp;
   struct timespec ts;
   //char **cmd;
   //int   i;
   
   /* shutdown all services: take care about the dependency tree */

   /* do not listen to client requests anymore
    * FIXME: perhaps before shutdown? */
   cinit_ipc_destroy();

   /* now: all services are down, let's kill all other processes */
   if( kill(-1,SIGTERM) == -1) {
      print_errno(MSG_TERMKILL);
   }

   /* FIXME make SLEEP_KILL an optional configuration statement */
   ts.tv_sec   = SLEEP_KILL; /* defined in conf/sleep_kill */
   ts.tv_nsec  = 0;
   nanosleep(&ts,NULL);

   if( kill(-1,SIGKILL) == -1) {
      print_errno(MSG_KILLBILL);
   }

   /* execute umount, as defined in conf/umount */

   /* execute_sth(CINIT_UMOUNT); */

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
