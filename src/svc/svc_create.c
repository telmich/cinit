/***********************************************************************
 *
 *    2005-2007 Nico Schottelius (nico-cinit at schottelius.org)
 *
 *    part of cLinux/cinit
 *
 *    Check whether service is existent
 */

#include <stdio.h>      /* NULL           */
#include <string.h>     /* strcpy         */
#include <unistd.h>     /* stat           */
#include <sys/stat.h>   /* stat           */
#include <limits.h>     /* PATH_MAX       */
#include <errno.h>      /* errno          */
#include "svc.h"        /* listitem       */
#include "cinit.h"      /* path_append    */

/* checking for existence is done before! */
/* FIXME: check heedars for conformance with POSIX */
struct listitem *svc_create(char *svc)
{
   char              buf[PATH_MAX+1];
   struct stat       statbuf;
   struct listitem   *li;
   
   li = list_insert(svc,-1);
   if(!li) return NULL;

   /* FIXME: add two path length checks? svc and svc+strlen(C_RESPAWN)? */
   strcpy(buf,svc);
   if(!path_append(buf,C_RESPAWN)) return NULL;

   if(stat(buf,&statbuf) == -1) {
      if(errno == ENOENT) {
         svc_set_status(li,ST_SH_ONCE);
      } else {
         return NULL;
      }
   } else {
      /* FIXME remove debug */
      mini_printf("respawn: ",1);
      mini_printf(li->abs_path,1);
      mini_printf("\n",1);
      svc_set_status(li,ST_SH_RESPAWN);
   }

   return li;
}
