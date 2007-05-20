/* 
 * cinit
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * run services parallel
 */
#include <sys/types.h>
#include <sys/wait.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <limits.h>

#include "cinit.h"


/*********************************************************************** 
 * parallel run forked() run_svc()
 */

int run_run_svcs(char *abspath)
{
   DIR *d_tmp = NULL;
   struct dirent *tdirent;
   char pathbuf[PATH_MAX+1];
   pid_t pids[MAX_DEPS];
   int status, i, ret = 1;

   D_PRINTF(abspath);

   d_tmp = opendir(abspath);
   
   /* if there is no such dir, we are finished */
   if(d_tmp == NULL) {
      return 1;
   }
   
   i = 0;
   while( (tdirent = readdir(d_tmp) ) != NULL) {
      /* ignore . and .. and everything with a . at the beginning */
      if ( *(tdirent->d_name) == '.') continue;

      if(i < MAX_DEPS) {
         pids[i] = fork();
      } else {
         LOG(MSG_ERR_DEPS);
         break;
      }

      if(pids[i] == -1) { /* err */
         perror(MSG_ERR_FORK);
         return 0;
      }

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
}
