/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Destory ipc mechanism, cinit is gonna die soon.
 *
 */

#include <sys/msg.h>       /* msgget         */
#include <stdio.h>         /* NULL           */

#include "msgq.h"
#include "cinit.h"

void cinit_ipc_destroy(void)
{
   if(msgctl(mq_in,IPC_RMID,NULL) == -1) {
      print_errno(MSG_MSGQ_DESTROY);         /* print warning, continue */
   }
   if(msgctl(mq_out,IPC_RMID,NULL) == -1) {
      print_errno(MSG_MSGQ_DESTROY);         /* print warning, continue */
   }
}
