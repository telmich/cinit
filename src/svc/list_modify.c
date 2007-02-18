/***********************************************************************
 * 
 *    (c) 2005 Marcus Przyklink (downhill-clinux (at) burningchaos.org)
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    OBSOLETED. Not in use anymore.
 * 
 *    part of cLinux/cinit
 * 
 *    List handling
 */

#include <stdlib.h>
#include <string.h>
#include "cinit.h"
#include "comm.h"    /* for ST_OFF */
#include "svc.h"    /* for ST_OFF */

/* change pid and status of a process */
int list_modify(char *path, int new_status, pid_t new_pid)
{
   struct listitem *tmp;

   tmp = list_search(path);
   if(tmp == NULL) {
      return 0;
   }

   /* delete objects, which are killed */
   if(new_status == ST_OFF) {
      return list_delete(path);
   } else {
      tmp->status = new_status;
      tmp->pid    = new_pid;
   }

   return 1;
}
