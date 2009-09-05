/*******************************************************************************
 *
 * 2007-2009 Nico Schottelius (nico-cinit at schottelius.org)
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
      FIXME: not needed anymore! -> change to svc_status_changed()
 *    Stop a service, taking care about its dependencies
 */

#include "svc.h"                /* enums */
#include "svc-intern.h"         /* struct listitem */

/*
 * how == CINIT_SSSO_COMPLETE => stop needs/wants before
 * how & CINIT_SSSO_WO_NEEDS  => omit needs
 * how & CINIT_SSSO_WO_WANTS  => omit wants
 */

void svc_stop_deps(struct listitem *li, int how)
{
   struct dep *tmp;

   /*
    * don't continue if already being stopped 
    */
   if(li->status & CINIT_ST_SH_STOP) return;

   /*
    * shutdown depending services first: needed_by 
    */
   tmp = li->needed_by;
   do {
      if(how & CINIT_SSSO_WO_NEEDS)
         break;
      svc_stop_deps(tmp->svc, how);
      tmp = tmp->next;
   } while(tmp != li->needed_by);

   /*
    * shutdown depending services first: wanted_by 
    */
   tmp = li->wanted_by;
   do {
      if(how & CINIT_SSSO_WO_WANTS)
         break;
      svc_stop_deps(tmp->svc, how);
      tmp = tmp->next;
   } while(tmp != li->wanted_by);

   svc_disable(li);
}
