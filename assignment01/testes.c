#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void penis(char l[]);

int main () {

  char c[] = "Hello";
  char *v = malloc(sizeof(strlen(c)));

  strcpy(v, c);
  printf("%s\n", v);
  penis(v);

  return 0;
}

void penis(char l[]) {

  printf("%s\n", l);

  return;
}
