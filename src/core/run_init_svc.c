/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    run initial service(s)
 */

#include <unistd.h>           /* _exit, fork */

#include "cinit.h"
#include "messages.h"
#include "ipc.h"

int run_svc(char *rpath) { rpath = "test"; return 0; }  /* a hack to compile cinit for now */

int run_init_svc(char *cinit_svc)
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
/* ready for cinit-0.2 */
