/* 
 * cinit
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * We are called, when a child dies. Remove it.
 */

#include <sys/types.h>
#include <sys/wait.h>

#include "cinit.h"

/***********************************************************************
 * sig_child
 * collect the children
 */

void sig_child(int signal)
{
   mini_printf("sigchild\n",1);
   do {
      signal = waitpid(-1,&signal,WNOHANG);
   } while( signal > 0);
}
