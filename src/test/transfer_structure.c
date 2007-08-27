#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct test {
   char buf[2048];
   int cmd;
};

struct badtest {
   char *buf;
   int cmd;
};

#define PATH "/etc/cinit/svc/local-tuning/udev"

int main()
{
   struct test cmd;
   struct badtest nocmd;
   int pfd[2];
   int tmp;

   strcpy(cmd.buf,"/which/service/to/disable");
   cmd.cmd = 42;

   if(pipe(pfd) == -1) return 1;
   nocmd.cmd = 42;
   nocmd.buf = malloc(strlen(PATH)+1);
   strcpy(nocmd.buf,PATH);


   if(fork() > 1) {
      tmp = write(pfd[1],&cmd,sizeof(cmd));
      printf("PA: tmp=%d\n",tmp);

      tmp = write(pfd[1],&nocmd,sizeof(nocmd));
      printf("PA: tmp2=%d\n",tmp);
   } else {
      strcpy(cmd.buf,"");
      cmd.cmd = 0;
      
      tmp = read(pfd[0],&cmd,sizeof(cmd));
      printf("CH: tmp = %d, cmd = %d, buf = %s\n",tmp,cmd.cmd,cmd.buf);

      free(nocmd.buf);
      nocmd.cmd = 0;
      
      tmp = read(pfd[0],&nocmd,sizeof(nocmd));
      printf("CH: tmp = %d, cmd = %d, buf = %s\n",tmp,nocmd.cmd,nocmd.buf);
   }

   return 0;

}
