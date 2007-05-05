/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    reboot specific functions
 *
 */

#ifndef CINIT_REBOOT_HEADER
#define CINIT_REBOOT_HEADER

/*****************************************************************************
 * Functions: abstract do_reboot
 */
#define cinit_do_reboot()     do_reboot(SIGHUP)
#define cinit_do_halt()       do_reboot(SIGUSR1)
#define cinit_do_poweroff()   do_reboot(SIGTERM)

#endif
