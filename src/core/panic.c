/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Execute something 
 */

#include "cinit.h"
#include <unistd.h>

void panic(void)
{
   char *nargv[2];
   
   /* USE execute_something but do NOT fork it, but let us replace */
   nargv[0] = SULOGIN;
   nargv[1] = NULL;

   execv(SULOGIN,nargv);
   _exit(1);
}
