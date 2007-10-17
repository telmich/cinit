/***********************************************************************
 *
 *    2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Stop a service
 */

#include <stdio.h>         /* NULL              */
#include <unistd.h>        /* fork              */
#include <string.h>        /* strerror          */
#include <errno.h>         /* errno             */
#include <limits.h>        /* PATH_MAX          */

#include "svc.h"           /* struct *          */
#include "svc-intern.h"    /* struct *          */
#include "messages.h"      /* MSG_*             */
#include "intern.h"        /* execute_sth       */

extern int svc_lock;

/*
 * respawn:
 *    - disable respawning: set status to ST_RESPAWN_STOP
 *    - send term signal? no => can be done in "off"
 *       => set environment CINIT_SVC_PID
 * once and respawn:
 *    - look for 'off' binary, execute if present
 *    - mark service as off or delete it?
 */


void svc_stop(struct listitem *li)
{

   char buf[PATH_MAX+1];

   svc_set_status(li, CINIT_ST_STOPPING);

   /**********************      Error      ************************/
   if(li->pid < 0) {
      svc_report_status(li->abs_path, MSG_SVC_FORK, strerror(errno));
      svc_set_status(li, CINIT_ST_BAD_ERR);
      return;
   }
   
   /********************** Client / fork() ************************/
   svc_report_status(li->abs_path, MSG_SVC_STOP, NULL);

   strcpy(buf, li->abs_path);    /* length check is done by path_append */
   if(!path_append(buf, C_OFF))  _exit(1);

   /* Check for existence */
   li->status = file_exists(buf);

   if(li->status == FE_NOT) {
      _exit(0);
   }

   if(li->status == FE_FILE) {
      /* FIXME: reset signals: Is this necessary? Or does fork clean it anyway? */
      set_signals(ACT_CLIENT);

      /* and now, fire it up */
      execute_sth(buf);
   } else {
      /* FIXME: report? */
      /* either no file or an error */
      _exit(1);
   }
}
