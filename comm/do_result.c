/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * write result of action
 * part of cinit
 */

#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include "cinit.h"

/* one handler for read and write! */
char do_result(int nsock, char *value)
{
   ssize_t (*fpoint)(int,void* ,size_t);
   char buf;

   if(value == NULL) {  /* client */
      value = &buf;
      fpoint = read;
   } else {
      fpoint = ( ssize_t (*)(int, void*, size_t) ) write;
   }

   if(fpoint(nsock,value,1) == -1) {  /* result */
      perror(MSG_ERR_IO);
      return 0;                 
   }

   return *value;
}
