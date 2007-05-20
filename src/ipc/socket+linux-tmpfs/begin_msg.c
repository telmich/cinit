/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * tell cinit that I want to start a service
 * part of cinit
 */

#include <unistd.h>
#include <stdio.h>
#include "cinit.h"

int begin_msg(char cmd)
{
   sock = connect_sock(sock);
   if( sock == -1 ) {
      return 0;
   }
   
   if(write(sock,&cmd,sizeof(cmd)) == -1) {
      perror(MSG_ERR_IO);
      return 0;
   }

   return 1;
}
