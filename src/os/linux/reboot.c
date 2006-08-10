/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    reboot the system
 *
 */

#include <unistd.h>
#include <sys/reboot.h>

void cinit_reboot(void)
{
   reboot(RB_AUTOBOOT);
}
