/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Listen to messages
 *
 */

#include <sys/ipc.h>             /* ftok              */
#include <sys/msg.h>             /* msgget            */
#include <unistd.h>              /* getpid()          */

#include "config.h"
#include "intern.h"              /* print_errno       */
#include "msgq.h"                /* msgq constants    */

int cinit_ipc_logon(void)
{
   key_t k_in, k_out;   /* FIXME: remove one variable */

   /* generiere nen schluessel: andersrum als im Server */
   k_in  = ftok(MSGQ_PATHNAME,MSGQ_TO_CLIENT);
   k_out = ftok(MSGQ_PATHNAME,MSGQ_TO_SERVER);

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

   /* we use the pid as identifier, so initialise it here */
   __cinit_cpid = getpid();
 
   return 1;
}
