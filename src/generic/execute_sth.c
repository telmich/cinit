
/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Executes something: replaces us
 */

#include <unistd.h>             /* _exit */

#include "intern.h"
#include "build_argv.h"
#include "messages.h"           /* D_PRINTF */

void execute_sth(char *basename)
{
   int tmp;
   struct ba_argv bav;

   tmp = cinit_build_argv(basename, &bav);
   if((tmp = cinit_build_argv(basename, &bav)) != BA_OK) {
      if(tmp != BA_E_MEM) {     /* do not print something on memory errors */
         print_errno(basename);
      }
      _exit(1);
   }

   /*
    * tell the user what we execute 
    */
   mini_printf(MSG_INTRO_EXEC, 1);
   mini_printf((bav.argv)[0], 1);
   mini_printf("\n", 1);

   execve((bav.argv)[0], bav.argv, bav.envp);
   print_errno(basename);
   _exit(1);                    /* simply exit non-zero. That's enough for
                                 * cinit to recognize it as faulty */
}
