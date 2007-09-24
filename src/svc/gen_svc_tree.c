/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Pre calculate the service tree
 */

#include <stdlib.h>

#include "intern.h"     /* functions   */
#include "svc.h"        /* constants   */
#include "svc-intern.h" /* functions   */

struct listitem *gen_svc_tree(char *svc)
{
   struct listitem   *li;
   struct dep        *deps;

   /* only do something if the service is not already known */
   if((li=list_search(svc)))           return li;

   /* create a template, so other instances won't try to recreate us */
   if(!(li=svc_create(svc)))           return NULL;

   if(!check_add_deps(li,DEP_NEEDS))   return NULL;
   if(!check_add_deps(li,DEP_WANTS))   return NULL;

   /* no dependencies? then you are a start service */
   if(!li->wants && !li->needs) {
      deps = dep_create(li);
      if(!deps) return NULL;
      dep_entry_add(&svc_init,deps);

      /* Mark it as being in the startup list, so it does not
       * get added again in a dep_needs_wants_add call */
      li->status |= CINIT_ST_IN_LIST;
   }

   return li;
}
