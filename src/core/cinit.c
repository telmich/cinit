/* 
 * (c) 2005, 2006 Nico Schottelius (nico-linux at schottelius.org)
 *
 * cinit.c: the main file
 *
 * part of cLinux/cinit
 */

#include <unistd.h>

/* open */
#include <fcntl.h>

/* siggnal */
#include <signal.h>

/* str* */
#include <string.h>

/* sockets */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <stdlib.h>

#include <sys/poll.h>  /* poll */

#include "cinit.h"
#include "ipc.h"

/* global variables */
struct listitem *list;
pid_t cpid;

/***********************************************************************
 * the main procedure
 */

int main(int argc, char **argv)
{
   char  *initdir;

   list = NULL;            /* list of services is empty currently */
   initdir = CINIT_INIT;   /* default init dir */

   cpid = getpid();
   if(cpid != 1) {
      usage(CINIT_VERSION,MSG_USAGE);
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
   
   if( ! cinit_ipc_init() ) {
      
   }

   /* create pipes */
   if(pipe(pfd) == -1) {
      perror(MSG_ERR_PIPE);
      panic();
   }

   /* start init or profile */
   run_init_svc(initdir);

   /* listen for incomming messages */
   /* read pipe */
   
   /* HIER WEITER */
   
   /* free, if we malloc()ed before */
   if(initdir != CINIT_INIT) {
      free(initdir);
   }

   /* wait until we recieved the signal to create the socket */

   /* our life is polling a socket */
   plist.fd = sock;
   plist.events = POLLIN | POLLPRI;
   while(1) {
      if(poll(&plist, 1, -1) != -1) {
         if( (plist.revents & POLLIN)  == POLLIN ||
             (plist.revents & POLLPRI) == POLLPRI) {
            sigio(sock);
         }
      }
   }
}
