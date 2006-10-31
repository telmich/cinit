/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Pre calculate the service tree
 */

/* FIXME: clean headers */
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

#include "cinit.h"
#include "messages.h"
#include "svc.h"

int check_add_deps(char *svc,int type)
{
   char buf[PATH_MAX+1];
   char oldpath[PATH_MAX+1];
   DIR *d_tmp;
   struct dirent *tdirent;

   /* remember where we are */
   if(!getcwd(oldpath,PATH_MAX+1)) {
      print_errno(MSG_CHDIR);
      return 0;
   }

   /* Create path */
   strcpy(buf,svc);
   if(type == DEP_NEEDS) {
      if(!path_append(buf,C_NEEDS)) return 0;
   } else {
      if(!path_append(buf,C_WANTS)) return 0;
   }

   d_tmp = opendir(buf);
   if(d_tmp == NULL) {
      if(errno != ENOENT) {
         print_errno(buf);
         return 0;
      }
      return 1;   /* it's fine when there's no needs */
   }
   if(chdir(buf) == -1) { /* change to needs or wants */
      print_errno(buf);
      return 0;
   }

   while( (tdirent = readdir(d_tmp) ) != NULL) {
      /* ignore . and .. and everything with a . at the beginning */
      if ( *(tdirent->d_name) == '.') continue;

      /* skip non-working directories */
      if(!path_absolute(tdirent->d_name,buf,PATH_MAX+1)) continue;

      /* FIXME: Debug */
      mini_printf("cad::",1);
      mini_printf(tdirent->d_name,1);
      mini_printf(" :: ",1);
      mini_printf(buf,1);
      mini_printf("\n",1);

      /* add dependencies of the new service */
      if(!gen_svc_tree(buf)) return 0;

      /* now add to our list */
   }
   if(chdir(oldpath) == -1) {
      print_errno(buf);
      return 0;
   }
   closedir(d_tmp);

   return 1;
}
