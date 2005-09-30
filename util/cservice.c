/* 
 * (c) 2005 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * cservice: control cinit services
 * part of cLinux/cinit
 */

/* *stat() */
#include <sys/stat.h>
#include <unistd.h>

/* open */
#include <fcntl.h>

/* signal */
#include <signal.h>

/* PATH_MAX */
#include <limits.h>

/* str* */
#include <string.h>

/* sockets */
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

/* mount */
#include <sys/mount.h>

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "cinit.h"

/* global variable */
struct listitem *list;
int sock;
pid_t cpid;

/***********************************************************************
 * cservice - control cinit services
 */

#define USAGE_TEXT "cservice - start and stop cinit services\n\n" \
   "cservice -[ear] <service>\n"  \
   "\t-e\t- (ein,on )   start a service (respawn if respawning is set)\n" \
   "\t-a\t- (aus,off)   stop a respawing service\n" \
   "\t-r\t- (restart)   stop and start a service\n"

/***********************************************************************
 * fuzzy_path: allow other kinds of path specification ..
 */
char *fuzzy_path(char *rpath)
{
   char pathtmp[PATH_MAX];
   char *re = NULL;

   /* change to rpath */
   if(chdir(rpath) == -1) {
      perror(rpath);
      return NULL;
   }

   /* get absolute name of rpath */
   if(! (int) getcwd(pathtmp,PATH_MAX)) {
      perror(pathtmp);
      return NULL;
   }
   
   re = malloc( strlen(pathtmp) + 1);

   if(re != NULL) {
      strcpy(re,pathtmp);
   }

   return re;
}

#define C_USAGE(error) usage(USAGE_TEXT,error)

/***********************************************************************
 * cservice: the main part for controlling cinit from outside
 */
int main(int argc, char **argv)
{
   /* argv */
   if(argc != 3)              C_USAGE(MSG_ERR_LESS_ARGS);
   if(argv[1][0] != '-')      C_USAGE(MSG_ERR_BAD_ARGS);
   if(strlen(argv[1]) != 2)   C_USAGE(MSG_ERR_ARGS_LEN);

   switch(argv[1][1]) {
      case 'a':   /* aus */
      case 'r':   /* restart */
         switch( msg_svc_on_off( fuzzy_path(argv[2]),0 ) ) {
            case ST_OFF:
               SERVICE_LOG(argv[2],LOG_SVC_STOPED);
               break;
            case RT_ERR_COMM:
               SERVICE_LOG(argv[2],MSG_ERR_COMM);
               break;
            default:
               SERVICE_LOG(argv[2],MSG_SHOULD_NOT_HAPPEN);
               break;
         }
         if( argv[1][1] == 'a') break; /* only continue if restarting */

      case 'e':   /* ein */
         switch (run_svc(argv[2])) { /* run_svc fuzzys itself */
            case RT_NOTEXIST:
               SERVICE_LOG(argv[2],LOG_SVC_NOTEXIST);
               break;
            case RT_SVC_FAILED:
               SERVICE_LOG(argv[2],LOG_SVC_FAILED);
               break;
            case ST_FAIL:
               SERVICE_LOG(argv[2],LOG_SVC_FAIL);
               break;
            case ST_ONCE:
               SERVICE_LOG(argv[2],LOG_SVC_ONCE);
               break;
            case RT_ERR_COMM:
               SERVICE_LOG(argv[2],MSG_ERR_COMM);
               break;
            case ST_RESPAWN:
               SERVICE_LOG(argv[2],LOG_SVC_RESPAWN);
               break;
            case ST_NEED_FAIL:
               SERVICE_LOG(argv[2],LOG_NEED_FAIL);
               break;
            default:
               SERVICE_LOG(argv[2],MSG_SHOULD_NOT_HAPPEN);
               break;
         }
         break;
      default:
         C_USAGE(MSG_ERR_BAD_ARGS);
         break;
   }
   return 0;
}
/* uses cinit-0.2 return code style */
