
/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    test gen_svc_tree
 */

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include "build_argv.h"

int main()
{
   gen_svc_tree("/etc/cinit/svc/init");
   list_display_all();
}
