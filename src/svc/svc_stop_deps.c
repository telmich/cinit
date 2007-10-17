/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Stop a service, taking care about its dependencies
 */

#include "svc.h"           /* enums             */
#include "svc-intern.h"    /* struct listitem   */

/*
 * how == CINIT_SSSO_COMPLETE => stop needs/wants before
 * how & CINIT_SSSO_WO_NEEDS  => omit needs
 * how & CINIT_SSSO_WO_WANTS  => omit wants
 */

void svc_stop_deps(struct listitem *li, int how)
{
   struct dep *tmp;

   /* shutdown depending services first: needed_by */
   tmp = li->needed_by;
   do {
      if(how & CINIT_SSSO_WO_NEEDS) break;
      svc_stop_deps(tmp->svc, how);
      tmp = tmp->next;
   } while(tmp != li->needed_by);

   /* shutdown depending services first: wanted_by */
   tmp = li->wanted_by;
   do {
      if(how & CINIT_SSSO_WO_WANTS) break;
      svc_stop_deps(tmp->svc, how);
      tmp = tmp->next;
   } while(tmp != li->wanted_by);

   svc_stop(li);
}
