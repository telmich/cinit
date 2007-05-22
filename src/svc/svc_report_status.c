/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Tell the world what happened to the service
 */

#include "intern.h"        /* mini_printf    */
#include "messages.h"      /* MSG_INTRO_SVC  */

void svc_report_status(char *svc, char *msg, char *err)
{
   mini_printf(MSG_INTRO_SVC,1);
   mini_printf(svc,1);
   mini_printf(": ",1);
   mini_printf(msg,1);
   if(err) {
      mini_printf(" (",1);
      mini_printf(err,1);
      mini_printf(")",1);
   }
   mini_printf("\n",1);
}
