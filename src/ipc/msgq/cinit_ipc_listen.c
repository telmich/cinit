/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Listen to messages
 *
 */

#include <sys/ipc.h>    /* ftok           */
#include <sys/msg.h>    /* msgget         */

#include "cinit.h"      /* print_errno    */
#include "config.h"
#include "msgq.h"

int cinit_ipc_listen(void)
{
   int tmp;

   struct msg_client m_client;

   while (1) {
      /* FIXME: change msg structure */
      tmp = msgrcv(mq_in,&m_client,(sizeof m_client),0,0);

      if(tmp == -1) {
         /* FIXME: EINTR ignore */
         print_errno(MSG_MSGQ_MSGRCV);
      }

      //printf("pid: %d, m_client\n",m_client.pid);

      /* use pid as the message type 
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
