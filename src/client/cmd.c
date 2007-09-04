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

#include "cmd.h"           /* own header        */
#include "signals.h"       /* which signal      */
#include "svc.h"           /* service related   */
#include "intern.h"        /* print_errno()     */

#include "cinit.h"         /* cinit external    */

#define C_USAGE(error) usage(USAGE_TEXT,error)
#define LOG(a,b)     mini_printf(a,1); minit_printf(b,1);

/***********************************************************************
 * cmd: main
 */
int main(int argc, char **argv)
{
   int opt, tmp;
   int32_t status;
   char *svc, *p = NULL;

   tmp = 0;

   /* FIXME: change e/d: make it a must to specify
    * -d w(ants) excluded)
    * -e n(eeds excluded)
    * -d i(nclude everything)
    */

   while((opt = getopt(argc,argv,CMD_OPTIONS)) != -1) {
      switch(opt) {
         /********************************************/
         case 'e':   /* enable service */
               svc = optarg;
         break;

         case 'd':   /* disable service */
               svc = optarg;
         break;

         /********************************************/
         case 's':   /* get status */
            svc  = optarg;

            /* relative path, add the cinit svc path in front of it */
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
            if(p) free(p);
            return tmp;

         break;

         case 'v':   /* get version of cinit */
            svc = cinit_get_version();
            if(svc) {
               printf("Version of cinit: %s\n",svc);
               free(svc);
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

   return 0;
}
