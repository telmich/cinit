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

int cinit_ipc_cread(struct cinit_answer *buf)
{
   struct msgq_server_short msg;

   if(msgrcv(mq_in, &msg, sizeof(msg), __cinit_cpid, 0) < 0) {
      print_errno("msgrcv,cread");
      return 0;
   }

   memcpy(buf, &(msg.msg), sizeof(*buf));

   return 1;
}
