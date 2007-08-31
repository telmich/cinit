/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Client sends messages to cinit
 *
 */

#include <sys/ipc.h>             /* ftok              */
#include <sys/msg.h>             /* msgget            */

#include <string.h>              /* memcpy()          */

#include "config.h"
#include "intern.h"              /* print_errno       */
#include "msgq.h"

int cinit_ipc_csend(struct cinit_question *data)
{
   struct msgq_client msg;

   msg.pid     = __cinit_cpid;
   msg.mtype   = 1;              /* cinit = 1 */

   /* copy structure into the msgq-structure */
   memcpy(&(msg.msg),data, sizeof(msg.msg));

   if(msgsnd(mq_out,&msg,sizeof(msg),0) < 0) {
      print_errno("msgsnd,csend");
      return 0;
   }

   return 1;
}
