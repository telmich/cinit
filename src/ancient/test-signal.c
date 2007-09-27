/* test case for glibc */

#include <unistd.h>
#include <signal.h>        /* sigaction, sigemtpyset  */
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>
#include <stdio.h>

void sig_child(int tmp)
{
   struct timeval tv;
   pid_t pid;


   while((pid = waitpid(-1, &tmp, WNOHANG)) > 0) {
      gettimeofday(&tv,NULL);
      printf("sighandler: %d\n",tv.tv_sec);
   }
}

int main()
{
   struct sigaction sa;
   struct timeval tv;
   struct timespec ts;
   pid_t pid;

   sigemptyset(&sa.sa_mask);
   sa.sa_flags = 0;

   sa.sa_handler  = sig_child;
   sa.sa_flags    = SA_NOCLDSTOP;

   sigaction(SIGCHLD,&sa,NULL);

   while(1) {
      pid = fork();

      /* child */
      if(!pid) {
         ts.tv_sec = 2;
         nanosleep(&ts,NULL);
         gettimeofday(&tv,NULL);     

         printf("child: %d\n",tv.tv_sec);
         return 0;
      }

      ts.tv_nsec = 100000;
      nanosleep(&ts,NULL);
   }
}
