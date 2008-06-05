#include <string.h>             /* memcpy() */
#include <stdio.h>

struct cinit_answer {
   int options;
   char data[2045];
};

int f1(struct cinit_answer *buf);
int f2(struct cinit_answer *buf);

int f2(struct cinit_answer *buf)
{
   struct cinit_answer msg;

   printf("f2: %p\n", buf);

   msg.options = 12;
   strcpy(msg.data, "stringit");

   printf("addr= %p\n", memcpy(buf, &msg, sizeof(*buf)));

   printf("ok\n");

   return 1;
}

int f1(struct cinit_answer *buf)
{
   printf("f1: %p\n", buf);
   printf("ret=%d\n", f2(buf));

   return 1;
}

int main()
{
   struct cinit_answer test;

   if(!f1(&test))
      return 1;

   printf("s: %s d: %d\n", test.data, test.options);

   return 1;
}
