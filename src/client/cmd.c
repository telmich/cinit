/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    cmd - the cinit client program - sends commands to cinit
 */

#include <unistd.h>        /* getopt            */
#include <signal.h>        /* signals           */
#include <stdio.h>         /* printf()          */
#include <stdlib.h>        /* free()            */
#include <string.h>        /* strncmp           */

#include <stdint.h>        /* integers          */
#include <limits.h>        /* PATH_MAX          */

#include "cmd.h"           /* own header        */
#include "signals.h"       /* which signal      */
#include "svc.h"           /* service related   */
#include "intern.h"        /* print_errno()     */

#include "cinit.h"         /* cinit external    */

#define C_USAGE(error) usage(USAGE_TEXT,error)

enum {
   NOTHING,
   ENABLE,
   DISABLE,
   PID,
   STATUS
} whattodo;

/***********************************************************************
 * cmd: main
 */
int main(int argc, char **argv)
{
   int      opt, tmp, cnt;
   char     buf[PATH_MAX+1];
   union {
      int32_t  status;
      pid_t    pid;
   } u;

   char     flag = 'i';
   int      what = NOTHING;

   cnt = tmp = 0;

   /*
    * -d w(ants)  excluded)
    * -e n(eeds   excluded)
    * -d i(nclude everything)
    */

/* check for
 * d|e:
 *    check for flags
 * p|s:
 *    continue with service
 * h|v|V: print and exit
 */
   while((opt = getopt(argc, argv, CMD_OPTIONS)) != -1) {
      switch(opt) {
         /********************************************/
         /* Non-Continuing parameters */
         /********************************************/
         case 'h':   /* help */
            printf(CMD_USAGE);
            return 0;
         break;

         /********************************************/
         case 'v':   /* get version of cinit */
            tmp = cinit_get_version(buf);
            if(tmp) {
               printf("Version of cinit: %s\n", buf);
               return 0;
            } else {
               fprintf(stderr, "Cannot get version of cinit!\n");
               return 2;
            }
         break;

         /********************************************/
         case 'V':   /* version */
            printf("Version of cmd: %s\n", CMD_VERSION);
            return 0;
         break;

         /********************************************/
         /* Continuing parameters */
         /********************************************/
         case 'e':   /* enable service */
            what = ENABLE;
            flag = optarg ? optarg[0] : 'i';
         break;

         case 'd':   /* disable service */
            what = DISABLE;
            flag = optarg ? optarg[0] : 'i';
         break;

         /********************************************/
         case 'p':   /* get pid */
            what = PID;
         break;

         /********************************************/
         case 's':   /* get status */
            what = STATUS;
         break;
         /********************************************/

         default:
            fprintf(stderr,"Sorry, I did not understand what you want. Try -h, please.\n");
            return 1;
         break;
      }
   }

   if(what == NOTHING) {
      fprintf(stderr,"That is not much you request from me. Try -h for help.\n");
      return 1;
   }
   
   if(!path_absolute(argv[optind], buf, PATH_MAX+1)) return 1;

   switch(what) {
      case ENABLE:
      case DISABLE:
      break;

      case PID:
         u.pid = cinit_svc_get_pid(buf);
         switch(u.pid) {
            case -1:
               fprintf(stderr, "Communication error\n");
               what = 2;
            break;
            case 0:
               printf("Unknown service: %s\n", buf);
               what = 1;
            break;
            default:
               printf("PID of %s: %d\n",buf, u.pid);
               what = 0;
            break;
         }
      break;
   
      case STATUS:
         u.status = cinit_get_svc_status(buf);
         if(u.status < 0) {
            fprintf(stderr, "Communication error\n");
            what = 2;
         } else {
            switch(u.status) {
               case CINIT_MSG_OK:
                  printf("Status of %s is: %d\n", buf, u.status);
                  what = 0;
               break;

               case CINIT_MSG_SVC_UNKNOWN:
                  printf("Unknown service: %s\n", buf);
                  what = 1;
               break;

               default: /* should not happen */
                  printf("Unknown status returned for %s: %d\n", buf, u.status);
                  what = 2;
               break;
            }
         } 
      break;
   }

   return what;
}
