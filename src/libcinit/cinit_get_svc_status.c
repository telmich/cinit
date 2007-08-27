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
#include <stdint.h>     /* integers             */

#include "cinit.h"      /* header for clients   */

/* returns either the status (>0)
 * or -1 on memory error
 */
int32_t cinit_get_svc_status(char *name)
{
   /* fixme: s32 int! */
   int tmp;
   int32_t res;

   int offset = 0, len = strlen(name);

   char *p, *answer;

   p = malloc(len + 2 * sizeof(tmp));
   if(!p) return -1;

   /* code */
   tmp = CINIT_MSG_GET_STATUS;
   strncpy(p,(char *) &tmp, sizeof(tmp));
   offset += sizeof(tmp);

   /* length */
   strncpy(&p[offset],(char *) &len, sizeof(len));
   offset += sizeof(len);

   /* data */
   strncpy(p, (char *) name, len);

   answer = cinit_send_to(p,len);

   if(answer) {
      strncpy((char *) &res, answer, sizeof(res));
      free(answer);
   } else {
      res = -1;
   }

   free(name);
   return res;
}
