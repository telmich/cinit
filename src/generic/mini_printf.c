/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Print to the world!
 *
 */

#include <unistd.h>

void mini_printf(char *str,int fd)
{
   char *p;

   /* don't get fooled by bad pointers */
   if(str == NULL) return;

   p = str;
   while ( *p ) p++;
   
   write(fd,str,(size_t) (p - str) );
}
