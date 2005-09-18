/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * try to start a service
 * part of cinit
 */

#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>
#include "cinit.h"

/* serv:
 * get buf
 * return length
 *
 * client:
 * print svc
 * return errorcode
 */
int do_svc_name(int sock2, char *svc, int action)
{
   int tmp;
   ssize_t (*fpoint)(int,void* ,size_t);
   
   /* set pointers */
   if(action == ACT_CLIENT) {
      fpoint = ( ssize_t (*)(int, void*, size_t) ) write;
      tmp = strlen(svc);
   } else {
      fpoint = read;
   }

   /* read / write lenght */
   if( fpoint(sock2,&tmp,sizeof(tmp)) == -1) {
      perror(MSG_ERR_IO);
      return 0;
   }

   if(tmp > PATH_MAX) {
      return 0;
   }

   /* write/read service name */
   if( fpoint(sock2,svc,tmp) == -1) {
      perror(MSG_ERR_IO);
      return 0;
   }

   return tmp;
}
