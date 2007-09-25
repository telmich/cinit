/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Listen to messages
 *
 */

#include <stdio.h>      /* printf()       */

#include <sys/msg.h>    /* msgget         */
#include <errno.h>      /* errno          */

#include "intern.h"     /* print_errno    */
#include "msgq.h"       /* structs        */

int cinit_ipc_listen(void)
{
   int                        tmp;
   struct cinit_msgq_client   qsn;
   struct cinit_msgq_server   asr;
   struct msqid_ds            msq;

   /* FIXME: remove debug */
   printf("MSGQ-IPC: Listening...\n");

   tmp = msgrcv(__cinit_mq_in, &qsn, sizeof (qsn.qsn), 0, 0);

   /* message system problem */
   if(tmp == -1) {
      if(errno != EINTR) {
         print_errno(__CINIT_MSG_MSGQ_MSGRCV);
      }
      
      return -1;
   }

   /* retrieve pid */
   if(msgctl(__cinit_mq_in, IPC_STAT, &msq) == -1) {
      print_errno(__CINIT_MSG_MSGQ_MSGCTL);
      return -1;
   }

   // debug code
   //printf("pid direkt: self: %d (peer: %d)\n",msq.msg_lrpid, msq.msg_lspid);

   if(!read_command(qsn.qsn, &(asr.asr))) {
      /* FIXME: mini_print */
      printf("read command failed\n");
      
      asr.asr.ret = CINIT_MSG_ERR;
   }
      
   asr.mtype = msq.msg_lspid;
   if(msgsnd(__cinit_mq_out, &asr, sizeof(asr.asr), 0) == -1) {
      /* FIXME: do different things on differen errnos ... */
      print_errno("msgsend/answer");
   }

   return 1;
}
