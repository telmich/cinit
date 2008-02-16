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
   char     data[CINIT_DATA_LEN];
   uint32_t options;
};

/* messages from cinit */
struct cinit_answer {
   uint32_t ret;
   uint32_t options;
   char     data[CINIT_DATA_LEN];
};

/* codes for messages */
enum {
   /* questions */
   CINIT_MSG_QUESTIONS=1000,  /* begin questions at 1000    */
   CINIT_MSG_GET_STATUS,      /* status of a service        */
   CINIT_MSG_GET_PID,         /* get pid of a service       */
   CINIT_MSG_GET_VERSION,     /* version of cinit           */
   CINIT_MSG_SVC_STOP,        /* service: stop              */
   CINIT_MSG_SVC_START,       /* service: start             */
   
   /* answers */
   CINIT_MSG_ANSWERS=2000,    /* begin answers at 2000      */
   CINIT_MSG_OK,              /* general ok value           */
   CINIT_MSG_ERR,             /* general error value        */
   CINIT_MSG_SVC_UNKNOWN,     /* Services is not known      */
   CINIT_MSG_SVC_STOPPED,     /* service: stop              */
   CINIT_MSG_SVC_STARTED      /* service: start             */
};

struct cinit_msg_msg {
   int code;
   char *msg;
};

//struct cinit_msg_msg cinit_codes2messages[] = {

//}

/* functions */
pid_t    cinit_svc_get_pid(char *);
uint32_t cinit_get_svc_status(char *);
int      cinit_get_version(char *);
int      cinit_send_to(struct cinit_question *, struct cinit_answer *);
void     cinit_cp_data(char data[], char *src);

#endif
