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
 *    Disable a service without dependencies
 */

#include <stdint.h>

#include "svc-intern.h"
#include "svc.h"
#include "cinit.h"

/* checking for existence is done before! */
uint32_t svc_disable(struct listitem *li)
{
   svc_set_status(li, CINIT_ST_STOPPING);
   svc_stop(li);
   svc_set_status(li, CINIT_ST_STOPPED);

   return CINIT_ASW_SVC_DISABLED;
}
