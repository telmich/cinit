/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * run_svc
 * part of cinit
 */

#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>

#include "cinit.h"

/* open socket connection to cinit-serv and close original socket */
int connect_sock(int socke)
{
   int nsock;
   struct sockaddr_un addr;

   close(socke);

   nsock = socket(PF_UNIX,SOCK_STREAM,0);
   if( nsock == -1 ) {
      perror(MSG_SOCKET);
      return -1;
   }
   socke = sizeof(addr);
   memset(&addr,0,socke);
   strcpy(addr.sun_path, CINIT_SOCK);
   addr.sun_family   = AF_UNIX;
   
   if(connect(nsock,(struct sockaddr *)&addr,socke) == -1) {
      return -1;
   }

   return nsock;
}
