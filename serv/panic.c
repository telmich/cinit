/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * panic: if cinit fails, start sulogin
 * part of cinit
 */

#include "cinit.h"
#include <unistd.h>

void panic(void)
{
   char *nargv[2];

   nargv[0] = SULOGIN;
   nargv[1] = NULL;

   execv(SULOGIN,nargv);
   _exit(1);
}
