/* 
 * cinit
 * (c) 2005-2006 Nico Schottelius (nico-linux at schottelius.org)
 * poweroff
 */

#include <sys/reboot.h>
#include <unistd.h>

#include "cinit.h"

/**********************************************************************
 * poweroff the system
 */
void cinit_poweroff(void)
{
   reboot(RB_POWER_OFF);
}
