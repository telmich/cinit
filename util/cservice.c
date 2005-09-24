/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * cservice: control cinit
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
 * cservice - control cinit
 */

#define USAGE_TEXT "cservice - start and stop cinit services\n\n" \
   "cservice -[ear] <service>\n"  \
   "\t-e\t- (ein,on)    start a service (respawn if respawning is set)\n" \
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
   if(re == NULL) return NULL;

   strcpy(re,pathtmp);

   return re;
}

#define C_USAGE(error) usage(USAGE_TEXT,error)

/***********************************************************************
 * cservice: the main part for controlling cinit from outside
 */
int main(int argc, char **argv)
{
   /* FIXME: move messages to message.h */
   /* argv */
   if(argc != 3)              C_USAGE("Too less arguments!");
   if(argv[1][0] != '-')      C_USAGE("Wrong arguments");
   if(strlen(argv[1]) != 2)   C_USAGE("Wrong parameter length");


   switch(argv[1][1]) {
      case 'a':   /* aus */
      case 'r':   /* restart */
         mini_printf(argv[2],1);
         mini_printf(": ",1);
         /* FIXME: move messages to message.h */
         switch( msg_svc_on_off( fuzzy_path(argv[2]),0 ) ) {
            case ST_OFF:
               mini_printf("Service successfully stoped.\n",1);
               break;
            case ST_ERR_COMM:
               mini_printf("Communication error\n",1);
               break;
            default:
               mini_printf("Unknown error occured.\n",1);
               break;
         }
         if( argv[1][1] == 'a') break; /* only continue if restarting */

      case 'e':   /* ein */
         mini_printf(argv[2],1);
         mini_printf(": ",1);
         switch (run_svc(argv[2])) { /* run_svc fuzzys itself */
            case RT_SVC_FAILED:
               mini_printf("Service failed to start before.\n",1);
               break;
            case ST_FAIL:
               mini_printf("Service failed to start.\n",1);
               break;
            case ST_TMP:
               mini_printf("Service is beeing started already.\n",1);
               break;
            case ST_ONCE:
               mini_printf("Service executed once.\n",1);
               break;
            case ST_RESPAWN:
               mini_printf("Service is respawning.\n",1);
               break;
            case ST_UNSPEC:
            default:
               mini_printf("Unknown error occured.\n",1);
               break;
         }
         break;
      default:
         C_USAGE("Unknown parameter");
         break;
   }
   return 0;
}
