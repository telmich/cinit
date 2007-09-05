/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Client reads messages from cinit
 *
 */

#include <sys/msg.h>             /* msgget            */
#include <string.h>              /* memcpy()          */

#include "intern.h"              /* print_errno       */
#include "msgq.h"                /* msq specific      */

int cinit_ipc_cread(struct cinit_answer *buf)
{
   struct msgq_server asr;
   struct msqid_ds    msq;

   /* retrieve local pid */
   if(msgctl(__cinit_mq_in, IPC_STAT, &msq) == -1) {
      print_errno("msgctl");
      return 0;
   }
   
   asr.mtype = msq.msg_lrpid;

   if(msgrcv(__cinit_mq_in, &asr, sizeof(asr.asr), asr.mtype, 0) == -1) {
      /* FIXME: msg* */
      print_errno("msgrcv,cread");
      return 0;
   }
   memcpy(buf, &(asr.asr), sizeof(*buf));

   return 1;
}
