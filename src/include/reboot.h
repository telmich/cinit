/*******************************************************************************
 *
 * 2007-2008 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    reboot specific functions
 *
 */

#ifndef CINIT_REBOOT_HEADER
#define CINIT_REBOOT_HEADER

/*****************************************************************************
 * the main reboot function
 */
void     do_reboot(int signal);


/*****************************************************************************
 * os specific functions
 */
void cinit_reboot(void);
void cinit_halt(void);
void cinit_poweroff(void);


/*****************************************************************************
 * Functions: abstract do_reboot
 */
#define cinit_do_reboot()     do_reboot(SIGHUP)
#define cinit_do_halt()       do_reboot(SIGUSR1)
#define cinit_do_poweroff()   do_reboot(SIGTERM)

#endif
