/**  
  (c) 2005 Peter Portmann (pp at bluewin.ch)
  error.c
      
  This script is written for the clinux-System and published
  under the terms of GPL 2.0

  Version: 0.1

  ChangeLog:

  Todo:

  Features:
*/

#include "error.h"
#include <errno.h>
#include <stdio.h>
#include <stdarg.h>
#include <syslog.h>
#include <string.h>
#include <stdlib.h>

#define  MAX_CHAR   4096

int  debug; /* Aufrufer von log_msg oder log_open muss debug setzen:
               0, wenn interaktiv; 1, wenn Daemon-Prozess */

/*---- Lokale Routinen zur Abarbeitung der Argumentliste --------------------*/
static void msg_err(int sys_msg, const char *fmt, va_list az)
{
   int  fehler_nr = errno;
   char puffer[MAX_CHAR];
   
   vsprintf(puffer, fmt, az);
   if (sys_msg)
      sprintf(puffer+strlen(puffer), ": %s ", strerror(fehler_nr));
   fflush(stdout);   /* fuer Fall, dass stdout und stderr gleich sind */
   fprintf(stderr, "%s\n", puffer);
   fflush(NULL);  /* alle Ausgabepuffer flushen */
   return;
}

static void msg_log(int sys_msg, int prio, const char *fmt, va_list az)
{
   int  fehler_nr = errno;
   char puffer[MAX_CHAR];
   
   vsprintf(puffer, fmt, az);
   if (sys_msg)
      sprintf(puffer+strlen(puffer), ": %s ", strerror(fehler_nr));
   if (debug) {
      fflush(stdout);   /* fuer Fall, dass stdout und stderr gleich sind */
      fprintf(stderr, "%s\n", puffer);
      fflush(NULL);  /* alle Ausgabepuffer flushen */
   } else {
      strcat(puffer, "\n");
      syslog(prio, puffer);
   }
   return;
}

/*---- Global aufrufbare Fehlerroutinen -------------------------------------*/
void  err_msg(int kennung, const char *fmt, ...)
{
   va_list     az;
   
   va_start(az, fmt);
   switch (kennung) {
      case WARNING:
      case FATAL:
              msg_err(0, fmt, az);
              break;
      case WARNING_SYS:
      case FATAL_SYS:
      case DUMP:
              msg_err(1, fmt, az);
              break;
       default:
              msg_err(1, "Falscher Aufruf von err_msg...", az);
              exit(3);
   }
   va_end(az);

   if (kennung==WARNING || kennung==WARNING_SYS)
      return;
   else if (kennung==DUMP)
      abort();  /* core dump */
   exit(1);
}

void  log_msg(int kennung, const char *fmt, ...)
{
   va_list     az;
   
   va_start(az, fmt);
   switch (kennung) {
      case WARNING:
      case FATAL:
              msg_log(0, LOG_ERR, fmt, az);
              break;
      case WARNING_SYS:
      case FATAL_SYS:
              msg_log(1, LOG_ERR, fmt, az);
              break;
       default:
              msg_log(1, LOG_ERR, "Falscher Aufruf von log_msg...", az);
              exit(3);
   }
   va_end(az);

   if (kennung==WARNING || kennung==WARNING_SYS)
      return;
   exit(2);
}

/*---- log_open ---------------------------------------------------------------
           initialisiert syslog() bei einem Daemon-Prozess                   */
void  log_open(const char *kennung, int option, int facility)
{
   if (debug==0)
      openlog(kennung, option, facility);
}
