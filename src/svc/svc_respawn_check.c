/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Check whether service is existent
 */

#include <stdio.h>      /* NULL        */
#include <limits.h>     /* PATH_MAX    */
#include "svc.h"

/* checking for existence is done before! */
int svc_respawn_check(struct listitem *svc)
{
   char buf[PATH_MAX+1];

   strcpy(buf,svc->abs_path);
   if(!path_append(buf,C_RESPAWN)) return 0
}
