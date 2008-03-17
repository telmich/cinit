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
 *    Converts cher * to uint32_t for svc operations
 *
 */


#include <stdio.h>      /* NULL                 */
#include <string.h>     /* strchr               */
#include <stdint.h>     /* integers             */

#include "cinit.h"      /* constants            */

uint32_t cinit_flag_to_uint32_t(char *flag)
{
   uint32_t ret = 0; /* no flags */

   if(flag != NULL) {
      if(strchr(flag, CINIT_CMD_SVC_NEEDS)) {
         ret |= CINIT_QSN_SVC_NEEDS;
      }
      if(strchr(flag, CINIT_CMD_SVC_WANTS)) {
         ret |= CINIT_QSN_SVC_WANTS;
      }
   }

   return ret;
}
