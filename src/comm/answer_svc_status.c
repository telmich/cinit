/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    return status of service
 *
 */

#include <string.h>     /* strncpy                    */
#include "svc.h"        /* VERSION                    */
#include "cinit.h"      /* structure: cinit_answer    */

int answer_svc_status(char *svc, struct cinit_answer *asr)
{
   struct listitem *tmp;

   tmp = list_search(svc);
   if(!tmp) return 0;
   
   asr->ret       = CINIT_MSG_OK;
   asr->options   = tmp->pid;

   return 1;
}
