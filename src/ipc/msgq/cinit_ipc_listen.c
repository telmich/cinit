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
   int                  tmp;
   struct msgq_client   qsn;
   struct msgq_server   asr;
   struct msqid_ds      msq;

   while (1) {
      qsn.mtype = 1; /* listen only to mtype = 1, == init */
      tmp = msgrcv(__cinit_mq_in, &qsn, sizeof (qsn.qsn), 0, 0);

      if(tmp == -1) {
         if(errno != EINTR) {
            print_errno(MSG_MSGQ_MSGRCV);
         }
         continue;
      }

      if(msgctl(__cinit_mq_in, IPC_STAT, &msq) == -1) {
         /* FIXME: do MSG_ */
         print_errno("msgctl");
         continue;
      }

      printf("pid direkt: self: %d (peer: %d)\n",msq.msg_lrpid, msq.msg_lspid);

      if(!read_command(qsn.qsn, &(asr.asr))) {
         /* FIXME: msg; mini_printf! */
         printf("read command failed\n");
         
         asr.asr.ret = CINIT_MSG_ERR;
      }

      
      asr.mtype = msq.msg_lspid;
      if(msgsnd(__cinit_mq_out, &asr, sizeof(asr.asr), 0) == -1) {
         /* FIXME: do different things on differen errnos ... */
         print_errno("msgsend/answer");
      }
   }

   return 1;
}
