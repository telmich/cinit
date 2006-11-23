/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Executes something: replaces us
 */

#include <unistd.h>              /* _exit                */
#include "cinit.h"
#include "build_argv.h"

void execute_sth(char *basename)
{
   int            tmp;
   struct ba_argv bav;
   
   mini_printf("ES::",1);
   mini_printf(basename,1);
   mini_printf("\n",1);

   tmp = cinit_build_argv(basename,&bav);
   if((tmp = cinit_build_argv(basename,&bav)) != BA_OK) {
      if(tmp != BA_E_MEM) {
         print_errno(basename);
      } /* do not print something on memory errors */
      _exit(1);   /* FIXME: adjust exit code? */
   }

   execve((bav.argv)[0],bav.argv,bav.envp);
   print_errno(basename);
   _exit(1);    /* FIXME: return specific error code, so cinit knows
                            * what happened! - sure? perhaps this gets non
                            * standard errors from other programs, too ... */
}
