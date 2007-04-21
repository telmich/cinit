/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    check whether file exists and is a file
 */

#include <errno.h>         /* errno                   */
#include <sys/stat.h>      /* stat                    */
#include <stdio.h>         /* NULL                    */
#include "cinit.h"         /* print_errno()           */
#include "svc.h"           /* svc_report_status()     */
#include "messages.h"      /* messages..              */

int file_exists(char *filename)
{
   struct stat buf;

   mini_printf("FE: ",1);
   mini_printf(filename,1);
   mini_printf("\n",1);
   
   /* check:
    * - is it a link? if so, is it broken? report!
    * - is it non existent? -> return non-existent
    * - is it existent, but not a regular file? report!
    */
   if(lstat(filename,&buf) == -1) {                /* lstat fails? */
      if(errno == ENOENT) {
         mini_printf("NIX DA: ok.\n",1);
         return FE_NOT;
      } else {
         mini_printf("anderer fehler.\n",1);
         print_errno(filename);
         return FE_ERR;
      }
   } else {
      if(S_ISLNK(buf.st_mode)) {                   /* is a link */
         mini_printf("ist nen link\n",1);
         
         /* check link destination */
         if(stat(filename,&buf) == -1) {           /* do real stat(): */
            if(errno == ENOENT) {
               svc_report_status(filename,MSG_BROKENLINK,NULL);
               return FE_NOLINK;
            } else {
               mini_printf("anderer fehler.\n",1);
               print_errno(filename);
               return FE_ERR;
            }
         }
      }
   } /* caught all stat() errors */

   if(!S_ISREG(buf.st_mode)) {
      svc_report_status(filename,MSG_NONREGULAR,NULL);
      return FE_OTHER;
   }

   return FE_FILE;
}
