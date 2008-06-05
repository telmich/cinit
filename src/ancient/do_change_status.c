
/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * change status of a service
 * part of cinit
 */

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>

#include "cinit.h"

/* client:
 *    svc = service name
 *    status = status
 *    pid = pid
 *    sock2 = sock
 *    action = ACT_WRITE
 *    return: error code
 *
 * server:
 *    svc = buffer
 *    status = where to save status
 *    svc = bufferTH_MAX
 *    pid = where to save pid
 *    sock2 = nsock
 *    action = ACT_READ
 *    return: read service lenght
 */

int do_change_status(char *svc, char *status, pid_t * pid, int sock2,
                     int action)
{
   int tmp;

   ssize_t(*fpoint) (int, void *, size_t);

   if(action == ACT_SERV) {
      fpoint = read;
   } else {
      fpoint = (ssize_t(*)(int, void *, size_t)) write;
      tmp = strlen(svc);
   }

   if(fpoint(sock2, &tmp, sizeof(tmp)) == -1) { /* length */
      perror(MSG_ERR_IO);
      return 0;
   }

   if(tmp > PATH_MAX) {
      return 0;
   }

   if(fpoint(sock2, svc, tmp) == -1) {  /* write service name */
      perror(MSG_ERR_IO);
      return 0;
   }

   if(fpoint(sock2, status, sizeof(*status)) == -1) {   /* status */
      perror(MSG_ERR_IO);
      return 0;
   }

   if(fpoint(sock2, pid, sizeof(*pid)) == -1) { /* PID */
      perror(MSG_ERR_IO);
      return 0;
   }

   return tmp;
}
