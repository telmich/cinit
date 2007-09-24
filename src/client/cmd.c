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

/***********************************************************************
 * cmd: main
 */
int main(int argc, char **argv)
{
   int      opt, tmp, cnt;
   int32_t  status;
   pid_t    pid;
   char     *svc, *p = NULL;
   char     buf[PATH_MAX];

   cnt = tmp = 0;

   /*
    * -d w(ants) excluded)
    * -e n(eeds excluded)
    * -d i(nclude everything)
    */

   while((opt = getopt(argc,argv,CMD_OPTIONS)) != -1) {
      ++cnt; 
      switch(opt) {
         /********************************************/
         case 'h':   /* help */
            printf(CMD_USAGE);
            return 0;
         break;

         case 'V':   /* version */
            printf("%s\n",CMD_VERSION);
            return 0;
         break;
         /********************************************/
         case 'e':   /* enable service */
               svc = optarg;
         break;

         case 'd':   /* disable service */
               svc = optarg;
         break;

         /********************************************/
         case 'p':   /* get pid */
         case 's':   /* get status */
            svc  = optarg;

            /* relative path, add the cinit svc path in front of it */
            /* FIXME: use buf! */
            if(strncmp(svc,SLASH,strlen(SLASH))) {
               p = malloc(strlen(CINIT_DIR)
                        + strlen(SLASH)
                        + strlen(SVCDIR) 
                        + strlen(SLASH)
                        + strlen(svc)
                        + 1);
               if(!p) {
                  /* bad error */
                  return 2;
               }
               strcpy(p,CINIT_DIR);
               strcat(p,SLASH);
               strcat(p,SVCDIR);
               strcat(p,SLASH);
               strcat(p,svc);
               svc = p;
            }

            if(opt == 's') {
               status = cinit_get_svc_status(svc);
               if(status < 0) {
                  printf("Communication error\n");
                  tmp = 1;
               } else {
                  switch(status) {
                     case CINIT_MSG_SVC_UNKNOWN:
                        printf("Unknown service: %s\n",svc);
                        tmp = 1;
                     break;
                     case CINIT_MSG_OK:
                        printf("Status of %s is: %d\n",svc, status);
                        tmp = 0;
                     break;
                     /* should not happen */
                     default:
                        printf("Unknown status returned for %s: %d\n",svc, status);
                        tmp = 3;
                     break;
                  }
               } 
            } else { /* -p */
               pid = cinit_svc_get_pid(svc);
               if(pid == 0) {
                  printf("Unknown service: %s\n",svc);
                  tmp = 1;
               } else {
                  printf("PID of %s: %d\n",svc, pid);
                  tmp = 0;
               }
            }

            if(p) free(p);
            return tmp;

         break;

         case 'v':   /* get version of cinit */
            tmp = cinit_get_version(buf);
            if(tmp) {
               printf("Version of cinit: %s\n", buf);
               return 0;
            } else {
               printf("Cannot get version of cinit!\n");
               return 1;
            }
         break;

         /* FIXME: add -V: version of cmd */

         default:
            printf("Unimplemented option :-)\n");
            return 1;
         break;
      }
   }
   
   if(!cnt) {
      printf(CMD_USAGE);
      return 1;
   }

   return 0;
}
