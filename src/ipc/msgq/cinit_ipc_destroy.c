/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Destory ipc mechanism, cinit is gonna die soon.
 *
 */

#include <sys/msg.h>       /* msgget         */
#include <stdio.h>         /* NULL           */

#include "msgq.h"          /* mq_in, mq_out  */
#include "intern.h"        /* print_errno    */

void cinit_ipc_destroy(void)
{
   if(msgctl(__cinit_mq_in, IPC_RMID, NULL) == -1) {
      print_errno(MSG_MSGQ_DESTROY);         /* print warning, continue */
   }
   if(msgctl(__cinit_mq_out, IPC_RMID, NULL) == -1) {
      print_errno(MSG_MSGQ_DESTROY);         /* print warning, continue */
   }
}
