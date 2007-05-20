/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    cmd - the cinit client program - sends commands to cinit
 */

#define USAGE_TEXT "cmd - cinit management\n\n" \
   "Usage:\n\ncmd -[phurs]\n"  \
   "\t-p\t- (power off)          Power off the system\n" \
   "\t-h\t- (halt)               Halt the system \n" \
   "\t-u\t- (update)             Reboot (warm) and update cinit\n" \
   "\t-r\t- (reboot)             Reboot the system\n" \
   "\t-s\t- (single user/rescue) Rescue mode\n\n" \

/* Arguments:
   
   -e: enable  service
   -d: disable service

   -o: only: omit dependencies on disable / enable

   -h: halt system
   -r: reboot system
   -p: power off
   

*/
int main(int argc, char **argv)
{



#define C_USAGE(error) usage(USAGE_TEXT,error)

/***********************************************************************
 * ccontrol: control cinit
 */
int main(int argc, char **argv)
{
   /* argv */
   if(argc != 2)              C_USAGE(MSG_ERR_LESS_ARGS);
   if(argv[1][0] != '-')      C_USAGE(MSG_ERR_BAD_ARGS);

   switch(argv[1][1]) {
      case 'p':   /* power off */
         LOG(MSG_POWER_OFF);
         msg_reboot(CMD_POWEROFF);
         break;

      case 'h':   /* halt */
         LOG(MSG_HALT);
         msg_reboot(CMD_HALT);
         break;

      case 'r':   /* reboot */
         LOG(MSG_REBOOT);
         msg_reboot(CMD_REBOOT);
         break;

      case 's':   /* rescue */
         LOG(MSG_RESCUE);
         msg_reboot(CMD_RESCUE);
         break;

      case 'u':   /* update */
         LOG(MSG_UPDATE);
         msg_reboot(CMD_UPDATE);
         break;

      default:
         C_USAGE(MSG_ERR_BAD_ARGS);
         break;
   }
   return 0;
}
/* cinit-0.2 return codes implemented - nothing changed*/

}
