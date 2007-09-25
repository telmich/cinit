/*************
 *
 * A very small program to show that the child() of a fork()
 * proceess can exit before fork() returns in the parent
 *
 * Nico Schottelius, Copying: GPLv3, 20070925
 *
 * I run it this way: ./fork-latency | grep "child exited" | sort | uniq | wc -l
 *    => Number of children that exited before we recorded them!
 *
 * Or: ./fork-latency | grep "found" | sort | uniq | wc -l
 *    => children, which exited after fork() returned.
 *
 * Some interesting facts:
 *
 *    - Very often the children exit before fork() returns:
 *
 *    [8:58] denkbrett:test% ./fork-latency | grep "found" | sort | uniq | wc -l
 *    2
 *
 *    - It looks like waitpid() returns more than once the same pid (MAX=500):
 *
 *    [9:01] denkbrett:test% ./fork-latency | grep "child exited before fork" | wc -l
 *    8435
 *
 *    [9:02] denkbrett:test% ./fork-latency | grep "found" | wc -l
 *    111
 *
 *    [9:02] denkbrett:test% ./fork-latency | grep "found" > TMP  
 *    [9:03] denkbrett:test% head TMP 
 *    (475) found
 *    (475) found
 *    (475) found
 *    (374) found
 *    (374) found
 *    (374) found
 *    (374) found
 *    (373) found
 *    (374) found
 *    (374) found
 *
 *
 *    Imho waitpid() should return 0, because we specified WNOHANG and
 *    SA_NOCLDSTOP, if no child changed status
 */


#include <unistd.h>        /* fork()                     */
#include <signal.h>        /* sigaction, sigemtpyset     */
#include <sys/wait.h>      /* waitpid                    */
#include <stdio.h>         /* printf, NULL               */

#define MAX 500            /* number of forks            */

pid_t list[MAX];
int      i=MAX;

void sig_child(int status)
{
   int o;
   int found;
   pid_t pid;

   while((pid = waitpid(-1, &status, WNOHANG)) > 0) {
      if(pid == -1) return; /* ignore errors */

      found = 0;
      // no need to search the whole list, use o = i instead
      //for(o = 0; o < MAX; o++) {
      for(o = i; o < MAX; o++) {
         if(list[o] == pid) {
            found = 1;
            break;
         }
      }
      if(found) {
         printf("(%d) found\n", i);
      } else {
         printf("(%d) child exited before fork() returned\n", i);
      }
   }
}

int main()
{
   struct sigaction sa;
   sigemptyset(&sa.sa_mask);

   sa.sa_flags = 0;
   sa.sa_handler  = sig_child;
   sa.sa_flags    = SA_NOCLDSTOP;
   sigaction(SIGCHLD,&sa,NULL);

   for(i=MAX-1; i >= 0; i--) list[i] = 0;

   i=MAX;
   
   for(i = MAX-1;i >= 0; i--) {
      list[i] = fork();

      /* child exists immediately */
      if(list[i] == 0) return 0;
   }
}
