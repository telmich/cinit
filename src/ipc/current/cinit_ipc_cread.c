/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Client reads messages from cinit
 *
 */

#include <sys/msg.h>             /* msg*              */
#include <string.h>              /* memcpy()          */
#include <unistd.h>              /* getpid()          */
#include "intern.h"              /* print_errno       */
#include "msgq.h"                /* msq specific      */

int cinit_ipc_cread(struct cinit_answer *buf)
{
   struct msgq_server asr;

   if(msgrcv(__cinit_mq_in, &asr, sizeof(asr.asr), getpid(), 0) == -1) {
      print_errno(MSG_MSGQ_MSGRCV);
      return 0;
   }
   memcpy(buf, &(asr.asr), sizeof(*buf));

   return 1;
}
