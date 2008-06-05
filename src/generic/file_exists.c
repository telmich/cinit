
/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    check whether file exists and is a file
 */

#include <errno.h>              /* errno */
#include <sys/stat.h>           /* stat */
#include <stdio.h>              /* NULL */

#include "intern.h"             /* print_errno() */
#include "svc-intern.h"         /* svc_report_status() */
#include "messages.h"           /* messages..  */

int file_exists(char *filename)
{
   struct stat buf;

   /*
    * check: - is it a link? if so, is it broken? report! - is it non existent? 
    * -> return non-existent - is it existent, but not a regular file? report! 
    */
   if(lstat(filename, &buf) == -1) {    /* lstat fails? */
      if(errno == ENOENT) {
         /*
          * FIXME: remove later 
          */
         printf("%s is not existing! => ok, most likely\n", filename);
         return FE_NOT;
      } else {
         mini_printf("anderer fehler.\n", 1);
         print_errno(filename);
         return FE_ERR;
      }
   } else {
      if(S_ISLNK(buf.st_mode)) {        /* is a link */
         /*
          * check link destination 
          */
         if(stat(filename, &buf) == -1) {       /* do real stat(): */
            if(errno == ENOENT) {
               svc_report_status(filename, MSG_BROKENLINK, NULL);
               return FE_NOLINK;
            } else {
               /*
                * FIXME: MSG_*, ?? 
                */
               mini_printf("anderer fehler.\n", 1);
               print_errno(filename);
               return FE_ERR;
            }
         }
      }
   }                            /* caught all stat() errors */

   if(!S_ISREG(buf.st_mode)) {
      svc_report_status(filename, MSG_NONREGULAR, NULL);
      return FE_OTHER;
   }

   return FE_FILE;
}
