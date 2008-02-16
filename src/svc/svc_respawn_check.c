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
 *    OBSOLETED? not in use.
 *
 *    Check whether service is existent
 */

#error "NOT IN USE"

#include <stdio.h>      /* NULL        */
#include <limits.h>     /* PATH_MAX    */
#include "svc.h"

/* checking for existence is done before! */
int svc_respawn_check(struct listitem *svc)
{
   char buf[PATH_MAX+1];

   strcpy(buf,svc->abs_path);
   if(!path_append(buf,C_RESPAWN)) return 0
}
