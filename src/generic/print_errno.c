
/***********************************************************************
 *
 *    stolen from tcpserver_blocker
 *
 *    Author: Nico Schottelius
 *    Date: 2006-08-24
 *
 *    Print the error found in errno
 */

#include <string.h>             /* strerror */
#include <errno.h>              /* errno */

#include "intern.h"             /* mini_printf, PD_ERR */

void print_errno(char *msg)
{
   if(msg) {
      mini_printf(msg, FD_ERR);
      mini_printf(": ", FD_ERR);
   }
   mini_printf(strerror(errno), FD_ERR);
   mini_printf("\n", FD_ERR);
}
