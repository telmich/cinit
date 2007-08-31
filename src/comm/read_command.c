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

#include "cinit.h"      /* structures                 */

int read_command(struct cinit_question qsn, struct cinit_answer *asr)
{
   switch(qsn.cmd) {
      case CMD_SVC_START:
      break;

      case CMD_SVC_START_ONLY:
      break;

      case CMD_SVC_START_NEEDS:
      break;

      case CMD_SVC_STOP:
      break;

      case CMD_SVC_STOP_ONLY:
      break;

      case CMD_SVC_STOP_WANTS:
      break;

      /* return error to client */
      default:
      break;


   }

   return 1;
}
