/* 
 * cinit
 * (c) 2005-2006 Nico Schottelius (nico-linux at schottelius.org)
 * reboot
 */

#include <sys/mount.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/reboot.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <time.h>

#include "cinit.h"

/**********************************************************************
 * halt the system
 */
void cinit_halt(void)
{
   reboot(RB_HALT_SYSTEM);
}
