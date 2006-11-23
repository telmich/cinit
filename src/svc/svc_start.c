/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Start a service
 */

#include <stdio.h>        /* DEBUG        */

#include <unistd.h>        /* fork        */
#include <string.h>        /* strerror    */
#include <errno.h>         /* errno       */
#include <limits.h>        /* PATH_MAX    */
#include "svc.h"           /* struct *    */
#include "messages.h"      /* MSG_*       */
#include "cinit.h"         /* execute_sth */

void svc_start(struct listitem *li)
{
   char buf[PATH_MAX+1];

   li->pid = fork();

   if(li->pid < 0) {
      svc_report_status(li->abs_path,MSG_SVC_FORK,strerror(errno));
      svc_set_status(li,ST_BAD_ERR);
      return;
   }
   if(li->pid > 0) {
      if(li->status & ST_SH_ONCE)
         li->status = ST_ONCE_OK;
      else
         li->status = ST_RESPAWNING;
      return;
   }

   /* Client: FIXME: check for valid length!
    * strlen(abs_path) + strlen(SLASH) + strlen(C_ON) */
   /* misuse status field (doesn't matter in fork) for strlen */
   li->status = strlen(li->abs_path);
   strncpy(buf,li->abs_path,li->status);
   buf[li->status] = '\0';
   printf("buf1: %s\n",buf);
   printf("buf-orig: %s\n",li->abs_path);
   strncat(buf,SLASH,PATH_MAX);
   printf("buf2: %s\n",buf);
   strncat(buf,C_ON,PATH_MAX);
   printf("buf3: %s\n",buf);

   mini_printf("SS::",1);
   mini_printf(li->abs_path,1);
   mini_printf("::",1);
   mini_printf(buf,1);
   mini_printf("\n",1);
   execute_sth(buf);
}
