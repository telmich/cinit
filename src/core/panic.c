
/*******************************************************************************
 *
 * 2005-2008 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Execute something 
 */

#include <unistd.h>             /* execv */

#include "intern.h"
#include "messages.h"

void panic(void)
{
   char *nargv[2];

   if(execute_and_wait(CINIT_PANIC))
      _exit(0);

   /***********************************************************************
    * In case nothing helps, try to execute something that is always there.
    * (conf/c_desaster)
    */
   nargv[0] = C_DESASTER;
   nargv[1] = NULL;

   if(execv(nargv[0], nargv) == -1) {
      print_errno(MSG_FATAL_PANIC);
   }

   /* We tried everything possible, die now. */
   _exit(1);
}
