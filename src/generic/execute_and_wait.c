/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Execute something, but fork() before
 *
 */

#include <sys/types.h>     /* pid_t       */
#include <sys/wait.h>      /* waitpid     */
#include <unistd.h>        /* fork        */
#include "messages.h"      /* MSG_*       */
#include "cinit.h"         /* print_errno, execute_sth */

int execute_and_wait(char *svc)
{
   pid_t pid;
   int status;

   /* fork */
   pid = fork();
   
   if(pid == -1) {
      print_errno(MSG_ERR_FORK);
      return 0;
   }

   /* exec / child */
   if(pid == 0) {
      execute_sth(svc); /* exits itself */
   }

   /* wait / parent */
   waitpid(pid,&status,0);

   if(WIFEXITED(status)) {
      if(WEXITSTATUS(status) == 0) {
         return 1;
      }
   }
   return 0;
}
