/*******************************************************************************
 *
 * 2005-2008 Nico Schottelius (nico-cinit at schottelius.org)
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

#include <unistd.h>           /* getpid,chdir            */
#include <string.h>           /* str(ncmp,len,cpy,cat)   */
#include <stdio.h>            /* perror                  */
#include <stdlib.h>           /* malloc                  */

#include "intern.h"           /* general things          */
#include "messages.h"         /* messages                */
#include "ipc.h"              /* general ipc methods     */
#include "svc-intern.h"       /* gen_svc_tree            */

struct listitem   *svc_list   = NULL;
struct dep        *svc_init   = NULL;
int    svc_lock               = 0;    /* global svc-lock */

int main(int argc, char **argv)
{
   char     *initdir = CINIT_INIT;        /* default init dir        */


   /* Is this really needed?
   pid_t    cpid;

   if(cpid != 1) {
      mini_printf(CINIT_VERSION,2);
      mini_printf(MSG_USAGE,2);
      return 0;
   }*/

   /* Look whether we should start a profile */
   while(argc > 1) {
      if(!strncmp(PROFILE, argv[argc-1], strlen(PROFILE) ) ) {
         initdir = malloc(strlen(CINIT_SVCDIR) +
                          strlen(&argv[argc-1][strlen(PROFILE)]) + 2);
         if(initdir == NULL) {
            panic();
         }
         strcpy(initdir, CINIT_SVCDIR);
         strcat(initdir, SLASH);
         strcat(initdir, &argv[argc-1][strlen(PROFILE)]);
         break;
      }
      --argc;
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
   if(!gen_svc_tree(initdir)) {
      panic();
   }

   /* free, if we malloc()ed before */
   if(strcmp(initdir,CINIT_INIT)) {
      free(initdir);
   }

   /* change to /, so applications have that as cwd, too
    * Is that really seneful? Does that help any application?
    * If not, just for looking nice, that's not a reason to
    * enable it.
   if(chdir(SLASH) == -1) {
      print_errno(SLASH);
      panic();
   } */

   if(!tree_exec(svc_init)) {
      panic();
   }

   while(1) {
      cinit_ipc_listen();
      
      /* check dependency list: perhaps we need to restart something */
      /* implement in cinit-0.3pre14/5 */

      // tree_exec(svc_init);
      // reuse tree_exec()?
      // if(dep) { svc_start() .. ?
   }

   /* OLD:
   if(!cinit_ipc_listen()) {
      panic();
   } */

   /* never reached */
   return 0;
}
