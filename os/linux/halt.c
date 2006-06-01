/* 
 * cinit
 * (c) 2005-2006 Nico Schottelius (nico-linux at schottelius.org)
 * reboot
 */

#include <sys/reboot.h>
#include <unistd.h>

#include "cinit.h"

/**********************************************************************
 * halt the system
 */
void cinit_halt(void)
{
   reboot(RB_HALT_SYSTEM);
}
