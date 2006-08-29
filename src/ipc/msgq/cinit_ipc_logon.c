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

int cinit_ipc_logon(void)
{
   int tmp;
   key_t k_in, k_out;
   int mq_in = 0, mq_out = 0;

   struct msg_client m_client;
   struct msg_server m_serv;

   /* generiere nen schluessel: andersrum als im Server */
   k_in  = ftok(IPC_KEY,IPC_OUT);
   k_out = ftok(IPC_KEY,IPC_IN);

   if(k_in == -1 || k_out == -1) {
      print_errno(MSG_MSGQ_FTOK);
      return 0;
   }

   /* neue queue */
   mq_in    = msgget(k_in,0666 | IPC_CREAT);
   mq_out   = msgget(k_out,0666 | IPC_CREAT);

   if(mq_in == -1 || mq_out == -1) {
      print_errno(MSG_MSGQ_MSGGET);
      return 0;
   }
 
   return 1;
}
