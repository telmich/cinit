/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Start the service tree we created
 */

#include <unistd.h>           /* _exit, fork */

#include "cinit.h"
#include "messages.h"
#include "ipc.h"

/* some thoughts...
 *
 * - we already generated the tree, we now need to start it from
 *   the ends
 *
 * - after starting the first service we have to care about SIG_CHILD
 *   to record changes
 *
 *
 *
 *
 *
 *
 *
 *
 *
 */

int tree_exec()
{
   pid_t pid;

   /* leave cinit alone */
   pid = fork();
   
   if(pid == -1) { /* err */
      print_errno(MSG_ERR_FORK);
      return 0;
   } else if(pid == 0) { /* child */
      cinit_ipc_sclose();
      set_signals(ACT_CLIENT);

   if(!cinit_ipc_logon()) _exit(1);

      /* FIXME: open stderr, stdin, stdout to files / syslog / logable ?
       * IMPLEMENT PER SERVICE!
       */
      
      run_svc(cinit_svc);

      _exit(0);   /* nobody cares about us, so exit successfully anyway */
   }
   /* parent exits, we don't care about our children */
   return 1;
}
