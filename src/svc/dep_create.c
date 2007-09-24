/***********************************************************************
 * 
 *    2006 Nico Schottelius (nico-cinit at schottelius.org)
 * 
 *    part of cLinux/cinit
 * 
 *    Create dependency
 */

#include <stdio.h>         /* NULL              */
#include <stdlib.h>        /* malloc()          */
#include "svc-intern.h"    /* structs           */

/* search for an entry by path, reverse: from end to the beginning */
struct dep *dep_create(struct listitem *svc)
{
   struct dep *entry;

   entry = malloc(sizeof(struct dep));
   if(!entry) return NULL;
   entry->svc = svc;

   return entry;
}
