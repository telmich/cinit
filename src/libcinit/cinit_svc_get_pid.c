/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Retrieves status of a service
 */


#include <string.h>     /* str*                 */
#include "cinit.h"      /* header for clients   */

/* returns either the status (>0)
 * or -1 on memory error
 */
pid_t cinit_svc_get_pid(char *name)
{
   struct cinit_question qsn;
   struct cinit_answer   asr;

   qsn.cmd = CINIT_MSG_GET_PID;
   strcpy((qsn.data), name);
   qsn.options = 0;

#error "return pid!!!"

   if(!cinit_send_to(&qsn, &asr)) return -1;

   return asr.ret;
}
