/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    cmd - the cinit client program - sends commands to cinit
 */

/*
-e:  enable service (including dependencies)
-eo: enable only the service without dependencies
-en: enable service and what it needs, but not its wants

-d:  disable service (including needs)
-do: disable only the service without dependencies
-dw: disable service and needs, but not the wants

-h: halt
-p: poweroff
-r: reboot

*/

/* #define USAGE_TEXT "cmd - cinit management\n\n" \
   "Usage:\n\ncmd -[phurs]\n"  \
   "   -s   - Service operation\n\n" \
   "        start:   Start service\n" \
   "        start:   Start service\n" \
   "\t-s\t- (service)            Power off the system\n" \
   "\t-s\t- (service)            Power off the system\n" \
   "\t-p\t- (power off)          Power off the system\n" \
   "\t-h\t- (halt)               Halt the system \n" \
   "\t-u\t- (update)             Reboot (warm) and update cinit\n" \
   "\t-r\t- (reboot)             Reboot the system\n" \
   "\t-s\t- (single user/rescue) Rescue mode\n\n" \

*/

/* Arguments:
   
   -e: enable  service
   -d: disable service

   -o: only: omit dependencies on disable / enable

   -h: halt system
   -r: reboot system
   -p: power off
   

*/

#define C_USAGE(error) usage(USAGE_TEXT,error)
#define LOG(a,b)     mini_printf(a,1); minit_printf(b,1);

#include <unistd.h>        /* getopt         */

#define OPTIONS            "deohpr"

/***********************************************************************
 * ccontrol: control cinit
 */
int main(int argc, char **argv)
{
   int opt;

   while((opt = getopt(argc,argv,OPTIONS)) != -1) {
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

   /* argv */
/*   if(argc != 2)              C_USAGE(MSG_ERR_LESS_ARGS);
   if(argv[1][0] != '-')      C_USAGE(MSG_ERR_BAD_ARGS);
*/
   return 0;
}
/*
      case 's':
         LOG(MSG_RESCUE);
         msg_reboot(CMD_RESCUE);
         break;

      case 'u':
         LOG(MSG_UPDATE);
         msg_reboot(CMD_UPDATE);
         break;

*/
