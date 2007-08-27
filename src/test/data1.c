#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
   int a, b, e;
   char *c = "/etc/cinit/svc/...", *data;

   int a2, b2;
   char *c2;

   a2 = b2 = 0;

   a = 1001;
   b = strlen(c);
   c2 = malloc(b+1);
   if(!c2) return 40;

   e = sizeof(a) + sizeof(b) + b;

   printf("e=%d (b=%d)\n",e,b);

   data = malloc(e);
   if(!data) return 20;

   /* in */
   strcpy(data,(char *) &a);
   e = sizeof(a);
   strcpy(&data[e],(char *) &b);
   e += sizeof(b);
   strcpy(&data[e],c);

   /* out */
   strncpy((char *) &a2,data,sizeof(a2));
   printf("a2=%d\n",a2);
   e = sizeof(a2);

   strncpy((char *) &b2,&data[e],sizeof(b2));
   printf("b2=%d\n",b2);
   e += sizeof(b2);

   strncpy(c2,&data[e],b2);
   printf("c2=%s\n",c2);

   return 0;
}
