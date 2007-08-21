/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    cmd - the cinit client program - sends commands to cinit
 */

#include <unistd.h>        /* getopt         */

#include "cmd.h"

#define C_USAGE(error) usage(USAGE_TEXT,error)
#define LOG(a,b)     mini_printf(a,1); minit_printf(b,1);

/***********************************************************************
 * cmd: main
 */
int main(int argc, char **argv)
{
   int opt;

   while((opt = getopt(argc,argv,CMD_OPTIONS)) != -1) {
      switch(opt) {
         case 'p':   /* power off */
         //   LOG(MSG_POWER_OFF);
         //   msg_reboot(CMD_POWEROFF);
         break;

         case 'h':   /* halt */
//            mini_printf(",1);
//            cinit_halt();
            break;

         case 'r':   /* reboot */
        //    LOG(MSG_REBOOT);
         //   msg_reboot(CMD_REBOOT);
            break;

         default:
         //   C_USAGE(MSG_ERR_BAD_ARGS);
            break;
      }
   }
}
