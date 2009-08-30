/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * reboot/halt/poweroff/rescue
 * part of cinit
 */

#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

#include "cinit.h"

/* we trust the caller */
int msg_reboot(char cmd)
{
   if(!begin_msg(cmd)) return 0;
   close(sock);
   return 1;
}
/* clean for cinit-0.2 */
