/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Return stop status
 *
 */

//#include <string.h>     /* strncpy                    */
#include "cinit.h"      /* structure: cinit_answer    */

int answer_svc_stop(char *svc, struct cinit_answer *asr)
{
   struct listitem *tmp;

   tmp = list_search(svc);
   if(!tmp) {
      asr->ret = CINIT_MSG_SVC_UNKNOWN;
   } else {
      asr->ret       = CINIT_MSG_OK;
      svc_stop(tmp);
   }

   return 1;
}
