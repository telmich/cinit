#include <mqueue.h>
#include <stdio.h>

int main()
{
   mqd_t readq = mq_open("/test",O_RDWR|O_CREAT|O_EXCL);
   //mqd_t readq = mq_open("/bin/ls",O_RDWR|O_CREAT|O_EXCL);

   if(readq == -1) {
      perror("oh nein");
      return 1;
   }
   mqd_t writeq = mq_open("/bin/cp",O_WRONLY|O_CREAT|O_EXCL);
   if(readq == -1) {
      perror("oh oh nein");
      return 1;
   }
}


