/* cinit
 * (c) 2005 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * We are called, when a child dies. Remove it.
 */

#include <sys/types.h>
#include <sys/wait.h>

#include "cinit.h"

/***********************************************************************
 * sig_child
 * collect the children
 */

void sig_child(int tmp)
{
   struct listitem *svc;

   do {
      /* check if it's a watched child */
      tmp = waitpid(-1,&tmp,WNOHANG);
      
      /* restart service, if we are watching it */
      svc = list_search_pid((pid_t) tmp);

      if( svc ) {
         svc->pid = exec_svc(svc->abs_path, CMD_START_SVC);
      }
   } while( signal > 0);
}
