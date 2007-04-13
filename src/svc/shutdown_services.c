/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Shutdown all services
 */

void shutdown_services(void)
{
   /* ipc must be stopped before! */

   /* stop services in the correct order:
    * - begin at a random process, and walk the tree up to the wanted_by and needed_by
    * - switch to next service, as soon as this tree is finished
    */

   /* OR: create list of services that noone wants/needs
    * - fillup this list everytime a service si not wanted/needed by others anymore
    */
   return;
}
