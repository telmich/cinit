/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * tell cinit that I want to start a service
 * part of cinit
 */

#include <string.h>
#include <unistd.h>
#include <stdio.h>

#include "cinit.h"


/* ********************************************************************** 
 * action: 1=on, 0=off
 */
int msg_svc_on_off(char *svc, int action)
{
   char cmd;

   if(action) {
      cmd = CMD_START_SVC;
   } else {
      cmd = CMD_STOP_SVC;
   }

   if(!begin_msg(cmd)) return 0;
   if(!do_svc_name(sock,svc,ACT_CLIENT)) return 0;
   return (int) do_result(sock,NULL);
}
