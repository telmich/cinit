/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Pre calculate the service tree
 */

#include "cinit.h"
#include <unistd.h>
#include <string.h>
#include <limits.h>        /* PATH_MAX    */

#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <errno.h>

int gen_svc_tree(char *svc)
{
   char buf[PATH_MAX+1], *p;
   DIR *d_tmp;
   struct dirent *tdirent;

   mini_printf("Service: ",1);
   mini_printf(svc,1);
   mini_printf("\n",1);
   /* only do something if the service is not already known */
   if(svc_known(svc)) return 1;

   /* create a template, so other instances won't try to recreate us */
   if(!svc_create(svc)) return 0;

   /* check needs */
   strcpy(buf,svc);
   if(!path_append(buf,C_NEEDS)) return 0;

   for(p=buf; *p != \'0'; p++) ; /* save current end */

   d_tmp = opendir(buf);
   
   /* if there is no such dir, we are finished */
   if(d_tmp != NULL) {
      if(chdir(buf) == -1) {
         print_errno(buf);
         return 0;
      }

      /* FIXME: problem: relative paths, due to non-chdir */
      while( (tdirent = readdir(d_tmp) ) != NULL) {
         /* ignore . and .. and everything with a . at the beginning */
         if ( *(tdirent->d_name) == '.') continue;

   mini_printf(tdirent->d_name,1);
   mini_printf("\n",1);

         /* skip non-working directories */
         if(!path_absolute(tdirent->d_name,buf,PATH_MAX+1)) continue;

         /* add all needs to our tree (call us recursively) */
         if(!gen_svc_tree(buf)) return 0;
      }
      if(chdir(svc) == -1) {
         print_errno(svc);
         return 0;
      }
      closedir(d_tmp);
   } else {
      if(errno != ENOENT) {
         print_errno(buf);
         return 0;
      }
   }
   /* read service information */
   
   /* check for wants */

   return 1;
}
