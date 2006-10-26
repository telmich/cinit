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

#include "cinit.h"            /* general things          */
#include "messages.h"         /* messages                */
#include "ipc.h"              /* general ipc methods     */

struct listitem *list;
pid_t cpid;

int main(int argc, char **argv)
{
   char  *initdir;

   list     = NULL;              /* empty list of services  */
   initdir  = CINIT_INIT;        /* default init dir        */

   /* FIXME: RE-ENABLE as SOON AS PRODUCTIVE cpid = getpid();
   if(cpid != 1) {
      mini_printf(CINIT_VERSION,2);
      mini_printf(MSG_USAGE,2);
      return 0;
   }*/

   set_signals(ACT_SERV);

   /* Look whether we should start a profile */
   while(argc > 1) {
      if( !strncmp(PROFILE, argv[argc-1], strlen(PROFILE)) ) {
         initdir = (char *) malloc(
                              strlen(CINIT_SVCDIR) +
                              strlen(&argv[argc-1][strlen(PROFILE)]) + 2
                              );
         if(initdir == NULL) {
            panic();
         }
         strcpy(initdir,CINIT_SVCDIR);
         strcat(initdir,SLASH);
         strcat(initdir,&argv[argc-1][strlen(PROFILE)]);
         break;
      }
      argc--;
   }

   /* FIXME: do we really need three calls? */
   mini_printf(MSG_BOOTING,1); mini_printf(initdir,1); mini_printf("\n",1);

   if(chdir(initdir) == -1) {
      print_errno(initdir);
      panic();
   }
   
   /* initialize ipc method */
   if(!cinit_ipc_init()) {
      panic();
   }

   /* pre-calculate service tree */
   gen_svc_tree(initdir);

   mini_printf("test\n",1);

   /* start init or profile */
   run_init_svc(initdir);

   /* free, if we malloc()ed before */
   if(initdir != CINIT_INIT) {
      free(initdir);
   }

   /* listen for incomming messages: should never return */
   if(!cinit_ipc_listen()) {
      panic();
   }
   return 0;
}
