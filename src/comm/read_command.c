/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    cinit reads a command sent by a client, called by ipc listener
 *
 */

#include "cinit.h"      /* structures                 */
#include "intern.h"     /* answer_svc_status()        */

int read_command(struct cinit_question qsn, struct cinit_answer *asr)
{
   switch(qsn.cmd) {
      case CINIT_MSG_GET_VERSION:
         if(!answer_version(asr)) return 0;
      break;

      case CINIT_MSG_GET_STATUS:
         if(!answer_svc_status(qsn.data, asr)) return 0;
      break;

      case CINIT_MSG_GET_PID:
         if(!answer_svc_pid(qsn.data, asr)) return 0;
      break;

      /* Unknown command: should not happen :-) */
      default:
         return 0;
      break;
   }

   return 1;
}
