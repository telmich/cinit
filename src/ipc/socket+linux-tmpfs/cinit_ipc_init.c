/* 
 * (c) 2005, 2006 Nico Schottelius (nico-linux at schottelius.org)
 * cinit.c
 * part of cLinux/cinit
 */

/* *stat() */
#include <sys/stat.h>
#include <unistd.h>

/* open */
#include <fcntl.h>

/* siggnal */
#include <signal.h>

/* PATH_MAX */
#include <limits.h>

/* str* */
#include <string.h>

/* sockets */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <stdio.h>
#include <stdlib.h>

#include "cinit.h"

/***********************************************************************
 * create a socket, when we recieved a signal
 */
int main(int argc, char **argv)
{
   struct sockaddr_un addr;
   struct pollfd plist;
   char  *initdir;

   list = NULL;            /* list of services is empty currently */
   initdir = CINIT_INIT;   /* default init dir */

   cpid = getpid();
   if(cpid != 1) {
      usage(MSG_USAGE,MSG_NOT_ONE);
   }

   set_signals(ACT_SERV);  /* set signal handlers */

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
   mini_printf(MSG_CINIT,1); mini_printf(initdir,1); mini_printf("\n",1);

   if( chdir(CINIT_INIT) == -1) {
      perror(MSG_CHDIR);
      panic();
   }

   /******************** TMPDIR  **********************/
   if( mount(C_TMPMOUNT,CINIT_TMNT,C_TMPFS,0,NULL) == -1 ) {
      perror(MSG_ERR_MOUNT);
      panic();
   }

   /******************** begin socket **********************/
   sock = socket(AF_UNIX,SOCK_STREAM,0); /* create socket */
   if( sock == -1 ) {
      perror(MSG_SOCKET);
      panic();
   }
   
   memset(&addr, 0, sizeof(addr) ); /* clear addr */
   strcpy(addr.sun_path, CINIT_SOCK);
   addr.sun_family = AF_UNIX;
   
   if(bind(sock,(struct sockaddr *)&addr,sizeof(addr)) == -1) {
      perror(MSG_BIND);
      panic();
   }
   
   /* start listening */
   if(listen(sock,SOCK_QUEUE) == -1) {
      perror(MSG_LISTEN);
      panic();
   }
   
   /* start init or profile */
   run_init_svc(initdir);
   
   /* free, if we malloc()ed before */
   if(initdir != CINIT_INIT) {
      free(initdir);
   }

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
