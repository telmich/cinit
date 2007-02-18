/***********************************************************************
 *
 *    2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
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
