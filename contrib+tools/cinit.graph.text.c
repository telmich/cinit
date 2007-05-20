/**
  (c) 2005 Peter Portmann (pp at bluewin.ch)
  cinit.graph.text.c
      
  This script is written for the clinux-System and published
  under the terms of GPL 2.0

  Version: 0.2

  ChangeLog:
    Version 0.2 (Peter Portmann):
      * Not assigned link destinies are marked by (!).
      * Not readable directories are marked by "directory not readable".
    
    Version 0.1 (Peter Portmann):
      * Print of the directory structure of the contained files and links
        without following the links.

  Todo:

  Features:
*/
 
//#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
//#include "cinit.h"
#include "error.h"

#define FTW_F 1   /* file isn't a directory */
#define FTW_D 2   /* file is a directory */
#define FTW_DNR 3 /* not readable directory */
#define FTW_NS 4  /* unsuccesfully stat on this file */
#define MAX_CHAR   4096

/***********************************************************************
 * cinit.graph.text - textual representation of the cinit directory
 */

#define CSERVICE_BANNER    "cinit.graph.text - textual representatio of the cinit directory\n\n"
#define USAGE_TEXT         "\n\nUsage:\n\ncinit.graph.text <path>\n"  \
   "\tpath\t- cinit installationpath\n"

typedef int EACH_ENTRY(const char *, const struct stat *, int);
typedef enum  { FALSE=0, TRUE=1 }  bool;

static char dirpath[PATH_MAX];
static int depth = 0;
static long int filecount = 0;

static EACH_ENTRY each_entry;
static int pp_ftw(char *, EACH_ENTRY *);
static int each_getinfo(EACH_ENTRY *);

/***********************************************************************
 * pp_ftw: file tree walk
 */
static int pp_ftw(char *filepath, EACH_ENTRY *function)
{
   int n;

   if(chdir(filepath) < 0) /* In angegebenen Pfad wechseln */
      err_msg(FATAL_SYS, "can't change to %s", filepath);

   if(getcwd(dirpath, PATH_MAX) == 0) /* Absoluten Pfadnamen ermitteln */
      err_msg(FATAL_SYS, "error using getcwd for %s", filepath);

   n = each_getinfo(function);

   return(n);
}

/***********************************************************************
 * each_getinfo: get more info for each file.
 */
static int each_getinfo(EACH_ENTRY *function)
{
   struct stat statpuff;
   struct dirent *direntz;
   DIR *dirz;
   int n;
   char *zgr;

   if(lstat(dirpath, &statpuff) < 0)
      return(function(dirpath, &statpuff, FTW_NS)); /* Error on stat */

   if(S_ISDIR(statpuff.st_mode) == 0)
      return(function(dirpath, &statpuff, FTW_F)); /* no directory */

   /* It's a directory.
    * Call function() for it. After that handel each file in the directory. */

   if((dirz = opendir(dirpath)) == NULL) { /* Directory not readable */
      closedir(dirz);
      return(function(dirpath, &statpuff, FTW_DNR));
   }

   if((n = function(dirpath, &statpuff, FTW_D)) != 0) /* return the directorydirpath */
      return(n);

   zgr = dirpath + strlen(dirpath); /* append slash to the dirpathname */
   *zgr++ = '/';
   *zgr = '\0';

   while((direntz = readdir(dirz)) != NULL) {
      /* ignor . and .. */
      if(strcmp(direntz->d_name, ".") && strcmp(direntz->d_name, "..")) {
         strcpy(zgr, direntz->d_name); /* append filename after slash */
         depth++;
         if(each_getinfo(function) != 0) { /* Recursion */
            depth--;
            break;
         }
         depth--;
      }
   }
   *(zgr-1) = '\0'; /* deleting evrything after the slash */

   if(closedir(dirz) < 0)
      err_msg(WARNING, "closedir for %s failed", dirpath);

   return(n);
}

/***********************************************************************
 * each_entry: handling each file and build the graph step by step.
 */
static int each_entry(const char *filepath, const struct stat *statzgr, int filetype)
{
   struct stat statpuff;
   static bool erstemal=TRUE;
   int i;
 
   char link[MAX_CHAR];

   filecount++;
   if(!erstemal) {
      for(i=1 ; i<=depth ; i++)
         printf("%4c|", ' ');
      printf("----%s", strrchr(filepath, '/')+1);
   } else {
      printf("%s", filepath);
      erstemal = FALSE;
   }

   switch(filetype) {
      case FTW_F:
         switch(statzgr->st_mode & S_IFMT) {
            case S_IFREG: break;
            case S_IFCHR: printf(" c"); break;
            case S_IFBLK: printf(" b"); break;
            case S_IFIFO: printf(" f"); break;
            case S_IFLNK: 
               printf(" -> "); 
               if(( i=readlink(filepath, link, MAX_CHAR)) != -1)
                  printf("%.*s", i, link);
                  if(stat(filepath, &statpuff) < 0)
                     printf(" (!)");
               break;
            case S_IFSOCK: printf(" s"); break;
            default: printf(" ?"); break;
         }
         printf("\n");
         break;

      case FTW_D:
         printf("/\n");
         break;

      case FTW_DNR:
         printf("/ directory not readable\n");
         break;

      case FTW_NS:
         err_msg(WARNING_SYS, "Error using 'stat' on file %s", filepath);
         break;

      default:
         err_msg(FATAL_SYS, "Unknown Filetype (%d) by file %s", filetype, filepath);
         break;
   }

   return(0);
}

/***********************************************************************
 * main:
 */
int main(int argc, char *argv[])
{
   if(argc != 2)
      usage(CSERVICE_BANNER, USAGE_TEXT);

   exit(pp_ftw(argv[1], each_entry));
}
