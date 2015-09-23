#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_input(char input[]);

int main () {


    char str[30] = " test";
    char *ptr;
    long ret;
    
    ret = strtol(str, &ptr, 0);
    fprintf(stderr, "ERROR");
    read_input(str);
    printf("The number(unsigned long integer) is %ld\n", ret);
    printf("String part is |%s|", ptr);
    
    return(0);
}

void read_input(char input[]) {
    exit(1);
    fgets(input,100, stdin);
}
