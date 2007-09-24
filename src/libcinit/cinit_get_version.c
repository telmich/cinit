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

int cinit_get_version(char *buf)
{
   struct cinit_question ask;
   struct cinit_answer   asr;

   memset(&ask, '\0', sizeof(ask));
   memset(&asr, '\0', sizeof(asr));
   ask.cmd = CINIT_MSG_GET_VERSION;

   if(!cinit_send_to(&ask, &asr))   return 0;

   if(asr.ret != CINIT_MSG_OK)      return 0;
   
   /* buf is always big enough to save the version string */
   strcpy(buf, asr.data);

   return 1;
}
