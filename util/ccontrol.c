/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * ccontrol: control cinit
 * part of cLinux/cinit
 */

/* *stat() */
#include <sys/stat.h>
#include <unistd.h>

/* open */
#include <fcntl.h>

/* signal */
#include <signal.h>

/* PATH_MAX */
#include <limits.h>

/* str* */
#include <string.h>

/* sockets */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

/* mount */
#include <sys/mount.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "cinit.h"

/* global variable */
struct listitem *list;
int sock;
pid_t cpid;

/***********************************************************************
 * cservice - control cinit
 */

#define USAGE_TEXT "ccontrol - control cinit\n\n" \
   "\n\nUsage:\n\nccontrol -[phearsuw] <service>\n"  \
   "\t-p\t- (power off) Power off the system\n" \
   "\t-h\t- (halt)      Halt the system \n" \
   "\t-r\t- (reboot)    Reboot the system\n" \
   "\t-s\t- (single user/rescue) Rescue mode\n" \
   "\t-u\t- (update) XXX????     Update cinit\n" \
   "\t-w\t- (warm reboot) XXX??? Stop and start everything\n\n"

#define C_USAGE(error) usage(USAGE_TEXT,error)

/***********************************************************************
 * ccontrol: control cinit
 */
int main(int argc, char **argv)
{
   /* argv */
   if(argc != 2)              C_USAGE("Too less arguments!");
   if(argv[1][0] != '-')      C_USAGE("Wrong arguments");

   switch(argv[1][1]) {
      case 'p':   /* power off */
         LOG("Powering off...");
         msg_reboot(CMD_POWEROFF);
         break;

      case 'h':   /* halt */
         LOG("Halting...");
         msg_reboot(CMD_HALT);
         break;

      case 'r':   /* reboot */
         LOG("Rebooting...");
         msg_reboot(CMD_REBOOT);
         break;

      case 's':   /* rescue */
         LOG("Rescue mode...");
         msg_reboot(CMD_RESCUE);
         break;

      case 'u':   /* update */
         LOG("Update in progress...");
         msg_reboot(CMD_UPDATE);
         break;

      case 'w':   /* warm reboot */
         LOG("Hot reboot in progress...");
         msg_reboot(CMD_WBOOT);
         break;

      default:
         C_USAGE("Unknown parameter");
         break;
   }
   return 0;
}
