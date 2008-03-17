/*******************************************************************************
 *
 * 2006-2008 Nico Schottelius (nico-cinit at schottelius.org)
 *
 * This file is part of cinit.

 * cinit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cinit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cinit.  If not, see <http://www.gnu.org/licenses/>.

 *    Listen to messages
 *
 */

#include <stdio.h>      /* printf()       */

#include <sys/msg.h>    /* msg*           */
#include <errno.h>      /* errno          */

#include "intern.h"     /* print_errno    */
#include "msgq.h"       /* structs        */

int cinit_ipc_listen(void)
{
   int                        tmp;
   struct cinit_msgq_client   qsn;
   struct cinit_msgq_server   asr;
   struct msqid_ds            msq;

   tmp = msgrcv(__cinit_mq_in, &qsn, sizeof (qsn.qsn), 0, 0);

   /* message system problem */
   if(tmp == -1) {
      if(errno != EINTR) {
         print_errno(__CINIT_MSG_MSGQ_MSGRCV);
      }
      return -1;
   }

   /* retrieve pid */
   if(msgctl(__cinit_mq_in, IPC_STAT, &msq) == -1) {
      print_errno(__CINIT_MSG_MSGQ_MSGCTL);
      return -1;
   }

   if(!read_command(qsn.qsn, &(asr.asr))) {
      /* FIXME: mini_print */
      printf("read command failed\n");
      
      asr.asr.ret = CINIT_ASW_ERR_INTERN;
   }
      
   asr.mtype = msq.msg_lspid;
   if(msgsnd(__cinit_mq_out, &asr, sizeof(asr.asr), 0) == -1) {
      /* FIXME: do different things on differen errnos ... */
      print_errno("msgsend/answer");
   }

   return 1;
}
