/* 
 * (c) 2006 Nico Schottelius (nico-linux-cinit //@\\ schottelius.org)
 * part of cinit
 */

#include <sys/ipc.h>             /* ftok */
#include <sys/msg.h>             /* msgget */

#include "cinit.h"
#include "msgq.h"

int cinit_ipc_init(void)
{
   key_t k_tmp;

   k_tmp = ftok(MSGQ_PATHNAME,MSGQ_TO_SERVER);

   if(k_tmp == -1) return 0;
   
   mq_server = msgget(k_tmp,0600 | IPC_CREAT);
   if(mq_server == -1) return 0;

   return 1;
}
