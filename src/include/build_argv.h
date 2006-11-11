/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit //@\\ schottelius.org)
 *
 *    part of cLinux/cinit
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
