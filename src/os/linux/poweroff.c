/***********************************************************************
 *
 *    2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    poweroff the system
 *
 */

#include <unistd.h>
#include <sys/reboot.h>

void cinit_poweroff(void)
{
   reboot(RB_POWER_OFF);
}
