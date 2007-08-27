/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    sends data from the client to cinit
 */


#include "ipc.h"        /* IPC                     */
#include "cinit.h"      /* struct cinit_message    */

/* gets a bunch of bytes and returns the answer from cinit */
char *cinit_send_to(struct cinit_message *data, int len)
{
   if(!cinit_ipc_logon())        return NULL;
   if(!cinit_ipc_connect())      return NULL;
   if(!cinit_ipc_csend(data))    return NULL;

   return 1;
}
