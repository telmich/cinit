/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Client reads messages from cinit
 *
 */

/* FIXME: cleanup headers */
#include <sys/ipc.h>             /* ftok              */
#include <sys/msg.h>             /* msgget            */

#include <string.h>              /* memcpy()          */

#include "intern.h"              /* print_errno       */
#include "msgq.h"                /* __cinit_cpid      */

   #include <stdio.h>
int cinit_ipc_cread(struct cinit_answer *buf)
{
   struct msgq_server msg;

   if(msgrcv(mq_in, &msg, sizeof(msg.asr), __cinit_cpid, 0) == -1) {
      /* FIXME: msg* */
      print_errno("msgrcv,cread");
      return 0;
   }
   memcpy(buf, &(msg.asr), sizeof(*buf));

   return 1;
}
