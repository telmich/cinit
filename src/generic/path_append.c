/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    create path to needs
 */

#include <string.h>                 /* strlen               */
#include <limits.h>                 /* PATH_MAX             */

#include "intern.h"                 /* mini_printf, PD_ERR  */

int path_append(char *path, char *append)
{
   size_t end = strlen(path);

   if(strcmp(&path[end-1],SLASH)) {
      if((end + strlen(SLASH) + strlen(append)) > PATH_MAX) return 0;
      strcat(path,SLASH);
   } else {
      if((end + strlen(append)) > PATH_MAX) return 0;
   }
   strcat(path,append);

   return 1;
}
