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

int gen_svc_tree(char *svc)
{
   char buf[PATH_MAX+1];
   DIR *d_tmp;
   struct dirent *tdirent;
   char pathbuf[PATH_MAX+1];
   pid_t pids[MAX_DEPS];
   int status, i, ret = 1;

   /* only do something if the service is not already known */
   if(svc_known(svc)) return 1;

   /* create a template, so other instances won't try to recreate us */

   strcpy(buf,svc);
   if(!path_append(buf,C_NEEDS)) return 0;

   /* open needs */
   d_tmp = opendir(abspath);
   
   /* if there is no such dir, we are finished */
   if(d_tmp != NULL) {
   
      while( (tdirent = readdir(d_tmp) ) != NULL) {
         /* ignore . and .. and everything with a . at the beginning */
         if ( *(tdirent->d_name) == '.') continue;

      if(pids[i] == 0) { /* child */
         strcpy(pathbuf,abspath);
         strcat(pathbuf,SLASH);
         strcat(pathbuf,tdirent->d_name);
         if ( run_svc(pathbuf) )
            _exit(0);
         else
            _exit(1);
      } else { /* parent */
         ++i;
      }
   }

   closedir(d_tmp);
   
   /* wait for pids */
   --i; /* the index is one too much since last i++ */
   while(i >= 0) {
      waitpid(pids[i], &status, 0);

      /* if anything failed, we failed */
      if( ! WIFEXITED(status)) {
         ret = 0;
      } else {
         if( WEXITSTATUS(status) ) {
            ret = 0;
         }
      }
      --i;
   }
   return ret;

   /* check for needs */
   /* 
    * create_path_needs()
    * opendir()
    *    skip .*
    * chdir()
    *    warn about broken links!
    * gen_svc_tree(need)
    */

   /* check for wants */

   return 1;
}
