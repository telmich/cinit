/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * run_svc
 * part of cinit
 */

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>


#include "cinit.h"

/* run a service, gets (relative or absolute) path */
pid_t respawn_svc(char *abspath)
{
   pid_t pid;
   int tmp;
   int pipefd[2];
   struct sigaction sa;
   char delay[PATH_MAX+1];
   
   D_PRINTF(abspath);

   if(pipe(pipefd) == -1) {
      perror(MSG_ERR_PIPE);
      return 0;
   }
      
   pid = fork();
   if(pid == -1) {
      perror(MSG_ERR_FORK);
      return 0;
   }

   /******************** PARENT ********************/
   if(pid > 0) {
      /* if we read anything, our child succeded */
      if( read(pipefd[0],&tmp,sizeof(tmp)) == -1) {
         perror(MSG_ERR_IO);
         return 0;
      }
      return pid; /* return watchers pid */
   }

   /****************** CHILD: Service watcher ********************/
   sa.sa_handler = sig_terminate;
   sigaction(SIGTERM,&sa,NULL);      /* term = kill respawing process */
   /* sigterm handler should kill first our watching pid, reset the
   pid to 0 and then we'll kill ourselves */
   
   tmp = 1;
   if( write(pipefd[1],&tmp,sizeof(tmp)) == -1) {
      perror(MSG_ERR_IO);
      _exit(1);
   }

   /* try to read delay into sock */
   strcpy(delay,abspath);
   strcat(delay,SLASH);
   strcat(delay,C_DELAY);

   /* reuse sock to specify delay */
   sock = -1;
   tmp = open(delay,O_RDONLY);
   if(tmp != -1) {
      pipefd[0] = read(tmp,&delay[0],PATH_MAX);
      if(pipefd[0] > 0 && pipefd[0] <= PATH_MAX) {
         delay[pipefd[0]] = 0;
         sock = atoi(delay);
      }
      close(tmp);
   }
   
   do {
      /* exec_svc will set cpid accordingly */
      if( ! exec_svc(abspath, CMD_START_SVC) ) {
         if(cpid != 0) {
            D_PRINTF("sloefen");
            sleep(SLEEP_SVC);
            D_PRINTF("Zuende geschlafen");
         }
      }
   } while( cpid ); /* cpid is reset by sig_terminate() */

   /* FIXME: put most code of sig_terminate here, look for no_kill */

   /* start off task */
   exec_svc(abspath,CMD_STOP_SVC);

   D_PRINTF("jetzt weg");
   _exit(0);
}
