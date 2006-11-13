/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Set the status of a service
 */

#include "svc.h"

/* checking for existence is done before! */
int svc_set_status(struct listitem *li, int status)
{
   return (li->status = status);
}
