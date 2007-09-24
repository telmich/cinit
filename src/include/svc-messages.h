/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 *
 *    Service status messages
 */ 


#ifndef __CINIT_SVC_MESSAGES_H
#define __CINIT_SVC_MESSAGES_H

#include "svc.h"

struct cinit_svc_msg {
   int code;
   char *msg;
};

struct cinit_svc_msg cinit_svc_msg_codes[] = {
   { CINIT_ST_SH_ONCE,     "Service should be started once"       },
   { CINIT_ST_SH_RESPAWN,  "Service should respawn"               },
   { CINIT_ST_ONCE_OK,     "Service successfully started once"    },
   { CINIT_ST_ONCE_FAIL,   "Service failed to start once"         },
   { CINIT_ST_RESPAWNING,  "Service is respawning"                },
   { CINIT_ST_NEED_FAILD,  "One ore more needs failed"            },
   { CINIT_ST_IN_LIST,     "Service is in starter list"           },
   { CINIT_ST_BAD_ERR,     "Some strange error happened"          },
   { CINIT_ST_ONCE_RUN,    "Service is currently running once"    },
   { CINIT_ST_NOT_EXIST,   "This service does not exist"          }
};

#endif   /* _CINIT_SVC_H */
