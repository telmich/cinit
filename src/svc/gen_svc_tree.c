/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Pre calculate the service tree
 */

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
#include "svc.h"
#include "messages.h"

int gen_svc_tree(char *svc)
{
   struct listitem   *li;

   mini_printf("gen_svc_tree: ",1);
   mini_printf(svc,1);
   mini_printf("\n",1);

   /* only do something if the service is not already known */
   if(svc_known(svc))                  return 1;

   /* create a template, so other instances won't try to recreate us */
   if(!(li=svc_create(svc)))           return 0;

   if(!check_add_deps(li,DEP_NEEDS))   return 0;
   if(!check_add_deps(li,DEP_WANTS))   return 0;

   if(!li->wants && !li->needs) {
      mini_printf("NO: Service has no dependencies, end service\n",1);
   }

   return 1;
}
