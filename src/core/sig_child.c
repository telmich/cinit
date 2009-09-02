/*******************************************************************************
 *
 * 2005-2009 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    The child handler (may *not* exec other functions!)
 *
 */

#include "svc-intern.h"          /* marking */

/***********************************************************************
 * sig_child: (c)collect the children
 */
void sig_child(int tmp)
{
   tmp = 2; /* FIXME: how to tell stupid gcc that tmp is a must? */
   svc_exited = 1; /* FIXME: catch possible race conditions in svc_status_changed() */
}
