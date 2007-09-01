/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Client sends messages to cinit
 *
 */

/* FIXME: cleanup headers */
#include <sys/ipc.h>          /* ftok              */
#include <sys/msg.h>          /* msgget            */

#include <string.h>           /* memcpy()          */
#include "config.h"
#include "intern.h"           /* print_errno       */
#include "msgq.h"             /* structure         */

int cinit_ipc_csend(struct cinit_question *qsn)
{
   struct msgq_client msg;

   msg.mtype      = 1;              /* cinit = 1 */
   msg.w.pid      = __cinit_cpid;

   /* copy structure into the msgq-structure */
   memcpy(&(msg.w.qsn), qsn, sizeof(msg.w.qsn));

   if(msgsnd(mq_out, &msg, sizeof(msg.w), 0) == -1) {
      /* FIXME: msg */
      print_errno("msgsnd,csend");
      return 0;
   }

   return 1;
}
