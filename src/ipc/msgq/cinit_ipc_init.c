/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-linux-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Create new queues: One for recieving, one for sending
 *
 */

#include <sys/ipc.h>       /* ftok           */
#include <sys/msg.h>       /* msgget         */

#include "cinit.h"
#include "config.h"
#include "msgq.h"

int cinit_ipc_init(void)
{
   key_t k_tmp;

   /* to_server */
   k_tmp = ftok(MSGQ_PATHNAME,MSGQ_TO_SERVER);
   if(k_tmp == -1) {
      print_errno(MSG_MSGQ_FTOK);
      return 0;
   }
   mq_in = msgget(k_tmp,MSGQ_PERMS | IPC_CREAT);
   if(mq_in == -1) {
      print_errno(MSG_MSGQ_MSGGET);
      return 0;
   }

   /* to_client */
   k_tmp = ftok(MSGQ_PATHNAME,MSGQ_TO_CLIENT);
   if(k_tmp == -1) {
      print_errno(MSG_MSGQ_FTOK);
      return 0;
   }
   mq_out = msgget(k_tmp,MSGQ_PERMS | IPC_CREAT);
   if(mq_out == -1) {
      print_errno(MSG_MSGQ_MSGGET);
      return 0;
   }

   return 1;
}
