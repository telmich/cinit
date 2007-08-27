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

/* codes for messages */
enum {
   /* questions */
   CINIT_MSG_QUESTIONS=1000,
   CINIT_MSG_GET_STATUS,
   
   /* answers */
   CINIT_MSG_ANSWERS=2000,
   CINIT_MSG_SVC_UNKNOWN
};


#endif
