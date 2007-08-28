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
   struct cinit_question ask;
   struct cinit_answer   answer;

   ask.cmd = CINIT_MSG_GET_STATUS;
   strcpy((ask.data), name);
   ask.options = 0;

   cinit_send_to(&ask, &answer);

   return 1;
}
