/*******************************************************************************
 *
 * 2005-2009 Nico Schottelius (nico-cinit at schottelius.org)
 *
 * This file is part of cinit.

 * cinit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cinit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cinit.  If not, see <http://www.gnu.org/licenses/>.

 *
 *    The main file
 *
 */

#include <unistd.h>             /* getpid,chdir */
#include <string.h>             /* str(ncmp,len,cpy,cat) */
#include <stdio.h>              /* perror */
#include <stdlib.h>             /* malloc */
#include <signal.h>             /* struct sigaction */

#include "intern.h"             /* general things */
#include "messages.h"           /* messages */
#include "ipc.h"                /* general ipc methods */
#include "svc-intern.h"         /* gen_svc_tree */
#include "signals.h"            /* signals used by cinit */

struct listitem  *svc_list = NULL;  /* services in a dependency tree    */
struct dep       *deps_pending = NULL;  /* the first services to be started */
int               svc_exited;       /* did some service exit?           */

struct sigaction  sigstages[SIGSTAGE_END][SIGCINIT_END];
int               cinit_global_signals[SIGCINIT_END];

int main(int argc, char **argv)
{
   char *initdir = CINIT_INIT;  /* default init dir */

   /*
    * Is this really needed? pid_t cpid;
    * 
    * if(cpid != 1) { mini_printf(CINIT_VERSION,2); mini_printf(MSG_USAGE,2);
    * return 0; }
    */

   /* Bootup "logo" */
   mini_printf(MSG_BOOTING, 1); mini_printf(initdir, 1); mini_printf("\n", 1);

   /* Should we start a profile? */
   while(argc > 1) {
      if(!strncmp(PROFILE, argv[argc - 1], strlen(PROFILE))) {
         initdir = malloc(strlen(CINIT_SVCDIR) +
                          strlen(&argv[argc - 1][strlen(PROFILE)]) + 2);
         if(initdir == NULL) {
            panic();
         }
         strcpy(initdir, CINIT_SVCDIR);
         strcat(initdir, SLASH);
         strcat(initdir, &argv[argc - 1][strlen(PROFILE)]);
         break;
      }
      --argc;
   }

   /* no configuration? - panic! */
   if(chdir(initdir) == -1) {
      print_errno(initdir);
      panic();
   }

   /* initialize communication (IPC) */
   if(!cinit_ipc_init()) panic();

   /* Init signal handler */
   signal_init_map(sigstages, cinit_global_signals);
   set_signals(SIGSTAGE_DAEMON);

   /* build service dependency tree */
   if(!gen_svc_tree(initdir)) panic();

   /* unused now, free if allocated */
   if(strcmp(initdir, CINIT_INIT)) free(initdir);

   /* FIXME: what todo?
    * change to /, so applications have that as cwd, too Is that really
    * seneful? Does that help any application? If not, just for looking nice,
    * that's not a reason to enable it. if(chdir(SLASH) == -1) {
    * print_errno(SLASH); panic(); } 
    */

   /* the main startup routine */
   if(!tree_exec(deps_pending)) panic();

   /* listen to commands after startup */
   while(1) {
      /* react on service changes (=process exited) */
      if(svc_exited) svc_status_changed(deps_pending);

      /* handle the changes */
      if(deps_pending) svc_handle_pending(deps_pending);

      /* listen until we get a message or get interrupted */
      cinit_ipc_listen();

      /*
       * check dependency list: perhaps we need to restart something 
       */
      /*
       * implement in cinit-0.3pre14/5 
       */

      // tree_exec(deps_pending);
      // reuse tree_exec()?
      // if(dep) { svc_start() .. ?
   }

   return 0;
}
