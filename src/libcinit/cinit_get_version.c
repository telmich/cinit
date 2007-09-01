/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Retrieves version of cinit
 */

#include <stdlib.h>     /* malloc               */
#include <string.h>     /* str*, memset         */
#include <stdio.h>      /* NULL                 */

#include "cinit.h"      /* header for clients   */

char *cinit_get_version()
{
   struct cinit_question ask;
   struct cinit_answer   answer;
   char *ret;

   memset(&ask,'\0',sizeof(ask));
   ask.cmd = CINIT_MSG_GET_VERSION;

   if(!cinit_send_to(&ask, &answer)) return NULL;
   
   ret = malloc(strlen(answer.data) +1);
   if(!ret) return NULL;
   strcpy(ret,answer.data);

   return ret;
}
