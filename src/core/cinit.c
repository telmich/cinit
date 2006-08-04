/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    The main file
 *
 */

#include <unistd.h>           /* getpid,chdir            */
#include <string.h>           /* str(ncmp,len,cpy,cat)   */
#include <stdio.h>            /* perror                  */
#include <stdlib.h>           /* malloc                  */

#include "cinit.h"
#include "messages.h"
#include "ipc.h"

struct listitem *list;
pid_t cpid;

int main(int argc, char **argv)
{
   char  *initdir;

   list     = NULL;              /* empty list of services  */
   initdir  = CINIT_INIT;        /* default init dir        */

   cpid = getpid();
   if(cpid != 1) {
      mini_printf(CINIT_VERSION,2);
      mini_printf(MSG_USAGE,2);
      return 0;
   }

   set_signals(ACT_SERV);

   /* read args, profile support */
   while(argc > 1) {
      if( !strncmp(PROFILE, argv[argc-1], strlen(PROFILE)) ) {
         initdir = (char *) malloc(
                              strlen(CINIT_DIR) +
                              strlen(&argv[argc-1][strlen(PROFILE)]) + 2
                              );
         if(initdir == NULL) {
            panic();
         }
         strcpy(initdir,CINIT_DIR);
         strcat(initdir,SLASH);
         strcat(initdir,&argv[argc-1][strlen(PROFILE)]);
         break;
      }
      argc--;
   }

   /* tell the world we are there FIXME: do we really need three calls? */
   mini_printf(MSG_BOOTING,1); mini_printf(initdir,1); mini_printf("\n",1);

   if(chdir(CINIT_INIT) == -1) {
      perror(MSG_CHDIR);
      panic();
   }
   
   if(!cinit_ipc_init()) {
      panic();
   }

   /* start init or profile */
   run_init_svc(initdir);

   /* listen for incomming messages */
   
   /* free, if we malloc()ed before */
   if(initdir != CINIT_INIT) {
      free(initdir);
   }

   return 0;      /* gcc wants that, we not :( */
}
