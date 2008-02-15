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
 *    build **argv
 */

#ifndef CINIT_BA_HEADER
#define CINIT_BA_HEADER

/*****************************************************************************
 * Defines: return values
 */
enum {
   BA_OK,
   BA_E_NOTFOUND,
   BA_E_PARAMS,
   BA_E_ENV,
   BA_E_MEM,
   BA_E_OTHER
};

/*****************************************************************************
 * Structures
 */
struct ba_argv {
   char **argv;
   char **envp;
};

/*****************************************************************************
 * Functions
 */
int cinit_build_argv(char *basename, struct ba_argv *bav);

#endif
