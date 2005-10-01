/* 
 * (c) 2005 Nico Schottelius (nico-linux-cinit at schottelius.org)
 * run_svc
 * part of cinit
 */

/* headers are clean */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdio.h>
#include <time.h>

#include "cinit.h"

/***********************************************************************
 * run_svc: run a service and before all dependencies
 */
int run_svc(char *rpath)
{
   int tmp;
   pid_t pid;
   char abspath[PATH_MAX], pathtmp[PATH_MAX]; /* pathtmp = use-it-for-all bitch*/
   struct stat buf;
   struct timespec ts;
   
   /******************* absolute PATH ***************/
   /* get current working dir */
   if(! (int) getcwd(pathtmp,PATH_MAX)) {
      perror(pathtmp);
      return RT_UNSPEC;
   }

   /* change to rpath */
   if(chdir(rpath) == -1) {
      perror(rpath);
      return RT_NOTEXIST;
   }

   /* get absolute name of rpath */
   if(! (int) getcwd(abspath,PATH_MAX)) {
      perror(abspath);
      return RT_UNSPEC;
   }

   /* change back */
   if(chdir(pathtmp) == -1) {
      perror(pathtmp);
      return RT_UNSPEC; 
   }
   D_PRINTF(abspath);
   
   /******************* REGISTER SERVICE ***************/
   do {
      tmp = msg_svc_on_off(abspath,CMD_START_SVC);    /* check status */
      
      switch(tmp) {
         case ST_FAIL:     /* somebody failed before, we won't retry */
            return RT_SVC_FAILED;
            break;
         case ST_TMP: /* someone is working on it */
            ts.tv_sec = SLEEP_RERUN;
            nanosleep(&ts,NULL);
            break;
         case ST_ONCE:        /* somebody did our work */
         case RT_ERR_COMM:    /* communication failed */
         case ST_RESPAWN:     /* somebody does our work */
         case ST_NEED_FAIL:   /* the needs failed before */
            return tmp;
            break;
         case RT_TMPNOW:      /* do not go to default: */
            break;
         default:
            mini_printf(MSG_SHOULD_NOT_HAPPEN,1);
            return RT_UNSPEC;
            break;
      }
   } while(tmp != RT_TMPNOW);

   /******************* BEGIN DEPENDENCIES ***************/
   strcpy(pathtmp,abspath);
   strcat(pathtmp,SLASH);
   strcat(pathtmp,C_NEEDS);
   
   /* check for needs */
   if( stat(pathtmp,&buf) == 0 ) {
      if( ! run_run_svcs(pathtmp) ) {
         SERVICE_LOG(abspath,LOG_NEED_FAIL);
         msg_change_status(abspath, ST_NEED_FAIL, 0);
         return ST_NEED_FAIL;
      }
   }
   
   /********** WANTS ************/
   strcpy(pathtmp,abspath);
   strcat(pathtmp,SLASH);
   strcat(pathtmp,C_WANTS);

   if( stat(pathtmp,&buf) == 0 ) {
      run_run_svcs(pathtmp);  /* don't care about what happens with the want svc */
   }

   /******************* execute services ***************/
   strcpy(pathtmp,abspath);
   strcat(pathtmp,SLASH);
   strcat(pathtmp,C_RESPAWN);
   
   if( stat(pathtmp,&buf) == 0) {
      pid = respawn_svc(abspath);
      tmp = ST_RESPAWN;
   } else {
      pid = exec_svc(abspath, CMD_START_SVC);
      tmp = ST_ONCE;
   }

   if(!pid) {
      msg_change_status(abspath, ST_FAIL, pid);
      return ST_FAIL;
   }

   if(!msg_change_status(abspath, tmp, pid) ) {
      return RT_ERR_COMM;
   }

   return tmp;    /* ST_ONCE || ST_RESPAWN */
}
/* cinit-0.2 return codes implemented */
