/***********************************************************************
 *
 *    2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    How to halt the system
 */

#include <unistd.h>
#include <sys/reboot.h>

void cinit_halt(void)
{
   reboot(RB_HALT_SYSTEM);
}
