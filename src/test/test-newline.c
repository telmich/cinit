#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *strip_final_newline(char *test1);

int main()
{
   // char *test1 = "zeile1\nzeile2\n";
   // char *test2 = "zeile1\nzeile2\nzeile3";
   char *test1;
   char *test2;

   test1 = malloc(50);
   test2 = malloc(50);

   strcpy(test1, "zeile1\nzeile2\n");
   strcpy(test2, "zeile1\nzeile2\nzeile3");

   char *result;

   result = strip_final_newline(test1);
   printf("A%sA\n", result);

   result = strip_final_newline(test2);
   printf("B%sB\n", result);

   return 0;
}
