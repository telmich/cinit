#include <stdio.h>

struct msgq_server_short {
    long mtype;
    int mu;
};

main()
{
   struct msgq_server_short t1, *t2;

   t2 = &t1;

   int a = sizeof(t1);
   int b = sizeof(t2);
   int c = sizeof(*t2);

   printf("a=%d,b=%d,c=%d\n",a,b,c);

   return 0;
   
}
