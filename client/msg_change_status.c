/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * tell cinit that I want change the status of a service
 * part of cinit
 */

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

#include "cinit.h"

int msg_change_status(char *svc, char status, pid_t pid)
{
   if(!begin_msg(CMD_CHG_STATUS)) {
      return 0;
   }
   if(!do_change_status(svc,&status,&pid,sock,ACT_CLIENT)) {
      return 0;
   }
   if(!do_result(sock,NULL)) {
      return 0;
   }

   return 1;
}
