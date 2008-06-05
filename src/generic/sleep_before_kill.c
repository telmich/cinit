
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
 * Let's sleep a little bit
 *
 */

#include <time.h>               /* nanosleep */
#include <stdlib.h>             /* strtol() */
#include <errno.h>              /* errno */

#include "intern.h"             /* print_errno */
#include "messages.h"           /* messages */

void sleep_before_kill()
{
   char *content;
   int tmp;
   struct timespec ts;

   if(openreadclose(CINIT_SLEEPFILE, &content) == ORC_OK) {
      errno = 0;
      tmp = strtol(content, NULL, 10);
      if(errno != 0)
         tmp = SLEEP_KILL;
      free(content);
   } else {
      mini_printf(MSG_BUILTIN_SLEEP, 1);
      tmp = SLEEP_KILL;
   }

   ts.tv_sec = tmp;
   ts.tv_nsec = 0;

   if(nanosleep(&ts, NULL) == -1) {
      print_errno(MSG_ERR_SLEEP);
   }
}
