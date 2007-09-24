/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Return whether should respawn or not
 */

#include "svc-intern.h"
#include "svc.h"

/* checking for existence is done before! */
int svc_should_respawn(struct listitem *li)
{
   return (li->status & CINIT_ST_SH_RESPAWN);
}
