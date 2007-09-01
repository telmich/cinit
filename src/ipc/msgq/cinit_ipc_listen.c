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
#include "config.h"
#include "msgq.h"       /* structs        */
#include "comm.h"       /* the cmd struct */

int cinit_ipc_listen(void)
{
   int                  tmp;
   struct msgq_client   qsn;
   struct msgq_server   asr;

   while (1) {
      qsn.mtype = 1; /* listen only to mtype = 1, == init */
      tmp = msgrcv(mq_in, &qsn, sizeof (qsn.w), 0, 0);

      if(tmp == -1) {
         if(errno != EINTR) {
            print_errno(MSG_MSGQ_MSGRCV);
         }
         continue;
      }

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

      /*

      switch(msg.cmd) {
         case CINIT_MSG_GET_STATUS:
         break;

      }

       * send back: use pid as the message type 
      m_serv.mtype = (long) m_client.pid;
      strcpy(m_serv.text,"Alles ok\n");

      tmp = msgsnd(mq_out, &m_serv, sizeof(m_serv), 0);

      if(tmp == -1) {
         perror("msgsnd");
         return 0;
      } */
   }

   return 1;
}
