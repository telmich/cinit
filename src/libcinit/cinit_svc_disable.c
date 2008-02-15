 *    Disables a service


#include <string.h>     /* str*                 */
#include <stdint.h>     /* integers             */
#include "cinit.h"      /* header for clients   */

/* returns either the status (>0)
 * or -1 on memory error
 */
uint32_t cinit_get_svc_status(char *name, uint32_t *status)
{
   struct cinit_question qsn;
   struct cinit_answer   asr;

   qsn.cmd = CINIT_MSG_GET_STATUS;
   strcpy((qsn.data), name);
   qsn.options = 0;

   if(!cinit_send_to(&qsn, &asr)) return -1;

   *status = asr.options;

   return asr.ret;
}
