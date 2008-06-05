#include <stdio.h>

int openreadclose(char *filename, char **where);

int main()
{
   char *data;
   char *file = "test_openreadclose.c";

   openreadclose(file, &data);

   printf("%s\n", data);

   return 1;

}
