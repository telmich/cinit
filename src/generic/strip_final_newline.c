
/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    If the last character is \n, shrink the memory and remove it
 *
 */

#include <stdio.h>              /* NULL */
#include <string.h>             /* strchr */
#include <stdlib.h>             /* alloc */

char *strip_final_newline(char *str)
{
   char *p;

   /*
    * don't get fooled by bad pointers 
    */
   if(str == NULL) {
      return NULL;
   }

   p = strrchr(str, '\n');
   if(p) {
      if(*(p + 1) == '\0') {
         *p = '\0';             /* DO NOT FORGET TO TERMINATE STRING */
         str = realloc(str, (p - str));
      }
   }

   return str;
}
