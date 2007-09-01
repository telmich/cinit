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

   printf("cread: %p\n",buf);

   if(msgrcv(mq_in, &msg, sizeof(msg.msg), __cinit_cpid, 0) == -1) {
      print_errno("msgrcv,cread");
      return 0;
   }
   printf("ergebnins bekommen: %s\n", msg.msg.data);


   memcpy(buf, &(msg.msg), sizeof(struct cinit_answer));
//   memcpy(buf, &(msg.msg), sizeof(*buf));
   printf("ergebnins bekommen: %s\n", msg.msg.data);
   printf("ergebnins bekommen (buf): %s\n", buf->data);
   printf("cread-ende: %p\n",buf);

   return 1;
}
