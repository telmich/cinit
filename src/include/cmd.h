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
   "cmd -[ed] -[nw] -[ps] [service] -[v]\n\n"   \
   "   -e: enable service\n"                    \
   "        including dependencies\n"           \
   "   -d: disable service\n"                   \
   "        including dependencies\n\n"         \
   "      -n: without needs\n"                     \
   "           Skip wants when en/disabling\n"     \
   "      -w: without wants\n"                     \
   "           Skip needs when en/disabling\n\n"   \
   "   -h: get help\n"                          \
   "        this messages"                      \
   "   -p: get process id (pid)\n"              \
   "        of specified service\n"             \
   "   -s: get status\n"                        \
   "        of specified service\n"             \
   "   -v: get version\n"                       \
   "        of cinit\n"                         \
   "   -V: get version\n"                       \
   "        of cmd\n"                           \
   ""

#define CMD_OPTIONS "e:d:hp:s:vV"

#define MSG_KILL     "kill()"
#define CMD_VERSION  "cmd 0.1"

#endif
