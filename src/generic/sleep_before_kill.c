/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Sleep
 *
 */

#include <unistd.h>

void sleep_before_kill()
{
   char *p;

   /* don't get fooled by bad pointers */
   if(str == NULL) return;

   p = str;
   while ( *p ) p++;
   
   write(fd,str,(size_t) (p - str) );
}
