
/*******************************************************************************
 *
 * 2006-2008 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Mark the service as being failed
 */

#include "svc.h"
#include "svc-intern.h"

void svc_fail(struct listitem *li)
{
   if(li->status & CINIT_ST_ONCE_RUN)
      li->status = CINIT_ST_ONCE_FAIL;
   else {
      /*
       * FIXME: do something senseful, record time of dead? 
       */
      li->status = CINIT_ST_RESPAWNING;
   }
}
