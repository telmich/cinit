
/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    run initial service(s)
 */

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>

#include "cinit.h"

#include <time.h>

/*********************************************************************** 
 * start the first service
 */

int run_init_svc(char *cinit_svc)
{
   pid_t pid;

   /*
    * leave cinit alone 
    */
   pid = fork();

   if(pid == -1) {              /* err */
      print_errno(MSG_ERR_FORK);
      return 0;
   } else if(pid == 0) {        /* child */
      cinit_ipc_sclose();
      set_signals(ACT_CLIENT);

      /*
       * FIXME: open stderr, stdin, stdout to files / syslog / logable ?
       * IMPLEMENT PER SERVICE! 
       */

      run_svc(cinit_svc);

      _exit(0);                 /* nobody cares about us, so exit successfully
                                 * anyway */
   }
   /*
    * parent exits, we don't care about our children 
    */
   return 1;
}

/* ready for cinit-0.2 */
