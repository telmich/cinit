
/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    test build_argv
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "build_argv.h"

int main()
{
   char *file = "./test_exec";
   struct ba_argv cargv;
   int tmp;

   if((tmp = cinit_build_argv(file, &cargv)) != BA_OK) {
      if(tmp != BA_E_MEM) {
         perror("fehler:");
         exit(24);
      } else
         exit(23);
   }

   printf("code: %s\n", cargv.argv[0]);
   execve((cargv.argv)[0], cargv.argv, cargv.envp);

   perror("execve");

   return 1;
}
