/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Prototypes for ipc handler
 */

#ifndef CINIT_IPC_HEADER
#define CINIT_IPC_HEADER

/*****************************************************************************
 * Functions
 */
int cinit_ipc_init(void);        /* init in init      */
int cinit_ipc_listen(void);      /* listen in init    */
int cinit_ipc_logoff(void);      /* logoff from init  */

int cinit_ipc_logon(void);       /* logon to init     */
int cinit_ipc_connect(void);     /* connect to init   */

#endif
