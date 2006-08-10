/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    poweroff
 *
 */

#include <unistd.h>
#include <sys/reboot.h>

void cinit_poweroff(void)
{
   reboot(RB_HALT | RB_POWERDOWN);
}
