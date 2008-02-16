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
 *    Shutdown all services: This is more or less the negative
 *    version of 'tree_exec()'
 */

#include "svc-intern.h"    /* struct      */

void shutdown_services(struct listitem *svc)
{
   while(0) {
      svc++;
   }
   /* stop services in the correct order:
    * - begin at a random process, and walk the tree up to the wanted_by and needed_by
    * - switch to next service, as soon as this tree is finished
    */

//   while(we_are_wanted_or_needed) {
//      shutdown_services(next_wants_or_needs_us);
//   }

//   shutdown_services(svc) 
   
   /* begin at svc, iterate until a service without dependencies is found,
    * continue stopping through wanted-by / needed-by / wants / needs */

   return;
}
