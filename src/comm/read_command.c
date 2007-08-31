/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    cinit reads a command sent by a client, called by ipc listener
 *
 */

#include <string.h>     /* strncpy                    */

#include "config.h"     /* VERSION                    */
#include "comm.h"       /* message struct definition  - OLD?*/
#include "cinit.h"      /* structures                 */

int read_command(struct cinit_question qsn, struct cinit_answer *asr)
{
   switch(qsn.cmd) {
      case CINIT_MSG_GET_VERSION:
         asr->ret = CINIT_MSG_OK;
         strncpy(asr->data,VERSION,PATH_MAX);
      break;

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
