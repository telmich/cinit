
/* 
 * (c) 2005 Nico Schottelius (nico-linux at schottelius.org)
 * run_svc
 * part of cinit
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
 * exec_svc: exec service abspath C_ON or C_OFF
 */

inline pid_t exec_svc(char *abspath, int action)
{
   int tmp;
   char *p, pathtmp[PATH_MAX];
   char *sbuf = NULL, **nargv = NULL, **nenv = NULL;
   int fd, argc;
   struct stat buf;

   cpid = fork();
   if(cpid == -1) {
      perror(MSG_ERR_FORK);
      return 0;
   }

   /***** PARENT ******/
   if(cpid > 0) {
      waitpid(cpid, &tmp, 0);
      if(WIFEXITED(tmp)) {
         if(!WEXITSTATUS(tmp)) {
            return cpid;
         }
      }
      SERVICE_LOG(abspath, LOG_SVC_FAIL);
      return 0;
   }

   /*********** CHILD EXECUTION ***********/
   strcpy(pathtmp, abspath);
   strcat(pathtmp, SLASH);

   if(action == CMD_START_SVC) {
      strcat(pathtmp, C_ON);
   } else {
      strcat(pathtmp, C_OFF);
   }

   /*
    * readlink retrieves real name, if it is a symlink 
    */
   if((tmp = readlink(pathtmp, pathtmp, PATH_MAX)) == -1) {

      /*
       * nothing there? fine, exit 
       */
      if(errno == ENOENT) {
         _exit(0);
      } else if(errno != EINVAL) {
         perror(MSG_READLINK);
         _exit(1);
      }

      /*
       * restore original name, file is not a link 
       */
      strcpy(pathtmp, abspath);
      strcat(pathtmp, SLASH);

      if(action == CMD_START_SVC) {
         strcat(pathtmp, C_ON);
      } else {
         strcat(pathtmp, C_OFF);
      }
      tmp = strlen(pathtmp);
   } else {
      /*
       * add '\0', readlink forgets it 
       */
      pathtmp[tmp] = '\0';
   }
   ++tmp;                       /* the byte to add to memory for \0; neither
                                 * readlink nor strlen count the \0 */

   /********** build argv0 ********/
   nargv = (char **) malloc(sizeof(char *));
   if(nargv == NULL)
      _exit(1);

   *nargv = (char *) malloc(tmp);
   if(*nargv == NULL)
      _exit(1);

   strcpy(*nargv, pathtmp);

   /********************** read params *********************/
   strcpy(pathtmp, abspath);
   strcat(pathtmp, SLASH);

   if(action == CMD_START_SVC) {
      strcat(pathtmp, C_ONARG);
   } else {
      strcat(pathtmp, C_OFFARG);
   }

   /*
    * open params file 
    */
   if(!stat(pathtmp, &buf)) {
      fd = open(pathtmp, O_RDONLY);

      if(fd == -1) {
         perror(MSG_ERR_OPEN);
         _exit(1);
      }

      argc = 0;

      /*
       * fill sbuf with content 
       */
      while((tmp = read(fd, pathtmp, PATH_MAX)) != 0) {
         if(tmp == -1) {
            perror(MSG_ERR_READ);
            _exit(1);
         }

         sbuf = realloc(sbuf, argc + tmp + 1);
         strncpy(&sbuf[argc], pathtmp, tmp);
         argc += tmp;
      }
      close(fd);

      if(argc) {
         sbuf[argc] = '\0';     /* terminate string */
      }
   } else {
      sbuf = NULL;
   }

   /************** build string **************/
   /*
    * The idea is to reuse the allocated memory. We'll simply * replace the \n
    * with \0 and set a char* to it. * We'll lose the last byte (the initial
    * \0), but we * don't care, as we die some seconds later with execv() * oh, 
    * we'll only lose it, if the file is terminated by \n 
    */

   argc = 1;                    /* argv0 */
   while(sbuf != NULL) {
      p = strchr(sbuf, '\n');
      nargv = realloc(nargv, sizeof(char *) * (argc + 1));

      if(nargv == NULL) {
         LOG(MSG_ERR_ALLOC);
         _exit(1);
      }

      /*
       * set to the beginning 
       */
      nargv[argc] = sbuf;

      /*
       * if we found \n 
       */
      if(p != NULL) {
         *p = '\0';
      } else {
         /*
          * set to the end of sbuf, not to the \0, but one before 
          */
         p = sbuf + (strlen(sbuf) - 1);
      }

      /*
       * if next byte is 0, the end of string is found 
       */
      if(*(p + 1) == '\0') {
         sbuf = NULL;
      } else {
         sbuf = p + 1;
      }
      ++argc;
   }

   /************ close argv list **************/
   nargv = realloc(nargv, sizeof(char *) * (argc + 1)); /* 1: NULL-pointer */
   if(nargv == NULL) {
      LOG(MSG_ERR_ALLOC);
      _exit(1);
   }
   nargv[argc] = NULL;          /* terminate argv list */

   /********************** read environment *********************/
   strcpy(pathtmp, abspath);
   strcat(pathtmp, SLASH);
   if(action == CMD_START_SVC) {
      strcat(pathtmp, C_ONENV);
   } else {
      strcat(pathtmp, C_OFFENV);
   }

   argc = 0;
   sbuf = NULL;
   if(!stat(pathtmp, &buf)) {
      fd = open(pathtmp, O_RDONLY);

      /*
       * file exists, failing to open it is an error 
       */
      if(fd == -1) {
         perror(MSG_ERR_OPEN);
         _exit(1);
      }

      while((tmp = read(fd, pathtmp, PATH_MAX)) != 0) {
         if(tmp == -1) {
            perror(MSG_ERR_READ);
            _exit(1);
         }

         sbuf = realloc(sbuf, argc + tmp + 1);
         strncpy(&sbuf[argc], pathtmp, tmp);
         argc += tmp;
      }
      close(fd);
      if(argc)
         sbuf[argc] = '\0';     /* terminate string */
   }

   /************** build environment string **************/
   argc = 0;
   while(sbuf != NULL) {
      p = strchr(sbuf, '\n');

      nenv = realloc(nenv, sizeof(char *) * (argc + 1));
      if(nenv == NULL) {
         LOG(MSG_ERR_ALLOC);
         _exit(1);
      }
      nenv[argc] = sbuf;

      /*
       * if we found \n 
       */
      if(p != NULL) {
         *p = '\0';
      } else {
         /*
          * set to the end of sbuf, not to the \0, but one before 
          */
         p = sbuf + (strlen(sbuf) - 1);
      }

      if(*(p + 1) == '\0') {
         sbuf = NULL;
      } else {
         sbuf = p + 1;
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

   execve(nargv[0], nargv, nenv);

   /*
    * we should never reach this block 
    */
   P_EXEC_FAILED(nargv[0]);
   perror(MSG_ERR_EXECVE);
   /*
    * FIXME: remove debug, remove double printing without loosing info 
    */
   sleep(3);                    /* debug */
   _exit(1);
}
