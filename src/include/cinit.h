/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Header file for external programs (in theory)
 */

#ifndef __CINIT_EXTERNAL_HEADER
#define __CINIT_EXTERNAL_HEADER

/* includes */
#include <stdint.h>     /* required for functions  */
#include <limits.h>     /* PATH_MAX                */
#include <sys/types.h>  /* pid_t                   */

/*
 * structures: independent of the ipc code!
 */

/* messages from the client */
struct cinit_question {
   int32_t  cmd;
   char     data[PATH_MAX];
   int32_t  options;
};

/* messages from cinit */
struct cinit_answer {
   int32_t  ret;
   int32_t  options;
   char     data[PATH_MAX];
};

/* codes for messages */
enum {
   /* questions */
   CINIT_MSG_QUESTIONS=1000,  /* begin questions at 1000    */
   CINIT_MSG_GET_STATUS,      /* status of a service        */
   CINIT_MSG_GET_PID,         /* get pid of a service       */
   CINIT_MSG_GET_VERSION,     /* version of cinit           */
   
   /* answers */
   CINIT_MSG_ANSWERS=2000,    /* begin answers at 2000      */
   CINIT_MSG_OK,              /* general ok value           */
   CINIT_MSG_ERR,             /* general error value        */
   CINIT_MSG_SVC_UNKNOWN      /* Services is not known      */
};

struct cinit_msg_msg {
   int code;
   char *msg;
};

//struct cinit_msg_msg cinit_codes2messages[] = {

//}

/* functions */
pid_t    cinit_svc_get_pid(char *);
int32_t  cinit_get_svc_status(char *);
int      cinit_get_version(char *);
int      cinit_send_to(struct cinit_question *, struct cinit_answer *);

#endif
