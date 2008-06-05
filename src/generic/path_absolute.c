
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
 *    create an absulte path
 *
 */

#include <unistd.h>             /* chdir(),getcwd */
#include <limits.h>             /* PATH_MAX */
#include "intern.h"             /* print_errno */
#include "messages.h"           /* messages */

int path_absolute(char *relpath, char *newpath, size_t size)
{
   char oldpath[PATH_MAX + 1];

   if(!getcwd(oldpath, PATH_MAX + 1)) {
      print_errno(MSG_GETCWD);
      return 0;
   }

   if(chdir(relpath) == -1) {
      print_errno(relpath);
      return 0;
   }

   if(!getcwd(newpath, size)) {
      print_errno(relpath);
      return 0;
   }

   if(chdir(oldpath) == -1) {
      print_errno(oldpath);
      return 0;
   }

   return 1;
}
