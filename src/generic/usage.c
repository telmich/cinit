/***********************************************************************
 *
 *    2005-2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    usage: tell the world what we want - seriously no capitalism
 *
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
