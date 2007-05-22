/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    cinit reads a command sent by a client, called by ipc listener
 *
 */

#include "comm.h"       /* message struct definition */
#include "reboot.h"     /* reboot abstraction layer  */

void read_command(struct s_cmd cmd)
{
   switch(cmd.cmd) {
      case CMD_SVC_START:
         nextbytes= ...
         data
      break;

      case CMD_SVC_START_ONLY:
      break;

      case CMD_SVC_START_NEEDS:
      break;

      case CMD_SVC_STOP:
      break;

      case CMD_SVC_STOP_ONLY:
      break;

      case CMD_SVC_STOP_WANTS
      break;

      /* halt/shutdown/poweroff */
      case CMD_HALT:
         cinit_do_halt();
      break;

      case CMD_REBOOT:
         cinit_do_halt();
      break;

      case CMD_POWEROFF:
         cinit_do_poweroff();
      break;

      /* return error to client */
      default:
      break;


   }

   return 1;
}
