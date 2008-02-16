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
 *    Check whether service is existent
 */

#include <stdio.h>      /* NULL           */
#include <sys/stat.h>   /* stat           */
#include <errno.h>      /* errno          */

#include "svc.h"        /* constants      */
#include "svc-intern.h" /* listitem       */
#include "intern.h"     /* path_append    */
#include "cinit.h"      /* CINIT_DATA_LEN */

/* checking for existence is done before! */
struct listitem *svc_create(char *svc)
{
   char              buf[CINIT_DATA_LEN];
   struct stat       statbuf;
   struct listitem   *li;
   
   li = list_insert(svc, -1);
   if(!li) return NULL;

   cinit_cp_data(buf, svc);
   if(!path_append(buf, C_RESPAWN)) return NULL;

   if(stat(buf, &statbuf) == -1) {
      if(errno == ENOENT) {
         svc_set_status(li, CINIT_ST_SH_ONCE);
      } else {
         return NULL;
      }
   } else {
      svc_set_status(li, CINIT_ST_SH_RESPAWN);
   }

   return li;
}
