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
#include <limits.h>        /* PATH_MAX    */

int gen_svc_tree(char *start)
{
   char buf[PATH_MAX+1];

   /* only do something if the service is not already known */
   if(svc_known(start)) return 1;

   /* check for needs */
   /* start (+ SLASH) + needs */
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
