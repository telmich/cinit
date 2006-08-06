/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Listen to messages
 *
 */

#include <sys/ipc.h>             /* ftok */
#include <sys/msg.h>             /* msgget */

#include "config.h"
#include "msgq.h"

int cinit_ipc_listen(void)
{
   int tmp;
   key_t k_in, k_out;
   int mq_in = 0, mq_out = 0;
   int tmp = 0;

   struct msg_client m_client;
   struct msg_server m_serv;
   
   /* generiere nen schluessel */
   k_in  = ftok(IPC_KEY,IPC_IN);
   k_out = ftok(IPC_KEY,IPC_OUT);

   if(k_in == -1 || k_out == -1) {
      perror("ftok");
      exit(1);
   }
   
   /* neue queue */
   mq_in    = msgget(k_in,0666 | IPC_CREAT);
   mq_out   = msgget(k_out,0666 | IPC_CREAT);

   if(mq_in == -1 || mq_out == -1) {
      perror("msgget");
      exit(1);
   }
    
    /* wrong tabsto ;-) */
while (1) {
   tmp =  msgrcv(mq_in,&m_client,(sizeof m_client),0,0);

   if(tmp == -1) {
      perror("msgrcv");
      exit(1);
   }

   printf("pid: %d, m_client: %s\n",m_client.pid,m_client.text);

   /* use pid as the message type */
   m_serv.mtype = (long) m_client.pid;
   strcpy(m_serv.text,"Alles ok\n");

   tmp = msgsnd(mq_out, &m_serv, sizeof(m_serv), 0);

   if(tmp == -1) {
      perror("msgsnd");
      exit(1);
   }
} /* while */


   return 1;
}
