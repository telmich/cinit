/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Disables a service
 */


#include <string.h>     /* str*                 */
#include <stdint.h>     /* integers             */
#include "cinit.h"      /* header for clients   */

/* returns either the status (>0)
 * or -1 on memory error
 */
int32_t cinit_get_svc_status(char *name)
{
   struct cinit_question qsn;
   struct cinit_answer   asr;

   qsn.cmd = CINIT_MSG_GET_STATUS;
   strcpy((qsn.data), name);
   qsn.options = 0;

   if(!cinit_send_to(&qsn, &asr)) return -1;

   return asr.ret;
}
