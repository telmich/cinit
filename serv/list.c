/* (c) 2005 by Marcus Przyklink (downhill-clinux (at) burningchaos.org)
 * list handling: the processes cinit will execute/executed
 * part of cinit
 * changed some formatting, Nico Schottelius
 */

#include <stdlib.h>
#include <string.h>
#include "cinit.h"


int list_insert(char *path, int status)
{
   struct listitem *tmp;

   tmp = malloc( sizeof(struct listitem) );

   if( tmp == NULL ) {
      return 0;
   }


   if( list == NULL ) { /* list is empty, we have to init it */
      list = tmp;
      list->after    = list;
      list->before   = list;
   } else {             /* list has members, add this one */
      tmp->after           = list;  /* after the new element comes the begin */
      tmp->before          = list->before;   /* change to the ex-last */
      list->before->after  = tmp;   /* change last element */
      list->before         = tmp;   /* first element has us as previous now */
   }

   tmp->abs_path = malloc( strlen(path) + 1);
   if( tmp->abs_path == NULL ) {
      LOG(MSG_ERR_ALLOC);
      return 0;
   }

   strcpy(tmp->abs_path,path);
   tmp->status = status;
   tmp->pid    = 0;
   
   return 1;
}

/* search for an entry by path, reverse: from end to the beginning */
struct listitem *list_search(char *path)
{
   struct listitem *tmp;

   if( list == NULL ) { /* think positive */
      return NULL;
   } else {
      tmp = list;
   }

   do {
      if( !strcmp(path, tmp->abs_path) ) {
         return tmp;
      }
      tmp = tmp->before;
   } while(tmp != list);
   
   return NULL;
}

int list_delete(char *path)
{
   struct listitem *tmp;

   tmp = list_search(path);

   if( tmp == NULL ) {
      return 0;
   }

   tmp->after->before = tmp->before;
   tmp->before->after = tmp->after;
   free(tmp->abs_path);
   free(tmp);
   return 1;
}

/* change pid and status of a process */
int list_modify(char *path, int new_status, pid_t new_pid)
{
   struct listitem *tmp;

//   D_PRINTF(path);
   
   tmp = list_search(path);
   if( tmp == NULL ) {
      return 0;
   }

   /* delete objects, which are killed */
   if(new_status == ST_OFF) {
      return list_delete(path);
   } else {
      tmp->status = new_status;
      tmp->pid    = new_pid;
   }

   return 1;
}
