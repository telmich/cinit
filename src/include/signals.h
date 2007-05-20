/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Define signals to use: needs signal.h to be included before.
 */

#ifndef CINIT_SIGNALS_HEADER
#define CINIT_SIGNALS_HEADER

#define SIG_CINIT_HALT        SIGUSR1
#define SIG_CINIT_POWEROFF    SIGTERM
#define SIG_CINIT_REBOOT      SIGHUP

#endif
