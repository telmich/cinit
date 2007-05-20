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
int msg_svc_on_off(char *svc, char action)
{
   if(!begin_msg(action)) return RT_ERR_COMM;
   if(!do_svc_name(sock,svc,ACT_CLIENT)) return RT_ERR_COMM;
   return (int) do_result(sock,NULL);
}
/* returns cinit-0.2-style return codes */
