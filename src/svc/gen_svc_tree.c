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

int gen_svc_tree(char *svc)
{
   char buf[PATH_MAX+1];
   DIR *dir;

   /* only do something if the service is not already known */
   if(svc_known(svc)) return 1;

   strcpy(buf,svc);
   if(!path_append(buf,C_NEEDS)) return 0;

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
