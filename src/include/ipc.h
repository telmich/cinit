/*******************************************************************************
 *
 * 2006-2008 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Prototypes for ipc handler
 */

#ifndef CINIT_IPC_HEADER
#define CINIT_IPC_HEADER

/* FIXME: change to cinit/types.h later */
#include "cinit.h"

/*****************************************************************************
 * Functions: in server
 */
int cinit_ipc_init(void);        /* init in init                     */
int cinit_ipc_listen(void);      /* listen in init                   */
int cinit_ipc_sclose(void);      /* fork of cinit come from outside! */
int cinit_ipc_ssend(void *data); /* send to a client from the server */
void cinit_ipc_destroy(void);    /* destroy ipc handler in cinit     */

/*****************************************************************************
 * Functions: in clients
 */
int cinit_ipc_logon(void);                      /* logon to init     */

int cinit_ipc_connect(void);                    /* connect to init   */

int cinit_ipc_csend(struct cinit_question *);   /* ask the server    */
int cinit_ipc_cread(struct cinit_answer *);     /* read answer       */

int cinit_ipc_logoff(void);                     /* logoff            */

/*****************************************************************************
 * Functions: shared
 */

#endif
