/***********************************************************************
 *
 *    2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    poweroff
 *
 */

#include <unistd.h>           /* reboot */
#include <sys/reboot.h>       /* reboot */
#include <stdio.h>            /* NULL   */

void cinit_reboot(void)
{
   reboot(RB_AUTOBOOT,NULL);
}
