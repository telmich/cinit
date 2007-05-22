/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    create an absulte path
 */

#include <unistd.h>                 /* chdir(),getcwd       */
#include <limits.h>                 /* PATH_MAX             */
#include "intern.h"                 /* print_errno          */
#include "messages.h"               /* messages             */

int path_absolute(char *relpath, char *newpath, size_t size)
{
   char oldpath[PATH_MAX+1];

   if(!getcwd(oldpath,PATH_MAX+1)) {
      print_errno(MSG_GETCWD);
      return 0;
   }

   if(chdir(relpath) == -1) {
      print_errno(relpath);
      return 0;
   }

   if(!getcwd(newpath,size)) {
      print_errno(relpath);
      return 0;
   }

   if(chdir(oldpath) == -1) {
      print_errno(oldpath);
      return 0;
   }

   return 1;
}
