/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    read data from cinit to the client
 */


#include "ipc.h"       /* IPC    */

/* gets a bunch of bytes and returns the answer from cinit */
int cinit_read_from(char **dest, int len)
{
   if(!cinit_ipc_logon())     return NULL;
   if(!cinit_ipc_connect())   return NULL;

   /* FIXME: add length to ipc function? */
   if(!cinit_ipc_csend(data))   return NULL;

   return 1;
}
