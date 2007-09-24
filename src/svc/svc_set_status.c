/***********************************************************************
 *
 *    2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Set the status of a service
 */

#include "svc-intern.h"

/* checking for existence is done before! */
int svc_set_status(struct listitem *li, int status)
{
   /* FIXME: also set time? */

   return (li->status = status);
}
