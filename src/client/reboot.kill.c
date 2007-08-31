/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Reboot the system through a kill call
 */

#include <signal.h>        /* kill()            */

#include "messages.h"      /* MSG_*             */
#include "intern.h"        /* print_errno()     */
#include "signals.h"       /* signals mapping   */

int main()
{
   if(kill(1,SIG_CINIT_REBOOT) == -1) {
      print_errno(MSG_REBOOT_KILL);
      return 1;
   }

   return 0;
}
