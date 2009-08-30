/*******************************************************************************
 *
 * 2007-2009 Nico Schottelius (nico-cinit at schottelius.org)
 *
 * This file is part of cinit.

 * cinit is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cinit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cinit.  If not, see <http://www.gnu.org/licenses/>.

 *
 *    cmd - the cinit client program - sends commands to cinit
 *
 */

#include <unistd.h>             /* getopt */
#include <signal.h>             /* signals */
#include <stdio.h>              /* printf() */
#include <stdlib.h>             /* free() */
#include <string.h>             /* strncmp */

#include <stdint.h>             /* integers */
#include <limits.h>             /* PATH_MAX */

#include "cmd.h"                /* own header */
#include "signals.h"            /* which signal */
#include "svc.h"                /* service related */
#include "intern.h"             /* print_errno() */

#include "cinit.h"              /* cinit external */

#define C_USAGE(error) usage(USAGE_TEXT,error)
#define MSG_IPC_ERROR      "An IPC error occured while connecting to cinit. " \
                           "Is cinit running?\n"
#define MSG_UNKNOWN_SVC    "Unknown service: %s\n"
#define MSG_UNKNOWN_RET    "Unknown return code: %d\n"

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
   char buf[CINIT_DATA_LEN];
   char *flag = NULL;
   int opt;
   int what = NOTHING;
   uint32_t ret;
   uint32_t (*fp)(char *, uint32_t);   /* to select enable or disable */


   union {
      uint32_t status;
      pid_t pid;
   } u;

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
      switch (opt) {

         /********************************************
         * Non-continuing parameters 
         */

         /********************************************
         * help
         */
         case 'h':
            printf(CMD_USAGE);
            return 0;
            break;

         /********************************************/
         case 'v':             /* get version of cinit */
            ret = cinit_get_version(buf);
            switch (ret) {
               case CINIT_ASW_OK:
                  printf("Version of cinit: %s\n", buf);
                  return 0;
                  break;
               case CINIT_ASW_IPC_ERROR:
                  fprintf(stderr, MSG_IPC_ERROR);
                  what = 2;
                  break;

               default:        /* should not happen */
                  printf(MSG_UNKNOWN_RET, ret);
                  what = 3;
                  break;
            }
            return what;
            break;

         /********************************************/
         case 'V':             /* version */
            printf("Version of cmd: %s\n", CMD_VERSION);
            return 0;
            break;

         /********************************************/
            /*
             * Continuing parameters 
             */

         /********************************************/
         case 'e':             /* enable service */
            what = ENABLE;
            flag = optarg;
            break;

         case 'd':             /* disable service */
            what = DISABLE;
            flag = optarg;
            break;

         /********************************************/
         case 'p':             /* get pid */
            what = PID;
            break;

         /********************************************/
         case 's':             /* get status */
            what = STATUS;
            break;

         /********************************************/

         default:
            fprintf(stderr,
                    "Sorry, I did not understand what you want. Try -h, please.\n");
            return 1;
            break;
      }
   }

   if(what == NOTHING) {
      fprintf(stderr,
              "That is not much you request from me. Try -h for help.\n");
      return 1;
   }

   if(!path_absolute(argv[optind], buf, CINIT_DATA_LEN))
      return 1;

   fp = NULL;
   switch (what) {
      case ENABLE:
         fp = cinit_svc_enable;
      case DISABLE:
         if(!fp) fp = cinit_svc_disable;

         u.status |= cinit_flag_to_uint32_t(flag);

         ret = fp(buf, u.status);

         switch (ret) {
            case CINIT_ASW_OK:
               printf("Set status of %s.\n", buf);
               what = 0;
               break;

            case CINIT_ASW_SVC_UNKNOWN:
               printf(MSG_UNKNOWN_SVC, buf);
               what = 1;
               break;

            case CINIT_ASW_IPC_ERROR:
               fprintf(stderr, MSG_IPC_ERROR);
               what = 2;
               break;

            default:           /* should not happen */
               printf(MSG_UNKNOWN_RET, ret);
               what = 3;
               break;
         }
         break;

      case PID:
         ret = cinit_svc_get_pid(buf, &(u.pid));
         switch (ret) {
            case CINIT_ASW_OK:
               printf("PID of %s: %d\n", buf, u.pid);
               what = 0;
               break;

            case CINIT_ASW_SVC_UNKNOWN:
               printf(MSG_UNKNOWN_SVC, buf);
               what = 1;
               break;

            case CINIT_ASW_IPC_ERROR:
               fprintf(stderr, MSG_IPC_ERROR);
               what = 2;
               break;

            default:           /* should not happen */
               printf(MSG_UNKNOWN_RET, ret);
               what = 3;
               break;
         }
         break;

      case STATUS:
         ret = cinit_svc_get_status(buf, &(u.status));
         switch (ret) {
            case CINIT_ASW_OK:
               printf("Status of %s is: %d\n", buf, u.status);
               what = 0;
               break;

            case CINIT_ASW_SVC_UNKNOWN:
               printf("Unknown service: %s\n", buf);
               what = 1;
               break;

            case CINIT_ASW_IPC_ERROR:
               fprintf(stderr, MSG_IPC_ERROR);
               what = 2;
               break;

            default:           /* should not happen */
               printf(MSG_UNKNOWN_RET, ret);
               what = 3;
               break;
         }
         break;
   }

   return what;
}
