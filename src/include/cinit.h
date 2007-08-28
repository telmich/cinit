/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Header file for external programs (in theory)
 */

#ifndef CINIT_EXTERNAL_HEADER
#define CINIT_EXTERNAL_HEADER

/* includes */
#include <stdint.h>     /* required for functions  */
#include <limits.h>     /* PATH_MAX                */

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
   int32_t  options;
//   char     data[PATH_MAX];
};

/* codes for messages */
enum {
   /* questions */
   CINIT_MSG_QUESTIONS=1000,
   CINIT_MSG_GET_STATUS,
   
   /* answers */
   CINIT_MSG_ANSWERS=2000,
   CINIT_MSG_SVC_UNKNOWN
};

/* functions */
int32_t cinit_get_svc_status(char *);
//char *cinit_send_to(char *, int);
int cinit_send_to(struct cinit_question *, struct cinit_answer *);


#endif
