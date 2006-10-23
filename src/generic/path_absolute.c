/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    create an absulte path
 */

#include <unistd.h>                 /* chdir(),getcwd       */
#include "cinit.h"                  /* print_errno          */

int path_absolute(char *relpath, char *newpath, size_t size)
{
   if(chdir(relpath) == -1) {
      print_errno(relpath);
      return 0;
   }

   if(!getcwd(newpath,size)) {
      print_errno(relpath);
      return 0;
   }

   return 1;
}
