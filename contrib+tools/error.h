#ifndef ERROR_H
#define ERROR_H
/**
  (c) 2005 Peter Portmann (pp at bluewin.ch)
  error.h
      
  This script is written for the clinux-System and published
  under the terms of GPL 2.0

  Version: 0.1

  ChangeLog:

  Todo:

  Features:
*/

#define  WARNING      0 
#define  WARNING_SYS  1
#define  FATAL        2
#define  FATAL_SYS    3
#define  DUMP         4

void  log_msg(int kennung, const char *fmt, ...);
void  err_msg(int kennung, const char *fmt, ...);


#endif
