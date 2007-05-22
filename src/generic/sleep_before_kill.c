/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Sleep:
 *       read configuration,
 *       fallback to builtin value if not possible,
 *       sleep.
 *
 */

#include <time.h>             /* nanosleep      */
#include <stdlib.h>           /* strtol()       */
#include <errno.h>            /* errno          */

#include "intern.h"           /* print_errno    */
#include "messages.h"         /* messages       */

void sleep_before_kill()
{
   char              *content;
   int               tmp;
   struct timespec   ts;

   if(openreadclose(CINIT_SLEEPFILE,&content) == ORC_OK) {
      errno = 0;
      tmp   = strtol(content, NULL, 10);
      if(errno != 0) tmp = SLEEP_KILL;
      free(content);
   } else {
      mini_printf(MSG_BUILTIN_SLEEP,1);
      tmp = SLEEP_KILL;
   }

   ts.tv_sec   = tmp;
   ts.tv_nsec  = 0;
 
   if(nanosleep(&ts,NULL) == -1) {
      print_errno(MSG_ERR_SLEEP);
   }
}
