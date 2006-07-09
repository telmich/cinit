/* cinit
 * (c) 2005 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * We are called, when a child dies. Remove it.
 */

#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#include "cinit.h"

/***********************************************************************
 * sig_child
 * collect the children
 * FIXME: check whether we've race conditions when reciieving multiiple
 * signals
 * Perhaps disable listening to sig_child in meantime?
 */

void sig_child(int tmp)
{
   struct listitem *svc;

   do {
      /* check if it's a watched child */
      tmp = waitpid(-1, &tmp, WNOHANG);
      
      /* restart service, if we are watching it */
      svc = list_search_pid((pid_t) tmp);

      if( svc != NULL ) {
         svc->pid = exec_svc(svc->abs_path, CMD_START_SVC);
      }
   } while( tmp > 0);
}
