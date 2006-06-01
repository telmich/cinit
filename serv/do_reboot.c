/* 
 * cinit
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * We are called by signal to reboot
 */

#include <sys/mount.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reboot.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "cinit.h"

/***********************************************************************
 * sig_reboot
 * Shutdown the system 
 */

void sig_reboot(int signal)
{
   struct listitem *tmp;
   struct timespec ts;
   char **cmd;
   int   i;

   /* Let's disappear, we don't care about clients anymore */
   close(sock);
   /********* first SIGTERM the respawning processes **********/
   tmp = list->before;
   do {
      /* kill service watcher, which will kill processes itself */
      if( tmp->status == ST_RESPAWN) {
         kill(tmp->pid,SIGTERM);
      }
      tmp = tmp->before;
   } while( tmp != list );

   /********* now wait for the respawn watchers to return *****/
   tmp  = list->before;
   do {
      if( tmp->status == ST_RESPAWN) {
         /* wait until the respawn watcher terminated */
         waitpid(tmp->pid,&i,0);
      }

      /* execute shutdown service FIXME: parallelize that?*/
      exec_svc(tmp->abs_path,CMD_STOP_SVC);
      tmp = tmp->before;
   } while( tmp != list );

   /* now: all services are down, let's kill all other processes */
   if( kill(-1,SIGTERM) == -1) {
      perror(MSG_TERMKILL);
   }

   ts.tv_sec = SLEEP_KILL; /* defined in conf/sleep_kill */
   nanosleep(&ts,NULL);

   if( kill(-1,SIGKILL) == -1) {
      perror(MSG_KILLBILL);
   }
   D_PRINTF("SIGKILL GESENDET");

   /* release tmp */
   if(umount(CINIT_TMNT) == -1) {
      perror(CINIT_TMNT);
   }

/* THIS IS FUCKING UNCLEAN AND SHOULD BE CLEANED UP VERY MUCH!!! */
#define CMD_CNT 4

#define UMOUNT_CMD    "/bin/umount"
#define UMOUNT_ARG1   "-arfd"

#define MOUNT_CMD    "/bin/mount"
#define MOUNT_ARG1   "-o"
#define MOUNT_ARG2   "remount,ro"
#define MOUNT_ARG3   "/"

#define RESCUE_CMD    "/bin/sh"

   /* now: we are completley alone. umount everything, go to bed */
   cmd = (char **) malloc( (CMD_CNT+1) * ( sizeof (char*) ) );
   if(cmd) {
      /*  /bin/umount -a */
      cmd[0] = UMOUNT_CMD;
      cmd[1] = UMOUNT_ARG1;
      cmd[2] = NULL;

      i = fork();
      if(i == 0) {
         execv(cmd[0],cmd);
         _exit(1);   /* if exec fails in child */
      }

      /* /bin/mount -o remount,ro / */
      cmd[0] = MOUNT_CMD;
      cmd[1] = MOUNT_ARG1;
      cmd[2] = MOUNT_ARG2;
      cmd[3] = MOUNT_ARG3;
      cmd[4] = NULL;

      i = fork();
      if(i == 0) {
         execv(cmd[0],cmd);
         _exit(1);   /* if exec fails in child */
      }
   } else {
      _exit(1);
   }
   
   switch(signal) {
      case SIGTERM: /* power off */
         LOG(MSG_POWER_OFF);
         reboot(RB_POWER_OFF);
         break;
      case SIGHUP: /* reboot */
         LOG(MSG_REBOOT);
         reboot(RB_AUTOBOOT);
         break;
      case SIGUSR1: /* halt */
         LOG(MSG_HALT);
         reboot(RB_HALT_SYSTEM);
         break;
      case SIGUSR2: /* rescue - destroy ourself */
         LOG(MSG_RESCUE);
         cmd[0] = RESCUE_CMD;
         cmd[1] = NULL;
         execv(cmd[0],cmd);
         panic();
         break;
      case SIGCONT: /* update */
         LOG(MSG_UPDATE);
         cmd[0] = CINIT_BIN;
         cmd[1] = NULL;
         execv(cmd[0],cmd);
         panic();
         break;
   }

   /* do not exit, Linux does that for us */
}
