/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    return version of cinit
 *
 */

#include <string.h>     /* strncpy                    */
#include "config.h"     /* VERSION                    */
#include "cinit.h"      /* structure: cinit_answer    */

int answer_version(struct cinit_answer *asr)
{
   asr->ret = CINIT_MSG_OK;
   strncpy(asr->data, VERSION, PATH_MAX);

   return 1;
}
