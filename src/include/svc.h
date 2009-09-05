/*******************************************************************************
 *
 * 2006-2009 Nico Schottelius (nico-cinit at schottelius.org)
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
 *    Service status (also exposed to the outside)
 */ 


#ifndef __CINIT_SVC_H
#define __CINIT_SVC_H

/***********************************************************************
 * The real status types a service may have (ignore above)
 * We have 32 Bits, we should use them ;-)
 */
enum cinit_svc_status {
   /* first define basics */
   CINIT_ST_SH_ONCE     = 0x1,     /* service SHould be started once          yx*/
   CINIT_ST_SH_RESPAWN  = 0x2,     /* service SHould respawn                  yx*/
   CINIT_ST_ONCE_OK     = 0x4,     /* service was successfully started once     */
   CINIT_ST_ONCE_FAIL   = 0x8,     /* service failed to start                   */
   CINIT_ST_RESPAWNING  = 0x10,    /* service is respawning                     */
   CINIT_ST_NEED_FAILD  = 0x20,    /* this service is not started, need failed x*/
   CINIT_ST_IN_LIST     = 0x40,    /* this service is being started (= in list) */
   CINIT_ST_BAD_ERR     = 0x80,    /* some kind of error that SHOULD NOT happen */
   CINIT_ST_ONCE_RUN    = 0x100,   /* the once process is currently running   yx*/
   CINIT_ST_NOT_EXIST   = 0x200,   /* there's no such service in our database   */
   CINIT_ST_SH_STOP     = 0x400,   /* service was running, is being stopped    x*/
   CINIT_ST_STOPPED     = 0x800,   /* service is stopped                       x*/
   CINIT_ST_STOP_FAIL   = 0x1000   /* service failed to stop..strange situation */
};

/***********************************************************************
 * Possibilities the needs of a service may have
 */
enum cinit_svc_needs_status {
   CINIT_SNS_NEEDS_STARTED = 1,  /* all needs are started. We may start, too  */
   CINIT_SNS_NEEDS_FAILED,       /* one ore more needs failed                 */
   CINIT_SNS_NEEDS_UNFINISHED    /* one ore more needs are not yet started    */
};
/***********************************************************************
 * How to start/stop a service
 */
enum cinit_svc_start_stop_options {
   CINIT_SSSO_COMPLETE     = 0x0,   /* with all dependencies   */
   CINIT_SSSO_WO_NEEDS     = 0x1,   /* without needs           */
   CINIT_SSSO_WO_WANTS     = 0x2,   /* without wants           */
   CINIT_SSSO_WO_BOTH      = 0x4    /* without both            */
};
#endif   /* _CINIT_SVC_H */
