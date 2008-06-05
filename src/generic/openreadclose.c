
/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    read a file
 *
 */

#include <unistd.h>             /* open, read, close */
#include <string.h>             /* strncpy */
#include <stdlib.h>             /* realloc */
#include <errno.h>              /* errno */
#include <stdio.h>              /* NULL */
#include <fcntl.h>              /* open */
#include "intern.h"             /* ORC_* */

int openreadclose(char *filename, char **where)
{

   int tmp;
   int cnt;
   int fd;
   char buf[512];

   *where = NULL;

   /*
    * what a wonderful loop 
    */
   while((fd = open(filename, O_RDONLY)) == -1) {
      if(errno == ENOENT)
         return ORC_ERR_NONEXISTENT;
      if(errno != EINTR)
         return ORC_ERR_OPEN;
   }

   cnt = 0;
   while(1) {
      tmp = read(fd, buf, 512);

      if(tmp == -1) {
         if(errno == EINTR)
            continue;
         else
            return ORC_ERR_READ;
      } else if(tmp == 0) {
         break;
      }

      cnt += tmp;
      *where = realloc(*where, cnt + 1);
      if(*where == NULL)
         return ORC_ERR_MEM;

      /*
       * FIXME check correctness of copied buffer... and get some sleep..soon,
       * very soon! 
       */
      strncpy(&(*where)[cnt - tmp], buf, tmp);
   }

   while((fd = close(fd)) == -1) {
      if(errno == EINTR)
         continue;
      return ORC_ERR_CLOSE;
   }

   /*
    * terminate string! 
    */
   (*where)[cnt] = '\0';

   return ORC_OK;
}
