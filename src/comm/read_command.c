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
#include "cinit.h"      /* structures                 */

int read_command(struct cinit_question qsn, struct cinit_answer *asr)
{
   switch(qsn.cmd) {
      case CINIT_MSG_GET_VERSION:
         asr->ret = CINIT_MSG_OK;
         strncpy(asr->data,VERSION,PATH_MAX);
      break;

      case CINIT_MSG_GET_STATUS:
         if(!answer_svc_status(qsn.data, asr)) return 0;
         /* FIXME: handle return 0 in parten */
      break;

      /* return error to client */
      default:
      break;
   }

   return 1;
}
