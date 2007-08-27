/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Retrieves status of a service
 */


#include <stdlib.h>     /* malloc               */
#include <string.h>     /* str*                 */

#include "cinit.h"      /* header for clients   */

int cinit_get_svc_status(char *name)
{
   long int tmp
   int offset = 0;
   char *p, *answer;

   p = malloc(strlen(name) + 2 * sizeof(tmp));
   if(!p) return -1;

   /* code */
   tmp = CINIT_MSG_GET_STATUS;
   strncpy(p,(char *) &tmp[offset],sizeof(tmp));
   offset += sizeof(tmp);

   /* length */
   tmp = strlen(name);
   strncpy(p,(char *) &tmp[offset],sizeof(tmp));
   offset += sizeof(tmp);

   /* data */
   tmp = strlen(name);
   strncpy(p, (char *) name, tmp);

   answer = cinit_send_to(p);
   if(answer) {
      offset = 0;
      strncpy((char *) &tmp, &answer[offset], sizeof(tmp));

      free(answer);
   } else {
      tmp = -1;
   }

   free(name);
   return tmp;
}
