/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    This function reads the full service tree and generates
 *    a list of services to begin shutdown (those that are not
 *    wanted or needed by any other service).
 */

#include <stdio.h>         /* NULL        */

#include "svc.h"           /* structs     */
#include "intern.h"        /* structs     */

struct dep *gen_halt_list(struct listitem *svc_tree)
{
   struct dep        *list = NULL, *new = NULL;
   struct listitem   *tmp;

   /* no tree? nothing to shutdown. */
   if(!svc_tree) {
      return NULL;
   }

   /* find all services that do not depend on other services:
    * - empty wants? (currently ignore them)
    * - empty needs!
    */
   tmp = svc_tree;
   do {
      if(tmp->needs == NULL) {
         /* create new dependency */
         new = dep_create(tmp);
         if(!new) return NULL;

         dep_entry_add(&list,new);
      }
      tmp = tmp->next;
   } while(tmp != svc_tree);
   
   return list;
}
