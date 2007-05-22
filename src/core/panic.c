/***********************************************************************
 *
 *    2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Execute something 
 */

#include <unistd.h>        /* execv       */

#include "intern.h"
#include "messages.h"

void panic(void)
{
   char *nargv[2];

   if(execute_and_wait(CINIT_PANIC)) _exit(0);
   
   /***********************************************************************
    * THIS SHOULD NOT HAPPEN, fallback to hardcoded sulogin
    * (conf/sulogin)
    */
   nargv[0] = SULOGIN;
   nargv[1] = NULL;

   if(execv(SULOGIN,nargv) == -1) {
      print_errno(MSG_FATAL_PANIC);
   }

   /* there's nothing todo, if everything fails */
   _exit(23);
}
