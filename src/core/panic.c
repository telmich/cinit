/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-cinit at schottelius.org)
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

   execute_sth(CINIT_PANIC);
   
   /***********************************************************************
    * THIS SHOULD NOT HAPPEN, fallback to hardcoded sulogin
    * (conf/sulogin)
    */
   nargv[0] = SULOGIN;
   nargv[1] = NULL;

   execv(SULOGIN,nargv);

   /* there's nothing todo, if everything fails */
   _exit(1);
}
