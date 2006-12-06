/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    check whether file exists and is a file
 */

#include <sys/types.h>     /* FIXME: check headers against posix */
#include <sys/stat.h>
#include <unistd.h>

#include <errno.h>         /* errno                   */
#include "cinit.h"

int file_exists(char *filename)
{
   struct stat buf;
   
   if(stat(filename,&buf) == -1) {
      if(errno == ENOENT) {
         return FE_NOT;
      } else {
         print_errno(filename);
         return FE_ERR;
      }
   } else {
      if(!S_ISREG(buf.st_mode)) {
         return FE_OTHER;
      }
   }

   return FE_FILE;
}
