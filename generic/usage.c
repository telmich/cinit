/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * usage: tell the world what we want - no capitalism
 * part of cLinux/cinit
 */

#include <unistd.h>
#include "cinit.h"

/***********************************************************************
 * usage: tell the user what's wrong and a help text
 */
void usage(char *banner, char *text)
{
   /* print banner + error message */
   mini_printf(banner,1);
   mini_printf(text,1);
   _exit(1);
}
