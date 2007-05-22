/***********************************************************************
 *
 *    2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    usage: tell the world what we want - seriously no capitalism
 *    usage: tell the user what's wrong and a help text
 *
 */

#include <unistd.h>        /* _exit()     */
#include "intern.h"        /* mini_printf */

void usage(char *banner, char *text)
{
   /* print banner + error message */
   mini_printf(banner,1);
   mini_printf(text,1);
   _exit(1);
}
