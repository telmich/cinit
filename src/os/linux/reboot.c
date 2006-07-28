/* 
 * cinit
 * (c) 2005-2006 Nico Schottelius (nico-linux at schottelius.org)
 * reboot
 */

#include <sys/reboot.h>
#include <unistd.h>

#include "cinit.h"

/**********************************************************************
 * reboot the system
 */
void cinit_reboot(void)
{
   reboot(RB_AUTOBOOT);
}
