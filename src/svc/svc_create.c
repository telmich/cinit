/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Check whether service is existent
 */

#include <stdio.h>      /* NULL */
#include "svc.h"

int svc_create(char *svc)
{
   /* status is currently -1 -> unset */
   /* FIXME: do NOT use list_insert, as it does not
    * check whether the service already exists!
    *
    * Is that really an issue? We are most likely only called
    * from gen_svc_tree, which checks before...
    */

   return list_insert(svc,-1);
}
