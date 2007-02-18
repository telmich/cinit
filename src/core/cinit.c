/***********************************************************************
 *
 *    2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
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
#include "svc.h"              /* gen_svc_tree            */

struct listitem   *svc_list   = NULL;
struct dep        *svc_init   = NULL;

int main(int argc, char **argv)
{
   char     *initdir = CINIT_INIT;        /* default init dir        */
//   pid_t    cpid;


   /* FIXME: RE-ENABLE as SOON AS PRODUCTIVE cpid = getpid();
    * Is this really needed or should we lock() ourselves?
   if(cpid != 1) {
      mini_printf(CINIT_VERSION,2);
      mini_printf(MSG_USAGE,2);
      return 0;
   }*/

   /* Look whether we should start a profile */
   while(argc > 1) {
      if(!strncmp(PROFILE, argv[argc-1], strlen(PROFILE) ) ) {
         initdir = (char *) malloc(
                              strlen(CINIT_SVCDIR) +
                              strlen(&argv[argc-1][strlen(PROFILE)]) + 2);
         if(initdir == NULL) {
            panic();
         }
         strcpy(initdir, CINIT_SVCDIR);
         strcat(initdir, SLASH);
         strcat(initdir, &argv[argc-1][strlen(PROFILE)]);
         break;
      }
      argc--;
   }

   /* Bootup "logo" */
   mini_printf(MSG_BOOTING,1); mini_printf(initdir,1); mini_printf("\n",1);

   if(chdir(initdir) == -1) {
      print_errno(initdir);
      panic();
   }
   
   /* initialize ipc method */
   if(!cinit_ipc_init()) {
      panic();
   }

   /* listen to signals */
   set_signals(ACT_SERV);

   /* pre-calculate service tree */
   gen_svc_tree(initdir);

   /* free, if we malloc()ed before */
   if(initdir != CINIT_INIT) {
      free(initdir);
   }

   /* start tree from the bottom */
   /* FIXME: use panic() instead? */
   if(!tree_exec(svc_init)) return 1;

   mini_printf("=> cinit started.\n",1);

   /* listen for incomming messages: should never return */
   if(!cinit_ipc_listen()) {
      panic();
   }

   return 0;
}
