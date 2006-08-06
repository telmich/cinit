/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Create new queues: One for recieving, one for sending
 *
 */

#include <sys/ipc.h>             /* ftok */
#include <sys/msg.h>             /* msgget */

#include "config.h"
#include "msgq.h"

int cinit_ipc_init(void)
{
   key_t k_tmp;

   /* to_server */
   k_tmp = ftok(MSGQ_PATHNAME,MSGQ_TO_SERVER);
   if(k_tmp == -1) {
      perror(MSG_MSGQ_FTOK);
      return 0;
   }
   mq_server = msgget(k_tmp,0600 | IPC_CREAT);
   if(mq_server == -1) {
      perror(MSG_MSGQ_MSGGET);
      return 0;
   }

   /* to_client */
   k_tmp = ftok(MSGQ_PATHNAME,MSGQ_TO_CLIENT);
   if(k_tmp == -1) {
      perror(MSG_MSGQ_FTOK);
      return 0;
   }
   mq_client = msgget(k_tmp,0600 | IPC_CREAT);
   if(mq_client == -1) {
      perror(MSG_MSGQ_MSGGET);
      return 0;
   }

   return 1;
}
