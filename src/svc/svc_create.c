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

/* checking for existence is done before! */
struct listitem *svc_create(char *svc)
{
   return list_insert(svc,-1);
}
