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
 *    Header file for external programs (in theory)
 */

#ifndef __CINIT_EXTERNAL_HEADER
#define __CINIT_EXTERNAL_HEADER

/* includes */
#include <stdint.h>     /* required for functions  */
#include <limits.h>     /* PATH_MAX                */
#include <sys/types.h>  /* pid_t                   */

/* limits */
#define CINIT_DATA_LEN (PATH_MAX+1)

/*
 * structures: independent of the ipc code!
 */

/* messages from the client */
struct cinit_question {
   uint32_t cmd;
   uint32_t opt;
   char     data[CINIT_DATA_LEN];
};

/* messages from cinit */
struct cinit_answer {
   uint32_t ret;
   uint32_t opt;
   char     data[CINIT_DATA_LEN];
};

/***********************************************************************
 * codes for messages
 */
enum { /* questions */
   CINIT_QSN_GET_STATUS    = 0x01,     /* status of a service        */
   CINIT_QSN_GET_PID       = 0x02,     /* get pid of a service       */
   CINIT_QSN_GET_VERSION   = 0x04,     /* version of cinit           */
   CINIT_QSN_SVC_DISABLE   = 0x08,     /* service: stop              */
   CINIT_QSN_SVC_ENABLE    = 0x10,     /* service: start             */
   CINIT_QSN_SVC_NEEDS     = 0x20,     /* in/exclude needs           */
   CINIT_QSN_SVC_WANTS     = 0x40,     /* in/exclude wants           */
   CINIT_QSN_SVC_LIST      = 0x80,     /* list services              */

   CINIT_QSN_QUESTION_END  = 0xffff    /* last message               */
};

enum { /* answers */
   CINIT_ASW_IPC_ERROR     = 0x00,     /* bad error                  */
   CINIT_ASW_OK            = 0x01,     /* general ok value           */
   CINIT_ASW_SVC_UNKNOWN   = 0x04,     /* Services is not known      */
   CINIT_ASW_SVC_DISABLED  = 0x08,     /* service: stop              */
   CINIT_ASW_SVC_ENABLED   = 0x10,     /* service: start             */
   CINIT_ASW_SVC_ERR       = 0x20,     /* in/excluded needs          */
   CINIT_ASW_SVC_WANTS     = 0x40,     /* in/excluded wants          */
   CINIT_ASW_SVC_NEEDS     = 0x80,     /* in/excluded needs          */
   CINIT_ASW_ERR_INTERN    = 0x100,    /* cinit internal error       */

   CINIT_ASW_ANSWER_END    = 0xffff    /* last message               */
};

enum cinit_svc_flags {
   CINIT_CMD_SVC_WANTS = 'w',
   CINIT_CMD_SVC_NEEDS = 'n'
};

struct cinit_msg_msg {
   int code;
   char *msg;
};

//struct cinit_msg_msg cinit_codes2messages[] = {

//}

/* functions */
int      cinit_send_to(struct cinit_question *, struct cinit_answer *);
void     cinit_cp_data(char data[], char *src);

void     cinit_prepare_comm(struct cinit_question *qsn,
                            struct cinit_answer   *asr,
                            uint32_t cmd);

uint32_t cinit_flag_to_uint32_t(char *);
uint32_t cinit_get_version(char *);
uint32_t cinit_svc_disable(char *svc, uint32_t flag);
uint32_t cinit_svc_enable(char *svc, uint32_t flag);
uint32_t cinit_svc_get_pid(char *, pid_t *status);
uint32_t cinit_svc_get_status(char *, uint32_t *);

#endif
