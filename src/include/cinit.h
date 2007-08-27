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

/* structs */
struct cinit_message {
   long int mtype;
   char     data[PATH_MAX];
   int32_t  options;
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
char *cinit_send_to(char *, int);


#endif
