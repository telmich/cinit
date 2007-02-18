/***********************************************************************
 *
 *    2006-2007 Nico Schottelius (nico-linux-cinit schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Close the ressources from the server, clean state for forks.
 *
 */

int cinit_ipc_sclose(void)
{
   return 1;   /* nothing to do when using message queues */
}
