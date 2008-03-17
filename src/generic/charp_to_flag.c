/*******************************************************************************
 *
 * 2008      Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Convert char pointer to uint32_t flag
 *
 */

#include <string.h>     /* strchr      */
#include <stdio.h>      /* NULL        */

#include "cinit.h"      /* cinit       */

uint32_t charp_to_flag(char *str)
{
   uint32_t ret = 0;

   if(str != NULL) {
      if(strchr(str, CINIT_CMD_SVC_WANTS) != NULL) ret |= CINIT_QSN_SVC_WANTS;
      if(strchr(str, CINIT_CMD_SVC_NEEDS) != NULL) ret |= CINIT_QSN_SVC_NEEDS;
   }

   return ret;
}
