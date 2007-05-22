/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Listen to messages
 *
 */

#include <stdio.h>      /* printf()       */

#include <sys/ipc.h>    /* ftok           */
#include <sys/msg.h>    /* msgget         */
#include <errno.h>      /* errno          */

#include "intern.h"     /* print_errno    */
#include "config.h"
#include "msgq.h"
#include "comm.h"       /* the cmd struct */

int cinit_ipc_listen(void)
{
   int tmp;

   //struct msg_client m_client;

   struct s_cmd cmd;

   while (1) {
      mini_printf("IPC loop\n",1);

      tmp = msgrcv(mq_in,&cmd,(sizeof cmd),0,0);

      if(tmp == -1) {
         if(errno != EINTR) {
            print_errno(MSG_MSGQ_MSGRCV);
         }
         continue;
      }
      
      printf("pid: %d, cmd: %c\n",cmd.pid,cmd.cmd);

      //read_command(cmd);

      /* use pid as the message type 
      m_serv.mtype = (long) m_client.pid;
      strcpy(m_serv.text,"Alles ok\n");

      tmp = msgsnd(mq_out, &m_serv, sizeof(m_serv), 0);

      if(tmp == -1) {
         perror("msgsnd");
         return 0;
      } */
   }

   return 1;
}
