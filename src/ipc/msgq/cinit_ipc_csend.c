/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Client sends messages to cinit
 *
 */

#include <sys/msg.h>          /* msgget            */
#include <string.h>           /* memcpy()          */

#include "intern.h"           /* print_errno       */
#include "msgq.h"             /* structure         */

int cinit_ipc_csend(struct cinit_question *qsn)
{
   struct msgq_client msg;

   msg.mtype      = 1;              /* cinit = 1 */

   /* copy question structure into the msgq-structure */
   memcpy(&(msg.qsn), qsn, sizeof(msg.qsn));

   if(msgsnd(__cinit_mq_out, &msg, sizeof(msg), 0) == -1) {
      /* FIXME: msg */
      print_errno("msgsnd,csend");
      return 0;
   }

   return 1;
}
