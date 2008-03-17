/*******************************************************************************
 *
 * 2007-2008 Nico Schottelius (nico-cinit at schottelius.org)
 *
 * This file is part of cinit.

 * cinit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cinit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cinit.  If not, see <http://www.gnu.org/licenses/>.

 *
 *    Header file for the cmd (cinit management)
 */

#ifndef CINIT_CMD_HEADER
#define CINIT_CMD_HEADER

#define CMD_USAGE "cmd - cinit management\n\n"  \
   "cmd -[de [nw]] -[ps] [service] -[hvV]\n\n"   \
   "   -d: disable service\n"                   \
   "       n: without needs\n"                  \
   "           Skip needs when en/disabling\n\n"\
   "       w: without wants\n"                  \
   "           Skip wants when en/disabling\n"  \
   "   -e: enable service\n"                    \
   "        see above\n"                        \
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

#define CMD_OPTIONS "e::d::hpsvV"

#define MSG_KILL     "kill()"
#define CMD_VERSION  "0.2"

#endif
