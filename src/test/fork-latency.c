/*************
 *
 * A very small program to show that the child() of a fork()
 * proceess can / CANNOT exit before fork() returns in the parent
 *
 * Nico Schottelius, Copying: GPLv3, 20070925
 *
 * I run it this way:
 
 * % ./fork-latency | grep "Unknown child exited" | sort | uniq | wc -l
 *       => Number of children that exited before we recorded them! (should be 0)
 *
 * % ./fork-latency | grep "found" | sort | uniq | wc -l
 *    => children, which exited after fork() returned.
 *
 * % ./fork-latency | grep "found" | wc -l
 *    => should equal MAX (see sourcecode)
 *
 * % ./fork-latency | wc -l
 *    => should also equal MAX (see sourcecode)
 *
 * Some interesting facts:
 *
 *    - With MAX=5000 I get: 
 *
 *    [20:02] ikn:test% ./fork-latency | grep "found" | wc -l              
 *    731705
 *    [20:03] ikn:test% ./fork-latency |  wc -l                            
 *    734683
 *
 * [20:04] ikn:test% ./fork-latency | sort | head -n 4
 * 1339) found
 * 1339) found
 * 1339) found
 * 1339) found
 *
 *
 * I'm wondering, why even with WNOHANG I get to check pids twice,
 * also because I'm clearing the pid, after I found it (list[o] = 0).
 *
 */

#include <unistd.h>             /* fork() */
#include <signal.h>             /* sigaction, sigemtpyset */
#include <sys/wait.h>           /* waitpid */
#include <stdio.h>              /* printf, NULL */

#define MAX 5000             /* number of forks */

pid_t list[MAX];
int i;
int got_sig;

void sig_child(int sig)
{
   got_sig = 1;
}

void reap_child()
{
   int o;
   int found;
   int status;
   pid_t pid;

   /* WNOHANG is evil: it makes us call the loop MORE THAN ONCE
    * PER DEAD CHILD! -> registering a dead child via signal
    * handler makes WNOHANG obsolete
    */
   //while((pid = waitpid(-1, &status, WNOHANG)) > 0) {
   while((pid = waitpid(-1, &status, 0)) > 0) {
      found = 0;
      // no need to search the whole list, use o = i instead
      // for(o = 0; o < MAX; o++) {
      for(o = i; o < MAX; o++) {
         if(list[o] == pid) {
            list[o] = 0;  /* empty */
            found = 1;
            break;
         }
      }
      if(found) {
         printf("(%d) found\n", pid);
      } else {
         printf("(%d) Unknown child exited\n", pid);
      }
   }

   got_sig = 0;
}

int main()
{
   struct sigaction sa;

   /* listen to SIGCHLD */
   sigemptyset(&sa.sa_mask);
   sa.sa_flags = 0;
   sa.sa_handler = sig_child;
   sa.sa_flags = SA_NOCLDSTOP;
   sigaction(SIGCHLD, &sa, NULL);

   i = MAX;

   for(i = MAX - 1; i >= 0; i--) {
      printf("Forking %d\n", i);
      list[i] = fork();

      /* child exists immediately */
      if(list[i] == 0) return 0;
      
      /* parent code */
      if(got_sig) reap_child();
   }
}
