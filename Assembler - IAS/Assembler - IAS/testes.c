#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_input(char input[]);

int main () {


    char *c, *input;
    scanf("%s", c);
    input = strtok(c, "\"");
    printf("%s", input);

  return 0;
}

void read_input(char input[]) {
    fgets(input,100, stdin);
}
