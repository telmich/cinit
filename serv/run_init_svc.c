/* 
 * cinit
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * run initial service
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

   /* leave cinit alone */
   pid = fork();
   
   if(pid == -1) { /* err */
      perror(MSG_ERR_FORK);
      return 0;
   } else if(pid == 0) { /* child */
      close(sock);
      set_signals(ACT_CLIENT);
      /* FIXME: open stderr, stdin, stdout to files / syslog / logable ?*/
      if ( run_svc(cinit_svc) >= RT_SUCCESS )
         _exit(0);
      else
         _exit(1);
   }
   /* parent exits, we don't care about our children */
   return 1;
}
/* ready for cinit-0.2 */
