/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
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

   if( ( tmp = cinit_build_argv(file,&cargv) ) != BA_OK) {
      if(tmp != BA_E_MEM) {
         perror("fehler:");
         exit(1);
      }
   }

   execve((cargv.argv)[0],cargv.argv,cargv.envp);

   return 1;
}
