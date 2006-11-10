/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Start the service tree we created
 */

#include <unistd.h>              /* _exit, fork */

#include "cinit.h"            
#include "messages.h"            /* D_PRINTF */
#include "svc.h"                 /* svc_init    */

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

int tree_exec(struct dep *start)
{
   struct dep *tmp;
   
   if(start == NULL) return 1;

   //tmp = start->next;
   tmp = start;

   mini_printf("Test 01\n",1);
   do {
      mini_printf(tmp->svc->abs_path,1);
      mini_printf("\n",1);

//      tmp->svc->pid = fork();


//      if(tmp->svc->pid == -1) return 0;

 //     if(tmp->svc->pid == 0) { /* child code */
  //       execute_sth(tmp->svc->abs_path);
//         _exit(1);
   //   }

      //tmp = tmp->next;
      tmp = tmp->prev;
   } while(tmp != start);
   mini_printf("Test 02\n",1);

   return 1;
}
