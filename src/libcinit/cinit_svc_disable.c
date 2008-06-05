
/*******************************************************************************
 *
 * 2007-2008 Nico Schottelius (nico-cinit at schottelius.org)
 *
 * This file is part of cinit.

 * cinit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cinit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cinit.  If not, see <http://www.gnu.org/licenses/>.

 *
 *    Disables a service
 *
 */

#include <stdint.h>             /* integers */

#include "cinit.h"              /* header for clients */

/*
 * to cinit:
 *    disable + flags
 * from cinit:
 *    status
 *       unknown service
 *       disabled the service
 *
 *       disabled the service and needs
 *       disabled the service and wants
 *       disabled the service and needs and wants
 *
 *       if it is one of the last three it follows
 *       uint32_t num: how many services stopped
 *          num times
 *
 *          uint32_t len (excluding \0)
 *          char name[]
 */

uint32_t cinit_svc_disable(char *svc, uint32_t flag)
{
   struct cinit_question qsn;
   struct cinit_answer asr;

   cinit_prepare_comm(&qsn, &asr, CINIT_QSN_SVC_DISABLE);
   cinit_cp_data((qsn.data), svc);

   qsn.opt = flag;

   if(!cinit_send_to(&qsn, &asr))
      return CINIT_ASW_IPC_ERROR;

   /*
    * FIXME: 0.3pre15: add retrieval of services 
    */

   return asr.ret;
}
