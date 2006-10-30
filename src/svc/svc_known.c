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

int svc_known(char *svc)
{
   return (list_search(svc) != NULL) ? 1 : 0;
}
