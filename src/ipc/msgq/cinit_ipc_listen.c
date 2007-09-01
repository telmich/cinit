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

#include <sys/ipc.h>    /* ftok           */
#include <sys/msg.h>    /* msgget         */
#include <errno.h>      /* errno          */

#include "intern.h"     /* print_errno    */
//#include "config.h"
#include "msgq.h"       /* structs        */

int cinit_ipc_listen(void)
{
   int                  tmp;
   struct msgq_client   qsn;
   struct msgq_server   asr;
   struct msqid_ds      msq;

   while (1) {
      qsn.mtype = 1; /* listen only to mtype = 1, == init */
      tmp = msgrcv(mq_in, &qsn, sizeof (qsn.w), 0, 0);

      if(tmp == -1) {
         if(errno != EINTR) {
            print_errno(MSG_MSGQ_MSGRCV);
         }
         continue;
      }

      if(msgctl(mq_in, IPC_STAT, &msq) == -1) {
         print_errno("msgctl");
         continue;
      }

      printf("pid direkt: %d (%d)\n",msq.msg_lrpid, msq.msg_lspid);

      printf("pid: %d, cmd: %d\n",qsn.w.pid, qsn.w.qsn.cmd);

      if(!read_command(qsn.w.qsn, &(asr.asr))) {
         /* FIXME: msg */
         printf("read command failed\n");
      }

      /* answer something for now */
      asr.mtype = qsn.w.pid;
      /* FIXME: do different things on differen errnos ... */
      if(msgsnd(mq_out, &asr, sizeof(asr.asr), 0) == -1) {
         print_errno("msgsend/answer");
      }
   }

   return 1;
}
