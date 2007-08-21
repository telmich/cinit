/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Header file for the cmd (cinit management)
 */

#ifndef CINIT_CMD_HEADER
#define CINIT_CMD_HEADER

#define CMD_USAGE "cmd - cinit management\n\n"  \
   "Usage:\n\ncmd -[ednwphr]\n"                 \
   "   -e: enable service\n"                    \
   "        including dependencies\n"           \
   "   -d: disable service\n"                   \
   "        including dependencies\n"           \
   "   -n: without needs\n"                     \
   "        Skip wants when en/disabling\n"     \
   "   -w: without wants\n"                     \
   "        Skip needs when en/disabling\n"     \
   "   -s: get status\n"                        \
   "        of specified service\n"             \
   "   -h: halt\n"                              \
   "   -p: poweroff\n"                          \
   "   -r: reboot\n"

#define CMD_OPTIONS "ednwphr"

#endif
