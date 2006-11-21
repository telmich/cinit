/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Pre calculate the service tree
 */

#include <stdlib.h>
#include "cinit.h"
#include "svc.h"

struct listitem *gen_svc_tree(char *svc)
{
   struct listitem   *li;
   struct dep        *deps;

   /* only do something if the service is not already known */
   if((li=list_search(svc)))  return li;

   /* create a template, so other instances won't try to recreate us */
   if(!(li=svc_create(svc)))  return NULL;

   /* FIXME: remove debug */
   mini_printf("gen_tree::",1);
   mini_printf(svc,1);
   mini_printf("\n",1);

   if(!check_add_deps(li,DEP_NEEDS))   return NULL;
   if(!check_add_deps(li,DEP_WANTS))   return NULL;

   if(!li->wants && !li->needs) {
      /* FIXME: remove debug */
      mini_printf("START::",1);
      mini_printf(li->abs_path,1);
      mini_printf("\n",1);

      deps = dep_create(li);
      if(!deps) return NULL;
      dep_entry_add(&svc_init,deps);

      /* mark it as being in _THE_ list */
      li->status |= ST_IN_LIST;
   }

   return li;
}
