/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Start the service tree we created
 */

#include <unistd.h>           /* _exit, fork */

//#include "cinit.h"            /* svc_init    */
#include "svc.h"              /* svc_init    */

/* some thoughts...
 *
 * - we already generated the tree, we now need to start it from
 *   the ends
 *
 * - after starting the first service we have to care about SIG_CHILD
 *   to record changes
 *
 * - we execute all services in parallel without problems, because of
 *   SIG_CHILD notification
 * 
 * - After successfully starting the service we start the service that
 *   need or want that service
 *
 *
 *
 */

int tree_exec()
{
   struct dep *begin = svc_init->next;
   
   while(begin != svc_init) {
      begin->svc->pid = fork();

      if(begin->svc->pid == -1) return 0;

      if(begin->svc->pid == 0) { /* child code */
         execute_sth(begin->svc->name);
      }

      
      begin = begin->next;
   }

   return 1;
}
