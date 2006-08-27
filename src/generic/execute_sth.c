/***********************************************************************
 *
 *    2006 Nico Schottelius (nico-linux-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Execute something 
 */

#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include "cinit.h"

/***********************************************************************
 *
 * TODO: add a forking and a non-forking version: fork: other file!
 *
 * Return values:
 * - Does not return on success.
 * - could not find params
 * - could not execute 
 *

 
 *
 * char *basename: something we should execute
 * (*basename) + ".params" will be added as parameters
 * (*basename) + ".env" will be added as environment
 *
 */

#define RET_EXEC_NOTFOUND     1
#define RET_EXEC_RDLINK       2

int execute_sth(char *basename)
{
   int tmp;
   char *p, pathtmp[PATH_MAX+1];
   char *sbuf = NULL, **nargv = NULL, **nenv = NULL;
   int fd, argc;
   struct stat buf;
   
   /* STOPPED HERE */
   /* Try to get realname (for links) */
   if ( ( tmp = readlink(basename,pathtmp,PATH_MAX) ) == -1) {

      /* nothing there? */
      if(errno == ENOENT) {
         return RET_EXEC_NOTFOUND;
      } else if (errno != EINVAL) {
         perror(MSG_READLINK);
         return RET_EXEC_RLDLINK;
      }
      
      /* add '\0', readlink does not add it */
      pathtmp[tmp] = '\0'; 

   } else {
      /* original filename, no link */
      strcpy(pathtmp,abspath);
      tmp=strlen(pathtmp);
   }
   ++tmp; /* the byte to add to memory for \0;
             neither readlink nor strlen count the \0 */
   
   /* stopped */

   /********** build argv0 ********/
   nargv = (char **) malloc( sizeof(char *) );
   if(nargv == NULL) _exit(1);

   *nargv = (char *) malloc( tmp );
   if(*nargv == NULL) _exit(1);

   strcpy(*nargv,pathtmp);

   /********************** read params *********************/
   strcpy(pathtmp,abspath);
   strcat(pathtmp,SLASH);

   if(action == CMD_START_SVC) {
      strcat(pathtmp,C_ONARG);
   } else {
      strcat(pathtmp,C_OFFARG);
   }

   /* open params file */
   if( !stat(pathtmp,&buf) ) {
      fd = open(pathtmp,O_RDONLY);

      if(fd == -1) {
         perror(MSG_ERR_OPEN);
         _exit(1);
      }

      argc = 0;

      /* fill sbuf with content */
      while ( (tmp = read(fd,pathtmp,PATH_MAX) ) != 0 ) {
         if(tmp == -1) { 
            perror(MSG_ERR_READ);
            _exit(1);
         }

         sbuf = realloc(sbuf,argc + tmp + 1);
         strncpy(&sbuf[argc],pathtmp,tmp);
         argc += tmp;
      }
      close(fd);

      if(argc) {
         sbuf[argc] = '\0'; /* terminate string */
      }
   } else {
      sbuf = NULL;
   }

   /************** build string **************/
   /* The idea is to reuse the allocated memory. We'll simply
   * replace the \n with \0 and set a char* to it.
   * We'll lose the last byte (the initial \0), but we
   * don't care, as we die some seconds later with execv()
   * oh, we'll only lose it, if the file is terminated by \n */
   
   argc = 1; /* argv0 */
   while( sbuf != NULL) {
      p = strchr(sbuf,'\n');
      nargv = realloc(nargv, sizeof(char *) * (argc + 1));

      if(nargv == NULL) {
         LOG(MSG_ERR_ALLOC);
         _exit(1);
      }

      /* set to the beginning */
      nargv[argc] = sbuf;
      
      /* if we found \n */
      if(p != NULL) {
         *p = '\0';
      } else {
         /* set to the end of sbuf, not to the \0, but one before */
         p = sbuf + (strlen(sbuf)-1); 
      }
      
      /* if next byte is 0, the end of string is found */
      if( *(p+1) == '\0') {
         sbuf = NULL;
      } else {
         sbuf = p+1;
      }
      ++argc;
   }

   /************ close argv list **************/
   nargv = realloc(nargv, sizeof(char *) * (argc + 1)); /* 1: NULL-pointer */
   if(nargv == NULL) {
      LOG(MSG_ERR_ALLOC);
      _exit(1);
   }
   nargv[argc] = NULL;  /* terminate argv list */

   /********************** read environment *********************/
   strcpy(pathtmp,abspath);
   strcat(pathtmp,SLASH);
   if(action == CMD_START_SVC) {
      strcat(pathtmp,C_ONENV);
   } else {
      strcat(pathtmp,C_OFFENV);
   }

   argc = 0;
   sbuf = NULL;
   if( !stat(pathtmp,&buf) ) {
      fd = open(pathtmp,O_RDONLY);

      /* file exists, failing to open it is an error */
      if(fd == -1) {
         perror(MSG_ERR_OPEN);
         _exit(1);
      }

      while ( (tmp = read(fd,pathtmp,PATH_MAX) ) != 0 ) {
         if(tmp == -1) { 
            perror(MSG_ERR_READ);
            _exit(1);
         }

         sbuf = realloc(sbuf,argc + tmp + 1);
         strncpy(&sbuf[argc],pathtmp,tmp);
         argc += tmp;
      }
      close(fd);
      if(argc)
         sbuf[argc] = '\0'; /* terminate string */
   }

   /************** build environment string **************/
   argc = 0;
   while( sbuf != NULL ) {
      p = strchr(sbuf,'\n');
         
      nenv = realloc(nenv, sizeof(char *) * (argc + 1));
      if(nenv == NULL) {
         LOG(MSG_ERR_ALLOC);
         _exit(1);
      }
      nenv[argc] = sbuf;

      /* if we found \n */
      if(p != NULL) {
         *p = '\0';
      } else {
         /* set to the end of sbuf, not to the \0, but one before */
         p = sbuf + (strlen(sbuf)-1); 
      }

      if( *(p+1) == '\0') {
         sbuf = NULL;
      } else {
         sbuf = p+1;
      }
      ++argc;
   }

   /************ close env list **************/
   nenv = realloc(nenv, sizeof(char *) * (argc + 1));
   if(nenv == NULL) {
      LOG(MSG_ERR_ALLOC);
      _exit(1);
   }
   nenv[argc] = NULL;

   /****************** EXECUTE ********************/

   execve(nargv[0],nargv,nenv);

   /* we should never reach this block */
   P_EXEC_FAILED(nargv[0]);
   perror(MSG_ERR_EXECVE);
   /* FIXME: remove debug, remove double printing without loosing info */
   sleep(3); /* debug */
   _exit(1);
}
