/* 
 * (c) 2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * main.c
 * main part of cinit
 */

#include <sys/ipc.h>    /* ftok */
#include <sys/msg.h>    /* msgget */
#include <stdio.h>      /* perror */
#include <stdlib.h>     /* exit */

#include "cinit.h"

/* global variables */
struct listitem *list;
pid_t cpid;

/***********************************************************************
 * the main procedure
 */

int main(int argc, char **argv)
{
   char     *initdir;
   key_t    msg_key;
   int      msq_id;

   initdir  = CINIT_INIT;  /* default init dir                       */
   list     = NULL;        /* list of services is empty currently    */
   cpid     = getpid();    /* no comment                             */

   if(cpid != 1) {
      usage(CINIT_VERSION,MSG_USAGE);
   }

   /* set signal handlers */
   set_signals(ACT_SERV);

   /* read arguments, profile support */
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

   /* create message queues */

   /* start init or profile */
   run_init_svc(initdir);

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
