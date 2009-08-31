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
 *    Add dependencies to a service
 */

#include <unistd.h>              /* getcwd      */

#include <dirent.h>              /* DIR         */
#include <errno.h>               /* errno       */

#include <limits.h>              /* PATH_MAX    */
#include <stdlib.h>              /* malloc      */
#include <string.h>              /* strcpy      */

#include "intern.h"              /* mini_printf */
#include "messages.h"            /* MSG_*       */
#include "svc-intern.h"          /* DEP_*       */

int check_add_deps(struct listitem *svc, int type)
{
   char buf[PATH_MAX + 1];
   char oldpath[PATH_MAX + 1];
   struct dirent *tdirent;
   struct dep *deps = NULL;
   struct listitem *new_svc;
   DIR *d_tmp;

   /* remember where we started */
   if(!getcwd(oldpath, PATH_MAX + 1)) {
      print_errno(MSG_GETCWD);
      return 0;
   }

   /* Create path */
   strncpy(buf, svc->abs_path, PATH_MAX+1);
   if(type == DEP_NEEDS) {
      if(!path_append(buf, C_NEEDS)) return 0;
   } else {
      if(!path_append(buf, C_WANTS)) return 0;
   }

   d_tmp = opendir(buf);
   if(d_tmp == NULL) {
      if(errno != ENOENT) {
         print_errno(buf);
         return 0;
      }
      return 1;                 /* it's fine when there's no dependencies */
   }

   if(chdir(buf) == -1) {       /* change to needs or wants */
      print_errno(buf);
      return 0;
   }

   while((tdirent = readdir(d_tmp)) != NULL) {
      if(*(tdirent->d_name) == '.') continue;              /* ignore .* */

      /*
       * skip non-working directories / broken links path_absolute reports
       * errors on failure 
       */
      if(!path_absolute(tdirent->d_name, buf, PATH_MAX + 1)) continue;

      /* 1. create the service we depend on 2. initialize its dependencies */
      if(!(new_svc = gen_svc_tree(buf))) return 0;

      /*
       * We need ALL dependencies, as we are called only once per service; no
       * need to test that first! And the other service CANNOT know anything
       * about us yet, so we always add us to its list. 
       */

      /*
       * Dependencies: - a.needs b; add b to the list of dependencies. -
       * a.needs b; add a to the list of needed by b. 1. check whether the
       * dependency already exists 2. otherwise add it 3. do it once for needs, 
       * once for needed_by 
       */

      /* create a dependency entry containing us */
      deps = dep_create(svc);
      if(!deps) return 0;

      if(type == DEP_NEEDS) {
         /* add us to the other service */
         dep_entry_add(&(new_svc->needed_by), deps);

         /* add other service to us */
         deps = dep_create(new_svc);
         if(!deps) return 0;
         dep_entry_add(&(svc->needs), deps);
      } else {
         /* add us to the other service */
         dep_entry_add(&(new_svc->wanted_by), deps);

         /* add other service to us */
         deps = dep_create(new_svc);
         if(!deps) return 0;
         dep_entry_add(&(svc->wants), deps);
      }
   }
   if(chdir(oldpath) == -1) {
      print_errno(buf);
      return 0;
   }
   closedir(d_tmp);

   return 1;
}
