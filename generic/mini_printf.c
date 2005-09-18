/* 
 * cinit
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * print string
 */

#include <unistd.h>

void mini_printf(char *str,int fd)
{
   char *p;
   size_t length = 0;

   p = str;
   while ( *p != '\0') {
      ++length;
      ++p;
   }
   write(fd,str,length);
   /* \n is put by outside function */
   /* write(fd,"\n",1); */
}
