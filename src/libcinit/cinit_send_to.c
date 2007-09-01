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

int cinit_send_to(struct cinit_question *data, struct cinit_answer *res)
{
   if(!cinit_ipc_logon())        return 0;
   if(!cinit_ipc_csend(data))    return 0;
   if(!cinit_ipc_cread(res))     return 0;
   if(!cinit_ipc_logoff())       return 0;
   return 1;
}
