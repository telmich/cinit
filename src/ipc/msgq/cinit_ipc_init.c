/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Create new queues: One for recieving, one for sending
 *
 */

#include <sys/ipc.h>       /* ftok           */
#include <sys/msg.h>       /* msgget         */
#include "intern.h"        /* print_errno    */
#include "msgq.h"          /* message queue  */

int cinit_ipc_init(void)
{
   key_t k_tmp;

   /* to_server */
   k_tmp = ftok(__CINIT_MSGQ_PATHNAME, __CINIT_MSGQ_TO_SERVER);
   if(k_tmp == -1) {
      print_errno(__CINIT_MSG_MSGQ_FTOK);
      return 0;
   }
   __cinit_mq_in = msgget(k_tmp, __CINIT_MSGQ_PERMS | IPC_CREAT);
   if(__cinit_mq_in == -1) {
      print_errno(__CINIT_MSG_MSGQ_MSGGET);
      return 0;
   }

   k_tmp = ftok(__CINIT_MSGQ_PATHNAME, __CINIT_MSGQ_TO_CLIENT);
   if(k_tmp == -1) {
      print_errno(__CINIT_MSG_MSGQ_FTOK);
      return 0;
   }
   __cinit_mq_out = msgget(k_tmp, __CINIT_MSGQ_PERMS | IPC_CREAT);
   if(__cinit_mq_out == -1) {
      print_errno(__CINIT_MSG_MSGQ_MSGGET);
      return 0;
   }

   return 1;
}
